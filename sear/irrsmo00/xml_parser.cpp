#include "xml_parser.hpp"

#include <cstring>
#include <memory>
#include <regex>
#include <string>

#include "../conversion.hpp"
#include "logger.hpp"
#include "sear_error.hpp"

#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

namespace SEAR {
// Public Methods of XMLParser
nlohmann::json XMLParser::buildJSONString(SecurityRequest& request) {
  // Build JSON String from raw XML Security Result returned by IRRSMO00
  const char* p_raw_result = request.getRawResultPointer();
  int raw_result_length    = request.getRawResultLength();

  // Build a JSON string from the XML result string, SMO return and Reason
  // Codes
  Logger::getInstance().debug("Raw EBCDIC encoded result XML:");
  Logger::getInstance().hexDump(p_raw_result, raw_result_length);

  // Create a string from the raw pointer + length for conversion
  std::string ebcdic_string(p_raw_result, raw_result_length);

  std::string xml_buffer = toUTF8(ebcdic_string, "IBM-1047");

  Logger::getInstance().debug("Decoded result XML:", xml_buffer);

  // Pugixml refactor
  pugi::xml_document doc;

  // Load XML string into pugixml document
  pugi::xml_parse_result parse_result = doc.load_string(xml_buffer.c_str());

  if (!parse_result) {
    request.setSEARReturnCode(4);
    throw SEARError("unable to parse XML returned by IRRSMO00");
  }

  // Find the root <securityresult> node
  pugi::xml_node security_result_node = doc.child("securityresult");
  if (!security_result_node) {
    request.setSEARReturnCode(4);
    throw SEARError("XML does not contain <securityresult> node");
  }

  nlohmann::json result_json;
  pugi::xml_node admin_node = security_result_node.first_child();

  if (admin_node) {
    // recursively build the JSON object from the DOM tree
    convertXmlNodeToJson(admin_node, result_json);
    request.setSEARReturnCode(0);
  } else {
    request.setSEARReturnCode(4);
    throw SEARError("XML does not contain expected admin_type node");
  }

  return result_json;
}

void XMLParser::convertXmlNodeToJson(pugi::xml_node root,
                                     nlohmann::json& current_json) {
  // Iterate through all children of the current node
  // Initialization: Start from the first node
  // Condition: If node exists, it is true, otherwise false we reach the end of
  // the list and no more siblings Iteration: After finihsing the code, it jumps
  // to next tag at the same level
  for (pugi::xml_node node = root.first_child(); node;
       node                = node.next_sibling()) {
    // Check if this is a node (eg., <user>, <base>, etc.))
    if (node.type() == pugi::node_element) {
      // Gets tagname (e.g.,
      // user, permission, groupconnection etc.)
      std::string tag_name = node.name();
      nlohmann::json inner_data;

      // Check if this node just contains simple text (e.g.,
      // <racf:name operation="set">Squidward</racf:name>)
      // pugi::node_pcdata: Parsed Character Data, the plain text between an
      // opening and closing tag.
      if (node.first_child() &&
          node.first_child().type() == pugi::node_pcdata &&
          node.first_child() == node.last_child()) {
        // pugixml automatically unescapes &amp;, &lt;, etc. here
        inner_data = node.text().get();
      }
      // Check if it's an empty node (e.g.,
      // <racf:auditor operation="set"/>)
      else if (!node.first_child()) {
        inner_data = "";
      }
      // Otherwise, it has nested tags (e.g.,
      // <user> contains <base>, <csdata>, <omvs>)
      else {
        // Recursively convert nested tags to JSON
        convertXmlNodeToJson(node, inner_data);
      }

      // Add to the JSON object, converting to an array if the tag already
      // exists
      if (!current_json.contains(tag_name)) {
        current_json[tag_name] = inner_data;
      } else {
        if (current_json[tag_name].is_array()) {
          // If we do not already have this tag used in our object (at this
          // layer), just add data.
          current_json[tag_name].push_back(inner_data);
        } else {
          // If we already have this tag used in our object (at this layer),
          // we need to convert it to an array and add the new data.
          current_json[tag_name] = {current_json[tag_name], inner_data};
        }
      }
    }
  }
}
}  // namespace SEAR
