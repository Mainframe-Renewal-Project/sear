#ifndef __SEAR_XML_PARSER_H_
#define __SEAR_XML_PARSER_H_

#include <nlohmann/json.hpp>
#include <pugixml.hpp>
#include <string>

#include "logger.hpp"
#include "security_request.hpp"

namespace SEAR {
// XMLParser Parses an XML String and forms a JSON String
class XMLParser {
 private:
  static void convertXmlNodeToJson(pugi::xml_node root,
                                   nlohmann::json& current_json);

 public:
  nlohmann::json buildJSONString(SecurityRequest& request);
};
}  // namespace SEAR

#endif
