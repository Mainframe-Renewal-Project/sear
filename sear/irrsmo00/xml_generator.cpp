#include "xml_generator.hpp"

#include <cstring>
#include <memory>
#include <new>
#include <regex>

#include "key_map.hpp"
#include "logger.hpp"
#include "sear_error.hpp"
#include "trait_validation.hpp"
#include "../conversion.hpp"

#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

namespace SEAR {
// Public Functions of XMLGenerator
void XMLGenerator::buildXMLString(SecurityRequest& request) {
  // Main body function that builds an xml string
  const std::string& admin_type = request.getAdminType();
  const nlohmann::json& traits  = request.getTraits();

  // Build meta tag
  XMLGenerator::buildMetaTag();

  // Build the securityrequest tag (Consistent)
  XMLGenerator::buildOpenTag("securityrequest");

  XMLGenerator::buildAttribute("xmlns", "http://www.ibm.com/systems/zos/saf");
  XMLGenerator::buildAttribute("xmlns:racf",
                               "http://www.ibm.com/systems/zos/racf");
  XMLGenerator::buildEndNestedTag();

  std::string true_admin_type = convertAdminType(admin_type);
  XMLGenerator::buildOpenTag(true_admin_type);

  XMLGenerator::buildXMLHeaderAttributes(request, true_admin_type);

  XMLGenerator::buildAttribute("requestid", true_admin_type + "_request");

  if (!traits.empty()) {
    XMLGenerator::buildEndNestedTag();

    Logger::getInstance().debug("Validating traits ...");

    validate_traits(admin_type, request);

    XMLGenerator::buildRequestData(true_admin_type, admin_type, traits);

    Logger::getInstance().debug("Done");

    // Close the admin object
    XMLGenerator::buildFullCloseTag(true_admin_type);

    // Close the securityrequest tag (Consistent)
    XMLGenerator::buildFullCloseTag("securityrequest");
  } else {
    // Close the admin object
    XMLGenerator::buildCloseTagNoValue();
    // Close the securityrequest tag (Consistent)
    XMLGenerator::buildFullCloseTag("securityrequest");
  }

  Logger::getInstance().debug("Request XML:", xml_string_);

  std::string request_str_ebcdic = fromUTF8(xml_string_, "IBM-1047");

  auto request_unique_ptr_ebcdic = std::make_unique<char[]>(request_str_ebcdic.length());

  std::strncpy(request_unique_ptr_ebcdic.get(), request_str_ebcdic.c_str(),
               request_str_ebcdic.length());

  Logger::getInstance().debug("EBCDIC encoded request XML:");
  Logger::getInstance().hexDump(request_unique_ptr_ebcdic.get(), request_str_ebcdic.length());

  Logger::getInstance().debugAllocate(request_unique_ptr_ebcdic.get(), 64,
                                      request_str_ebcdic.length());


  request.setRawRequestPointer(request_unique_ptr_ebcdic.get());
  request_unique_ptr_ebcdic.release();
  request.setRawRequestLength(request_str_ebcdic.length());
}

// Private Functions of XMLGenerator
std::string XMLGenerator::replaceXMLChars(std::string data) {
  // Replace xml-substituted characters with their substitution strings
  std::string amp = "&amp;", gt = "&gt;", lt = "&lt;", quot = "&quot;",
              apos = "&apos;";
  for (std::size_t i = 0; i < data.length(); i++) {
    if (data[i] == '&') {
      data.replace(i, 1, amp, 0, amp.length());
      i += amp.length() - 1 - 1;
    }
    if (data[i] == '<') {
      data.replace(i, 1, lt, 0, lt.length());
      i += lt.length() - 1 - 1;
    }
    if (data[i] == '>') {
      data.replace(i, 1, gt, 0, gt.length());
      i += gt.length() - 1 - 1;
    }
    if (data[i] == '"') {
      data.replace(i, 1, quot, 0, quot.length());
      i += quot.length() - 1 - 1;
    }
    if (data[i] == '\'') {
      data.replace(i, 1, apos, 0, apos.length());
      i += apos.length() - 1 - 1;
    }
  }
  return data;
}
void XMLGenerator::buildOpenTag(std::string tag) {
  // Ex: "<base:universal_access"
  tag = XMLGenerator::replaceXMLChars(tag);
  xml_string_.append("<" + tag);
}
void XMLGenerator::buildMetaTag() {
  // Ex: "<?xml version="1.0" encoding="IBM-1047">"
  std::string tag = XMLGenerator::replaceXMLChars("IBM-1047");
  xml_string_.append("<?xml version=\"1.0\" encoding=\"" + tag + "\" ?>");
}
void XMLGenerator::buildAttribute(std::string name, std::string value) {
  // Ex: " operation=set"
  name  = XMLGenerator::replaceXMLChars(name);
  value = XMLGenerator::replaceXMLChars(value);
  xml_string_.append(" " + name + "=\"" + value + "\"");
}
void XMLGenerator::buildValue(std::string value) {
  // Ex: ">Read"
  value = XMLGenerator::replaceXMLChars(value);
  xml_string_.append(">" + value);
}
void XMLGenerator::buildEndNestedTag() { xml_string_.append(">"); }
void XMLGenerator::buildFullCloseTag(std::string tag) {
  // Ex: "</base:universal_access>"
  tag = replaceXMLChars(tag);
  xml_string_.append("</" + tag + ">");
}
void XMLGenerator::buildCloseTagNoValue() { xml_string_.append("/>"); }
void XMLGenerator::buildSingleTrait(const std::string& tag,
                                    const std::string& operation,
                                    const std::string& value) {
  // Combines above functions to build "trait" tags with added options and
  // values Ex: "<base:universal_access
  // operation=set>Read</base:universal_access>"
  XMLGenerator::buildOpenTag(tag);
  if (operation.length() != 0) {
    XMLGenerator::buildAttribute("operation", operation);
  }
  if (value.length() == 0) {
    XMLGenerator::buildCloseTagNoValue();
  } else {
    XMLGenerator::buildValue(value);
    XMLGenerator::buildFullCloseTag(tag);
  }
}

void XMLGenerator::buildXMLHeaderAttributes(
    const SecurityRequest& request, const std::string& true_admin_type) {
  // Obtain JSON Header information and Build into Admin Object where
  // appropriate
  const std::string& operation    = request.getOperation();
  const std::string& profile_name = request.getProfileName();
  const std::string& class_name   = request.getClassName();
  const std::string& group        = request.getGroup();
  const std::string& volume       = request.getVolume();
  const std::string& generic      = request.getGeneric();

  if (operation == "add") {
    XMLGenerator::buildAttribute("override", "no");
  }
  std::string irrsmo00_operation = XMLGenerator::convertOperation(operation);
  XMLGenerator::buildAttribute("operation", irrsmo00_operation);
  /*
  if (request.contains("run")) {
    buildAttribute("run", request["run"].get<std::string>());
  }
  */
  if (true_admin_type == "systemsettings") {
    return;
  }
  XMLGenerator::buildAttribute("name", profile_name);
  if ((true_admin_type == "user") or (true_admin_type == "group")) {
    return;
  }
  if (true_admin_type == "groupconnection") {
    XMLGenerator::buildAttribute("group", group);
    return;
  }
  if ((true_admin_type == "resource") or (true_admin_type == "permission")) {
    XMLGenerator::buildAttribute("class", class_name);
  }
  if ((true_admin_type == "dataset") or (true_admin_type == "permission")) {
    if (!volume.empty()) {
      XMLGenerator::buildAttribute("volume", volume);
    }
    if (!generic.empty()) {
      XMLGenerator::buildAttribute("generic", generic);
    }
    return;
  }
  return;
}

void XMLGenerator::buildRequestData(const std::string& true_admin_type,
                                    const std::string& admin_type,
                                    nlohmann::json request_data) {
  // Builds the xml for request data (segment-trait information) passed in a
  // json object
  nlohmann::json built_request{};
  std::string current_segment = "", item_segment, item_trait, item_operator;
  const char *translated_key, *racf_field_key;

  std::regex segment_trait_key_regex{R"~((([a-z]*):*)([a-z]*):(.*))~"};
  std::smatch segment_trait_key_data;

  auto item = request_data.begin();
  while (!request_data.empty()) {
    for (item = request_data.begin(); item != request_data.end();) {
      regex_match(item.key(), segment_trait_key_data, segment_trait_key_regex);
      if (segment_trait_key_data[3] == "") {
        item_operator = "";
        item_segment  = segment_trait_key_data[2];
      } else {
        item_operator = segment_trait_key_data[2];
        item_segment  = segment_trait_key_data[3];
      }
      item_trait = segment_trait_key_data[4];

      if (current_segment.empty()) {
        current_segment = item_segment;
        if ((true_admin_type != "systemsettings") and
            (true_admin_type != "groupconnection") and
            (true_admin_type != "permission")) {
          XMLGenerator::buildOpenTag(current_segment);
          XMLGenerator::buildEndNestedTag();
        }
      }

      if ((item_segment.compare(current_segment) == 0)) {
        // Build each individual trait
        int8_t trait_operator = map_operator(item_operator);
        // Need to obtain the actual data
        int8_t trait_type    = map_trait_type(item.value());
        int8_t expected_type = get_trait_type(admin_type, item_segment,
                                              item_segment + ":" + item_trait);
        if (expected_type == TRAIT_TYPE_PSEUDO_BOOLEAN and
            trait_type != TRAIT_TYPE_NULL) {
          trait_type = TRAIT_TYPE_PSEUDO_BOOLEAN;
        }
        translated_key = get_racf_key(admin_type.c_str(), item_segment.c_str(),
                                      (item_segment + ":" + item_trait).c_str(),
                                      trait_type, trait_operator);
        if (translated_key == nullptr) {
          // Temporary to get list/repeat traits working for RACF Options
          translated_key =
              get_racf_key(admin_type.c_str(), item_segment.c_str(),
                           (item_segment + ":" + item_trait).c_str(),
                           TRAIT_TYPE_REPEAT, trait_operator);
        }
        std::string trait_operator_str, value;
        switch (trait_type) {
          case TRAIT_TYPE_NULL:
            trait_operator_str = "del";
            value              = "";
            break;
          case TRAIT_TYPE_BOOLEAN:
            trait_operator_str = (item.value()) ? "set" : "del";
            value              = "";
            break;
          case TRAIT_TYPE_PSEUDO_BOOLEAN:
            trait_operator_str = "set";
            value              = (item.value()) ? "YES" : "NO";
            break;
          default:
            trait_operator_str =
                (item_operator.empty())
                    ? "set"
                    : XMLGenerator::convertOperator(item_operator);
            value = (trait_type == TRAIT_TYPE_BOOLEAN)
                        ? ""
                        : XMLGenerator::JSONValueToString(item.value());
        }
        racf_field_key =
            (!(*(translated_key + std::strlen(translated_key) - 1) == '*'))
                ? translated_key
                : item_trait.c_str();
        XMLGenerator::buildSingleTrait(("racf:" + std::string(racf_field_key)),
                                       trait_operator_str, value);
        item = request_data.erase(item);
      } else
        item++;
    }
    if ((true_admin_type != "systemsettings") and
        (true_admin_type != "groupconnection") and
        (true_admin_type != "permission")) {
      XMLGenerator::buildFullCloseTag(current_segment);
    }
    current_segment = "";
  }
}

std::string XMLGenerator::convertOperation(const std::string& operation) {
  // Converts the designated function to the correct IRRSMO00 operation.
  if (operation == "add") {
    return "set";
  }
  if (operation == "alter") {
    return "set";
  }
  if (operation == "delete") {
    return "del";
  }
  if (operation == "extract") {
    return "listdata";
  }
  return "";
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
  if (admin_type == "group-connection") {
    return "groupconnection";
  }
  if (admin_type == "racf-options") {
    return "systemsettings";
  }
  return admin_type;
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
