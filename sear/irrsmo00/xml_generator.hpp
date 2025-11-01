#ifndef __SEAR_XML_GENERATOR_H_
#define __SEAR_XML_GENERATOR_H_

#include <nlohmann/json.hpp>
#include <string>

#include "logger.hpp"
#include "security_request.hpp"

namespace SEAR {
// XMLGenerator Generates an XML String from a JSON string
class XMLGenerator {
 private:
  std::string xml_string_;
  static std::string replaceXMLChars(std::string data);
  void buildOpenTag(std::string tag);
  void buildMetaTag();
  void buildAttribute(std::string name, std::string value);
  void buildValue(std::string value);
  void buildEndNestedTag();
  void buildFullCloseTag(std::string tag);
  void buildCloseTagNoValue();
  void buildSingleTrait(const std::string& tag, const std::string& operation,
                        const std::string& value);
  void buildXMLHeaderAttributes(const SEAR::SecurityRequest& request,
                                const std::string& true_admin_type);
  void buildRequestData(const std::string& true_admin_type,
                        const std::string& admin_type,
                        nlohmann::json request_data);
  static std::string convertOperation(const std::string& operation);
  static std::string convertOperator(const std::string& trait_operator);
  static std::string convertAdminType(const std::string& admin_type);
  std::string JSONValueToString(const nlohmann::json& trait);

 public:
  void buildXMLString(SEAR::SecurityRequest& request);
};
}  // namespace SEAR

#endif
