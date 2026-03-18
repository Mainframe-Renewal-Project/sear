#include "xml_generator.hpp"

#include <cstring>
#include <memory>
#include <new>
#include <pugixml.hpp>
#include <regex>
#include <sstream>
#include <unordered_map>

#include "../conversion.hpp"
#include "key_map.hpp"
#include "logger.hpp"
#include "sear_error.hpp"
#include "trait_validation.hpp"

#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

namespace SEAR {

// Admin Type Mapping between SEAR and IRRSMO00
// std::string_view for readonly strings
const std::unordered_map<std::string_view, std::string_view> ADMIN_TYPE_MAP = {
    {"group-connection", "groupconnection"},
    {    "racf-options",  "systemsettings"}
};

// Operation Mapping between SEAR and IRRSMO00
const std::unordered_map<std::string_view, std::string_view> OPERATION_MAP = {
    {    "add",      "set"},
    {  "alter",      "set"},
    { "delete",      "del"},
    {"extract", "listdata"}
};

// Public Functions of XMLGenerator
void XMLGenerator::buildXMLString(SecurityRequest& request) {
  // Main body function that builds an xml string
  const std::string& admin_type = request.getAdminType();
  const nlohmann::json& traits  = request.getTraits();

  // Build pugixml document
  pugi::xml_document doc;

  // First XML declaration node with version and encoding attributes
  auto declaration = doc.prepend_child(pugi::node_declaration);

  // Build meta data attributes for the XML declaration
  declaration.append_attribute("version")  = "1.0";
  declaration.append_attribute("encoding") = "IBM-1047";

  // Build securityrequest node
  auto security_request_node = doc.append_child("securityrequest");

  security_request_node.append_attribute("xmlns") =
      "http://www.ibm.com/systems/zos/saf";
  security_request_node.append_attribute("xmlns:racf") =
      "http://www.ibm.com/systems/zos/racf";

  std::string true_admin_type = convertAdminType(admin_type);
  auto admin_node = security_request_node.append_child(true_admin_type.c_str());

  buildPugixmlHeaderAttributes(admin_node, request, true_admin_type);
  admin_node.append_attribute("requestid") =
      (true_admin_type + "_request").c_str();

  if (!traits.empty()) {
    Logger::getInstance().debug("Validating traits ...");
    // Validate traits
    validate_traits(admin_type, request);
    // Build XML body with traits
    buildPugixmlRequestData(admin_node, true_admin_type, admin_type, traits);

    Logger::getInstance().debug("Done");
  }

  // Declare the buffer that will hold XML string
  std::stringstream ss;

  // Save and encode the XML string into the buffer
  // "": no indentation characters at all
  // pugi::format_raw: prevent pugixml from adding extra whitespace
  doc.save(ss, "", pugi::format_raw);

  std::string xml_string = ss.str();

  // Add a space before the "?>" in the XML declaration to prevent an issue
  // where IRRSMO00 does not properly read the XML declaration if there is no
  // space
  std::string from = "encoding=\"IBM-1047\"?>";
  size_t pos       = xml_string.find(from);
  if (pos != std::string::npos)
    xml_string.replace(pos, from.size(), "encoding=\"IBM-1047\" ?>");

  Logger::getInstance().debug("Request XML:", xml_string);

  std::string request_str_ebcdic   = fromUTF8(xml_string, "IBM-1047");
  size_t request_str_ebcdic_length = request_str_ebcdic.length();

  // Allocate memory for the EBCDIC encoded XML string and copy the string into
  // it
  auto buffer = std::make_unique<char[]>(request_str_ebcdic_length);
  // std::copy: instead of strncpy, it does not add null terminators
  std::copy(request_str_ebcdic.begin(), request_str_ebcdic.end(), buffer.get());

  Logger::getInstance().debug("EBCDIC encoded request XML:");
  Logger::getInstance().hexDump(buffer.get(), request_str_ebcdic.length());

  // buffer.release() returns directly the pointer
  request.setRawRequestPointer(buffer.release());
  request.setRawRequestLength(request_str_ebcdic.length());
}

void XMLGenerator::buildPugixmlSingleTrait(pugi::xml_node& node,
                                           const std::string& tag,
                                           const std::string& operation,
                                           const std::string& value) {
  // Combines above functions to build "trait" tags with added options and
  // values Ex: "<base:universal_access
  // operation=set>Read</base:universal_access>"
  pugi::xml_node trait = node.append_child(tag.c_str());

  if (!operation.empty()) {
    trait.append_attribute("operation") = operation.c_str();
  }
  if (!value.empty()) {
    trait.text().set(value.c_str());
  }
}

void XMLGenerator::buildPugixmlHeaderAttributes(
    pugi::xml_node& node, const SecurityRequest& request,
    const std::string& true_admin_type) {
  // Obtain JSON Header information and Build into Admin Object where
  // appropriate
  const std::string& operation    = request.getOperation();
  const std::string& profile_name = request.getProfileName();
  const std::string& class_name   = request.getClassName();
  const std::string& group        = request.getGroup();
  const std::string& volume       = request.getVolume();
  const std::string& generic      = request.getGeneric();

  if (operation == "add") {
    node.append_attribute("override") = "no";
  }
  std::string irrsmo00_operation = XMLGenerator::convertOperation(operation);
  node.append_attribute("operation") = irrsmo00_operation;
  /*
  if (request.contains("run")) {
    buildAttribute("run", request["run"].get<std::string>());
  }
  */
  if (true_admin_type == "systemsettings") {
    return;
  }
  node.append_attribute("name") = profile_name;
  if ((true_admin_type == "user") or (true_admin_type == "group")) {
    return;
  }
  if (true_admin_type == "groupconnection") {
    node.append_attribute("group") = group;
    return;
  }
  if ((true_admin_type == "resource") or (true_admin_type == "permission")) {
    node.append_attribute("class") = class_name;
  }
  if ((true_admin_type == "dataset") or (true_admin_type == "permission")) {
    if (!volume.empty()) {
      node.append_attribute("volume") = volume;
    }
    if (!generic.empty()) {
      node.append_attribute("generic") = generic;
    }
    return;
  }
  return;
}

void XMLGenerator::buildPugixmlRequestData(pugi::xml_node& node,
                                           const std::string& true_admin_type,
                                           const std::string& admin_type,
                                           nlohmann::json request_data) {
  // Build the traits into the XML body. Each trait is represented as a child
  // node under the admin type node. E.g.
  // delete:operparm:receive_internal_console_messages: null
  for (auto& [key, value] : request_data.items()) {
    // Replace regex by string splitting
    // Expected format: [operation:][segment]:trait
    std::string item_operator, item_segment, item_trait;

    // Find the position of first and last colon in the key
    size_t first_colon = key.find(':');
    size_t last_colon  = key.rfind(':');

    // operation:segment:trait
    if (first_colon != last_colon) {
      // E.g. delete from delete:operparm:receive_internal_console_messages
      item_operator = key.substr(0, first_colon);
      // E.g. operparm from delete:operparm:receive_internal_console_messages
      item_segment =
          key.substr(first_colon + 1, last_colon - (first_colon + 1));

    } else {
      // segment:trait
      //  E.g. base from base:name
      item_segment = key.substr(0, first_colon);
    }
    // Trait name for the last part
    // E.g. receive_internal_console_messages from
    // delete:operparm:receive_internal_console_messages
    item_trait = key.substr(last_colon + 1);

    // systemsettings/groupconnection/permission don't use <segment>
    bool is_flat = (true_admin_type == "systemsettings" ||
                    true_admin_type == "groupconnection" ||
                    true_admin_type == "permission");

    // Segment node that the trait will be attached to.
    // E.g. <base> or <operparm>
    pugi::xml_node segment_node;

    if (is_flat) {
      // Use the admin type node directly
      // E.g. <systemsettings> or <groupconnection> or <permission>
      segment_node = node;
    } else {
      // Check if segment node already exists
      segment_node = node.child(item_segment.c_str());

      if (!segment_node) {
        // If segment node does not exist, create it
        segment_node = node.append_child(item_segment.c_str());
      }
    }

    int8_t trait_operator = map_operator(item_operator);
    int8_t trait_type     = map_trait_type(value);
    int8_t expected_type  = get_trait_type(admin_type, item_segment,
                                           item_segment + ":" + item_trait);

    // If the trait type is pseudo-boolean, but the expected type is not null,
    // then treat it as pseudo-boolean. In this case, we want to treat it as
    // pseudo-boolean "YES"/"NO"
    if (expected_type == TRAIT_TYPE_PSEUDO_BOOLEAN &&
        trait_type != TRAIT_TYPE_NULL) {
      trait_type = TRAIT_TYPE_PSEUDO_BOOLEAN;
    }

    const char* translated_key = get_racf_key(
        admin_type.c_str(), item_segment.c_str(),
        (item_segment + ":" + item_trait).c_str(), trait_type, trait_operator);

    std::string trait_operation = "set";
    std::string val_str;

    switch (trait_type) {
      case TRAIT_TYPE_NULL:
        trait_operation = "del";
        break;
      case TRAIT_TYPE_BOOLEAN:
        // value.get<bool>() returns a boolean from JSON value.
        if (value.get<bool>() == true) {
          trait_operation = "set";
        } else {
          trait_operation = "del";
        }
        break;
      case TRAIT_TYPE_PSEUDO_BOOLEAN:
        trait_operation = "set";

        if (value.get<bool>() == true) {
          val_str = "YES";
        } else {
          val_str = "NO";
        }
        break;
      default:
        // Use item_operator to determine the trait operation.
        // If item_operator is empty, then it defaults to "set" operation.
        if (item_operator.empty()) {
          trait_operation = "set";
        } else {
          trait_operation = XMLGenerator::convertOperator(item_operator);
        }
        val_str = JSONValueToString(value);
        break;
    }

    std::string racf_tag = "racf:";

    // E.g. racf:name
    if (translated_key &&
        translated_key[std::strlen(translated_key) - 1] != '*') {
      racf_tag += translated_key;
    } else {
      racf_tag += item_trait;
    }

    buildPugixmlSingleTrait(segment_node, racf_tag, trait_operation, val_str);
  }
}

std::string XMLGenerator::convertOperation(const std::string& operation) {
  // Converts the designated function to the correct IRRSMO00 operation.
  auto operator_xml = OPERATION_MAP.find(operation);
  if (operator_xml != OPERATION_MAP.end()) {
    // Found in mapper, return the corresponding XML operator
    // operator_xml->second: returns the value
    return std::string(operator_xml->second);
  } else {
    return "";
  }
}

std::string XMLGenerator::convertOperator(const std::string& trait_operator) {
  // Converts the designated function to the correct IRRSMO00 operator
  if (trait_operator == "delete") {
    return "del";
  }
  return trait_operator;
}

std::string XMLGenerator::convertAdminType(const std::string& admin_type) {
  // Converts the admin type between sear's definitions and IRRSMO00's
  // definitions. group-connection to groupconnection, racf-options to
  // systemsettings. All other admin types should be
  // unchanged

  // Find the admin type in mapper
  auto admin_type_xml = ADMIN_TYPE_MAP.find(admin_type);
  // Check if the admin type exists in mapper.
  if (admin_type_xml != ADMIN_TYPE_MAP.end()) {
    // Found in mapper, return the corresponding XML admin type
    // admin_type_xml->second: returns the value
    return std::string(admin_type_xml->second);
  } else {
    // Not found, return the original admin type
    return admin_type;
  }
}

std::string XMLGenerator::JSONValueToString(const nlohmann::json& trait) {
  if (trait.is_string()) {
    return trait.get<std::string>();
  }
  if (trait.is_array()) {
    std::string output_string = "";
    std::string delimeter =
        ", ";  // May just be " " or just be ","; May need to test
    for (const auto& item : trait.items()) {
      output_string += item.value().get<std::string>() + delimeter;
    }
    for (int i = 0; i < delimeter.length(); i++) {
      output_string.pop_back();
    }
    return output_string;
  }
  return trait.dump();
}
}  // namespace SEAR
