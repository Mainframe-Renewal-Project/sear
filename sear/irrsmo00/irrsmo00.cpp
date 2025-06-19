#include "irrsmo00.hpp"

#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

#include "irrsmo00_error.hpp"
#include "sear_error.hpp"
#include "xml_generator.hpp"
#include "xml_parser.hpp"

#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

namespace SEAR {
void IRRSMO00::call_irrsmo00(SecurityRequest &request,
                             bool profile_exists_check) {
  char work_area[1024];
  char req_handle[64]                    = {0};

  const char *surrogate_userid           = request.getSurrogateUserID();
  running_userid_t running_userid_struct = {
      (unsigned char)std::strlen(surrogate_userid), {0}};
  std::strncpy(running_userid_struct.running_userid, surrogate_userid,
               running_userid_struct.running_userid_length);

  unsigned int alet    = 0;
  unsigned int acee    = 0;
  int num_parms        = 17;
  int fn               = 1;

  int irrsmo00_options = request.getIRRSMO00Options();
  if (profile_exists_check == true) {
    irrsmo00_options = 13;
  }

  int raw_request_length = request.getRawRequestLength();
  int raw_result_length  = 10000;

  int saf_return_code;
  int racf_return_code;
  int racf_reason_code;

  auto result_unique_ptr = std::make_unique<char[]>(raw_result_length);
  Logger::getInstance().debugAllocate(result_unique_ptr.get(), 64,
                                      raw_result_length);
  std::memset(result_unique_ptr.get(), 0, raw_result_length);

  IRRSMO64(work_area, alet, &saf_return_code, alet, &racf_return_code, alet,
           &racf_reason_code, &num_parms, &fn, &irrsmo00_options,
           &raw_request_length, request.getRawRequestPointer(), req_handle,
           reinterpret_cast<char *>(&running_userid_struct), acee,
           &raw_result_length, result_unique_ptr.get());

  Logger::getInstance().debug("raw_result_length");
  Logger::getInstance().hexDump(reinterpret_cast<char *>(&raw_result_length),
                                4);
  Logger::getInstance().debug("result_unique_ptr");
  Logger::getInstance().hexDump(result_unique_ptr.get(), raw_result_length);

  // 'knownConditionTrueFalse' is a false positive. These conditionals work as
  // intended
  if (((saf_return_code != 8) or (racf_return_code != 4000)) or
      // cppcheck-suppress knownConditionTrueFalse
      ((saf_return_code == 8) and
       // cppcheck-suppress knownConditionTrueFalse
       (racf_return_code == 4000) and (racf_reason_code > 100000000))) {
    request.setSAFReturnCode(saf_return_code);
    request.setRACFReturnCode(racf_return_code);
    request.setRACFReasonCode(racf_reason_code);
    request.setRawResultPointer(result_unique_ptr.get());
    result_unique_ptr.release();
    request.setRawResultLength(raw_result_length);
    return;
  }

  // Handle result buffer too small scenario.
  int bytes_remaining   = racf_reason_code;
  int new_result_length = raw_result_length + bytes_remaining + 1;
  Logger::getInstance().debug("bytes_remaining");
  Logger::getInstance().hexDump(reinterpret_cast<char *>(&bytes_remaining), 4);
  Logger::getInstance().debug("new_result_length");
  Logger::getInstance().hexDump(reinterpret_cast<char *>(&new_result_length),
                                4);
  auto full_result_unique_ptr = std::make_unique<char[]>(new_result_length);
  Logger::getInstance().debugAllocate(full_result_unique_ptr.get(), 64,
                                      new_result_length);
  std::memset(full_result_unique_ptr.get(), 0, new_result_length);
  std::memcpy(full_result_unique_ptr.get(), result_unique_ptr.get(),
              raw_result_length);

  char *p_next_byte =
      full_result_unique_ptr.get() + raw_result_length * sizeof(unsigned char);

  IRRSMO64(work_area, alet, &saf_return_code, alet, &racf_return_code, alet,
           &racf_reason_code, &num_parms, &fn, &irrsmo00_options,
           &raw_request_length, request.getRawRequestPointer(), req_handle,
           reinterpret_cast<char *>(&running_userid_struct), acee,
           &bytes_remaining, p_next_byte);

  Logger::getInstance().debug("bytes_remaining after");
  Logger::getInstance().hexDump(reinterpret_cast<char *>(&bytes_remaining), 4);
  new_result_length = raw_result_length + bytes_remaining;
  Logger::getInstance().debug("full_result_unique_ptr");
  Logger::getInstance().hexDump(full_result_unique_ptr.get(),
                                new_result_length);

  request.setSAFReturnCode(saf_return_code);
  request.setRACFReturnCode(racf_return_code);
  request.setRACFReasonCode(racf_reason_code);
  request.setRawResultPointer(full_result_unique_ptr.get());
  full_result_unique_ptr.release();
  request.setRawResultLength(new_result_length);
}

bool IRRSMO00::does_profile_exist(SecurityRequest &request) {
  const std::string &admin_type   = request.getAdminType();
  const std::string &profile_name = request.getProfileName();
  const std::string &class_name   = request.getClassName();

  std::string xml_string;

  if (admin_type == "resource") {
    Logger::getInstance().debug("Checking if '" + admin_type + "' profile '" +
                                profile_name + "' already exists in the '" +
                                class_name + "' ...");
    xml_string =
        R"(<securityrequest xmlns="http://www.ibm.com/systems/zos/saf" xmlns:racf="http://www.ibm.com/systems/zos/racf"><)" +
        admin_type + R"( name=")" + profile_name + R"(" class=")" + class_name +
        R"("operation="listdata" requestid=")" + admin_type +
        R"(_request"/></securityrequest>)";
  } else {
    Logger::getInstance().debug("Checking if '" + admin_type + "' profile '" +
                                profile_name + "' already exists ...");
    xml_string =
        R"(<securityrequest xmlns="http://www.ibm.com/systems/zos/saf" xmlns:racf="http://www.ibm.com/systems/zos/racf"><)" +
        admin_type + R"( name=")" + profile_name +
        R"(" operation="listdata" requestid=")" + admin_type +
        R"(_request"/></securityrequest>)";
  }

  Logger::getInstance().debug("Request XML:", xml_string);

  // convert our c++ string to a char * buffer
  auto request_unique_ptr = std::make_unique<char[]>(xml_string.length());
  Logger::getInstance().debugAllocate(request_unique_ptr.get(), 64,
                                      xml_string.length());
  std::strncpy(request_unique_ptr.get(), xml_string.c_str(),
               xml_string.length());
  __a2e_l(request_unique_ptr.get(), xml_string.length());

  Logger::getInstance().debug("EBCDIC encoded request XML:");
  Logger::getInstance().hexDump(request_unique_ptr.get(), xml_string.length());

  request.setRawRequestPointer(request_unique_ptr.get());
  request_unique_ptr.release();
  request.setRawRequestLength(xml_string.length());

  IRRSMO00::call_irrsmo00(request, true);

  Logger::getInstance().debug("Done");

  if (request.getRawResultPointer() == nullptr) {
    return false;
  }

  if ((request.getRACFReturnCode() > 0) or (request.getSAFReturnCode() > 0)) {
    return false;
  }

  return true;
}

void IRRSMO00::post_process_smo_json(SecurityRequest &request) {
  nlohmann::json results  = request.getIntermediateResultJSON();
  nlohmann::json commands = nlohmann::json::array();

  if (results.contains("error")) {
    request.setSEARReturnCode(4);
    // Only expected for irrsmo00 errors which are not expected, but possible
    if (results["error"].contains("textinerror")) {
      throw IRRSMO00Error(results["error"]["errormessage"].get<std::string>() +
                          " Text in error: " +
                          results["error"]["textinerror"].get<std::string>());
    }
    throw IRRSMO00Error(results["error"]["errormessage"].get<std::string>());
  }

  if (results.contains("errors")) {
    // Only expected for "XML Parse Error"
    request.setSEARReturnCode(4);
    throw IRRSMO00Error(results["errors"].get<std::vector<std::string>>());
  }

  if (!results.contains("command")) {
    // Only expected for "Add Protection" cases
    request.setSEARReturnCode(4);
    const std::string &admin_type   = request.getAdminType();
    const std::string &profile_name = request.getProfileName();
    const std::string &class_name   = request.getClassName();
    if (class_name.empty()) {
      throw SEARError("unable to add '" + profile_name + "' because a '" +
                      admin_type + "' profile already exists with that name");
    } else {
      throw SEARError("unable to add '" + profile_name + "' in the '" +
                      class_name + "' class because a '" + admin_type +
                      "' profile already exists in the '" + class_name +
                      "' class with that name");
    }
  }

  for (auto item = results.begin(); item != results.end();) {
    if ((item.key() == "command")) {
      item++;
    } else {
      item = results.erase(item);
    }
  }

  if (results["command"].contains("image")) {
    // If there is only one command in the json
    nlohmann::json command;
    command["command"]  = results["command"]["image"];
    command["messages"] = nlohmann::json::array();
    if (results["command"].contains("message")) {
      if (results["command"]["message"].is_array()) {
        command["messages"].merge_patch(results["command"]["message"]);
      } else {
        command["messages"].push_back(results["command"]["message"]);
      }
    }
    commands.push_back(command);
  } else {
    // Iterate through a list of commands
    for (const auto &item : results["command"].items()) {
      nlohmann::json current_command{};
      if (item.value().contains("image")) {
        current_command["command"] = item.value()["image"];
      }
      current_command["messages"] = nlohmann::json::array();
      if (item.value().contains("message")) {
        if (item.value()["message"].is_array()) {
          current_command["messages"].merge_patch(item.value()["message"]);
        } else {
          current_command["messages"].push_back(item.value()["message"]);
        }
      }
      commands.push_back(current_command);
    }
  }
  results.erase("command");
  results["commands"] = commands;
  request.setIntermediateResultJSON(results);
}
}  // namespace SEAR
