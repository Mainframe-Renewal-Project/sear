#include "security_admin.hpp"

#include <arpa/inet.h>

#include <memory>
#include <nlohmann/json.hpp>

#include "irrsmo00.hpp"
#include "irrsmo00_error.hpp"
#include "keyring_extractor.hpp"
#include "keyring_modifier.hpp"
#include "keyring_post_processor.hpp"
#include "profile_extractor.hpp"
#include "profile_post_processor.hpp"
#include "sear_error.hpp"
#include "xml_generator.hpp"
#include "xml_parser.hpp"

namespace SEAR {
SecurityAdmin::SecurityAdmin(sear_result_t *p_result, bool debug) {
  Logger::getInstance().setDebug(debug);
  request_ = SecurityRequest(p_result);
}

void SecurityAdmin::makeRequest(const char *p_request_json_string, int length) {
  nlohmann::json request_json;

  try {
    std::string request_str(p_request_json_string, length);

    // Parse Request JSON
    try {
      request_json = nlohmann::json::parse(request_str);
    } catch (const nlohmann::json::parse_error &ex) {
      request_.setSEARReturnCode(8);
      throw SEARError(std::string("Syntax error in request JSON at byte ") +
                      std::to_string(ex.byte));
    }

    Logger::getInstance().debug("Validating parameters ...");
    try {
      SEAR_SCHEMA_VALIDATOR.validate(request_json);
    } catch (const std::exception &ex) {
      request_.setSEARReturnCode(8);
      throw SEARError(
          "The provided request JSON does not contain a valid request");
    }
    Logger::getInstance().debug("Done");

    // Load Request
    request_.load(request_json);

    // Make Request To Corresponding Callable Service
    if (request_.getOperation() == "extract" ||
        request_.getOperation() == "search") {
      if (request_.getAdminType() != "keyring") {
        Logger::getInstance().debug("Entering IRRSEQ00 path");
        ProfileExtractor profile_extractor;
        SecurityAdmin::doExtract(profile_extractor);
      } else {
        Logger::getInstance().debug("Entering IRRSDL00 path");
        KeyringExtractor keyring_extractor;
        SecurityAdmin::doExtract(keyring_extractor);
      }
    } else {
      if (request_.getAdminType() == "keyring" ||
          request_.getAdminType() == "certificate") {
        Logger::getInstance().debug("Entering IRRSDL00 path");
        KeyringModifier keyring_modifier;
        if (request_.getAdminType() == "keyring") {
          SecurityAdmin::doAddAlterDeleteKeyring(keyring_modifier);
        } else {
          if (request_.getOperation() == "add") {
            SecurityAdmin::doAddCertificate(keyring_modifier);
          } else if (request_.getOperation() == "delete") {
            SecurityAdmin::doDeleteCertificate(keyring_modifier);
          } else if (request_.getOperation() == "remove") {
            SecurityAdmin::doRemoveCertificate(keyring_modifier);
          }
        }
      } else {
        Logger::getInstance().debug("Entering IRRSMO00 path");
        SecurityAdmin::doAddAlterDelete();
      }
    }
  } catch (const SEARError &ex) {
    request_.setErrors(ex.getErrors());
  } catch (const IRRSMO00Error &ex) {
    request_.setErrors(ex.getErrors());
  } catch (const std::exception &ex) {
    request_.setSEARReturnCode(8);
    request_.setErrors({ex.what()});
  }
  request_.buildResult();
}

void SecurityAdmin::doExtract(Extractor &extractor) {
  extractor.extract(request_);

  if (request_.getAdminType() != "keyring") {
    ProfilePostProcessor post_processor;
    if (request_.getAdminType() == "racf-options") {
      // Post Process RACF Options Extract Result
      post_processor.postProcessRACFOptions(request_);
    } else if (request_.getAdminType() == "racf-rrsf") {
      post_processor.postProcessRACFRRSF(request_);
    } else {
      if (request_.getOperation() == "search") {
        // Post Process Generic Search Result
        post_processor.postProcessSearchGeneric(request_);
      } else {
        // Post Process Generic Extract Result
        post_processor.postProcessGeneric(request_);
      }
    }
  } else {
    KeyringPostProcessor post_processor;
    post_processor.postProcessExtractKeyring(request_);
  }

  Logger::getInstance().debug("Extract result has been post-processed");
}

void SecurityAdmin::doAddAlterDelete() {
  IRRSMO00 irrsmo00;

  // Check if profile exists already for some alter operations
  const std::string &operation    = request_.getOperation();
  const std::string &admin_type   = request_.getAdminType();
  const std::string &profile_name = request_.getProfileName();
  const std::string &class_name   = request_.getClassName();
  if ((operation == "alter") &&
      ((admin_type == "group") || (admin_type == "user") ||
       (admin_type == "dataset") || (admin_type == "resource"))) {
    Logger::getInstance().debug("Verifying that profile existis for alter ...");
    if (!irrsmo00.does_profile_exist(request_)) {
      request_.setSEARReturnCode(8);
      if (class_name.empty()) {
        throw SEARError("unable to alter '" + profile_name +
                        "' because the profile does not exist");
      } else {
        throw SEARError("unable to alter '" + profile_name + "' in the '" +
                        class_name +
                        "' class because the profile does not exist");
      }
    }

    // Since the profile exists check was successful,
    // we can clean up the preserved result information.
    if (void *req_ptr = request_.getRawRequestPointer()) {
      Logger::getInstance().debugFree(req_ptr);
      delete[] static_cast<char *>(req_ptr);
      request_.setRawRequestPointer(nullptr);
      request_.setRawRequestLength(0);
    }

    if (void *res_ptr = request_.getRawResultPointer()) {
      Logger::getInstance().debugFree(res_ptr);
      delete[] static_cast<char *>(res_ptr);
      request_.setRawResultPointer(nullptr);
      request_.setRawResultLength(0);
    }

    Logger::getInstance().debug("Done");
  }

  // Build Request
  XMLGenerator generator;
  generator.buildXMLString(request_);
  Logger::getInstance().debug("Calling IRRSMO00 ...");
  irrsmo00.call_irrsmo00(request_, false);
  Logger::getInstance().debug("Done");

  // Parse Result
  request_.setIntermediateResultJSON(XMLParser::buildJSONString(request_));

  // Post-Process Result
  irrsmo00.post_process_smo_json(request_);

  if (void *final_req = request_.getRawRequestPointer()) {
    delete[] static_cast<char *>(final_req);
    request_.setRawRequestPointer(nullptr);
    request_.setRawRequestLength(0);
  }

  if (void *final_res = request_.getRawResultPointer()) {
    delete[] static_cast<char *>(final_res);
    request_.setRawResultPointer(nullptr);
    request_.setRawResultLength(0);
  }

  Logger::getInstance().debug("Done");
}

void SecurityAdmin::doAddAlterDeleteKeyring(KeyringModifier &modifier) {
  modifier.addOrDeleteKeyring(request_);

  KeyringPostProcessor post_processor;
  post_processor.postProcessAddOrDeleteKeyring(request_);

  Logger::getInstance().debug(
      "Add/delete keyring result has been post-processed");
}

void SecurityAdmin::doAddCertificate(KeyringModifier &modifier) {
  modifier.addCertificate(request_);

  Logger::getInstance().debug("Add certificate result has been post-processed");
}

void SecurityAdmin::doDeleteCertificate(KeyringModifier &modifier) {
  modifier.deleteOrRemoveCertificate(request_);

  Logger::getInstance().debug(
      "Delete certificate result has been post-processed");
}

void SecurityAdmin::doRemoveCertificate(KeyringModifier &modifier) {
  modifier.deleteOrRemoveCertificate(request_);

  Logger::getInstance().debug(
      "Remove certificate result has been post-processed");
}
}  // namespace SEAR
