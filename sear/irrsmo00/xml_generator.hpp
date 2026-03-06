#ifndef __SEAR_XML_GENERATOR_H_
#define __SEAR_XML_GENERATOR_H_

#include <nlohmann/json.hpp>
#include <pugixml.hpp>
#include <string>

#include "logger.hpp"
#include "security_request.hpp"

namespace SEAR {
// XMLGenerator Generates an XML String from a JSON string
class XMLGenerator {
 private:
  std::string xml_string_;
  static std::string replaceXMLChars(std::string data);
  void buildAttribute(std::string name, std::string value);
  void buildXMLHeaderAttributes(const SEAR::SecurityRequest& request,
                                const std::string& true_admin_type);
  static std::string convertOperation(const std::string& operation);
  static std::string convertOperator(const std::string& trait_operator);
  static std::string convertAdminType(const std::string& admin_type);
  std::string JSONValueToString(const nlohmann::json& trait);
  void buildPugixmlHeaderAttributes(pugi::xml_node& node,
                                    const SEAR::SecurityRequest& request,
                                    const std::string& true_admin_type);
  void buildPugixmlRequestData(pugi::xml_node& node,
                               const std::string& true_admin_type,
                               const std::string& admin_type,
                               nlohmann::json request_data);
  static void buildPugixmlSingleTrait(pugi::xml_node& node,
                                      const std::string& tag,
                                      const std::string& operation,
                                      const std::string& value);

 public:
  void buildXMLString(SEAR::SecurityRequest& request);
};
}  // namespace SEAR

#endif
