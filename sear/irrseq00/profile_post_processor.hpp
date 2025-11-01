#ifndef __SEAR_PROFILE_POST_PROCESSOR_H_
#define __SEAR_PROFILE_POST_PROCESSOR_H_

#include <nlohmann/json.hpp>
#include <string>

#include "irrseq00.hpp"
#include "logger.hpp"
#include "security_request.hpp"

namespace SEAR {
class ProfilePostProcessor {
 public:
  static void postProcessGeneric(SecurityRequest &request);
  static void postProcessSearchGeneric(SecurityRequest &request);
  static void postProcessRACFOptions(SecurityRequest &request);

 private:
  static void processGenericField(nlohmann::json &json_field,
                                  const generic_field_descriptor_t *p_field,
                                  const char *p_profile,
                                  const char sear_field_type
                                );
  static std::string postProcessFieldKey(const std::string &admin_type,
                                         const std::string &segment,
                                         const char *p_raw_field_key
                                        );
  static std::string postProcessKey(const char *p_source_key, int length);
  static std::string decodeEBCDICBytes(const char *p_ebcdic_bytes, int length);
};
}  // namespace SEAR

#endif
