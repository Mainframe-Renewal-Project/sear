#include "keyring_modifier.hpp"

#include "irrsdl00.hpp"
#include "sear_error.hpp"

namespace SEAR {
void KeyringModifier::addOrDeleteKeyring(SecurityRequest &request) {
  uint8_t function_code = request.getFunctionCode();

  /*************************************************************************/
  /* Keyring Modify                                                        */
  /*************************************************************************/
  if (function_code == KEYRING_ADD_FUNCTION_CODE ||
      function_code == KEYRING_DELETE_FUNCTION_CODE) {
    auto unique_ptr =
        std::make_unique<char[]>(sizeof(keyring_modify_arg_area_t));
    keyring_modify_arg_area_t *p_arg_area =
        reinterpret_cast<keyring_modify_arg_area_t *>(unique_ptr.get());
    std::memset(p_arg_area, 0, sizeof(keyring_modify_arg_area_t));

    KeyringModifier::buildKeyringArgs(&p_arg_area->args, request, false);

    request.setRawRequestLength((int)sizeof(keyring_modify_arg_area_t));
    Logger::getInstance().debug("Keyring modify request buffer:");
    Logger::getInstance().hexDump(reinterpret_cast<char *>(p_arg_area),
                                  request.getRawRequestLength());
    request.setRawRequestPointer(KeyringModifier::preserveRawRequest(
        reinterpret_cast<char *>(p_arg_area), request.getRawRequestLength()));

    Logger::getInstance().debug("Calling IRRSDL00 ...");
    IRRSDL00::addOrDeleteKeyring(request, p_arg_area);
    Logger::getInstance().debug("Done");
  }

  // Check Return Codes
  if (request.getSAFReturnCode() > 4 or request.getRACFReturnCode() > 4) {
    request.setSEARReturnCode(4);
    // Raise Exception if Modify Failed.
    const std::string &profile_type = request.getAdminType();
    throw SEARError("unable to modify '" + profile_type + "'");
  }

  request.setSEARReturnCode(0);
}

void KeyringModifier::addCertificate(SecurityRequest &request) {
  uint8_t function_code = request.getFunctionCode();

  /*************************************************************************/
  /* Add certificate                                                       */
  /*************************************************************************/
  if (function_code == CERTIFICATE_ADD_FUNCTION_CODE) {
    auto unique_ptr =
        std::make_unique<char[]>(sizeof(certificate_add_arg_area_t));
    certificate_add_arg_area_t *p_arg_area =
        reinterpret_cast<certificate_add_arg_area_t *>(unique_ptr.get());
    std::memset(p_arg_area, 0, sizeof(certificate_add_arg_area_t));

    KeyringModifier::buildKeyringArgs(&p_arg_area->args, request, true);

    request.setRawRequestLength((int)sizeof(certificate_add_arg_area_t));
    Logger::getInstance().debug("Certificate add request buffer:");
    Logger::getInstance().hexDump(reinterpret_cast<char *>(p_arg_area),
                                  request.getRawRequestLength());
    request.setRawRequestPointer(KeyringModifier::preserveRawRequest(
        reinterpret_cast<char *>(p_arg_area), request.getRawRequestLength()));

    Logger::getInstance().debug("Calling IRRSDL00 ...");
    IRRSDL00::addCertificate(request, p_arg_area);
    Logger::getInstance().debug("Done");
  }

  // Check Return Codes
  if (request.getSAFReturnCode() > 4 or request.getRACFReturnCode() > 4) {
    request.setSEARReturnCode(4);
    // Raise Exception if Modify Failed.
    const std::string &profile_type = request.getAdminType();
    throw SEARError("unable to add '" + profile_type + "'");
  }

  request.setSEARReturnCode(0);
}

void KeyringModifier::deleteOrRemoveCertificate(SecurityRequest &request) {
  uint8_t function_code = request.getFunctionCode();

  /*************************************************************************/
  /* Delete certificate                                                    */
  /*************************************************************************/
  if (function_code == CERTIFICATE_DELETE_FUNCTION_CODE ||
      function_code == CERTIFICATE_REMOVE_FUNCTION_CODE) {
    auto unique_ptr =
        std::make_unique<char[]>(sizeof(certificate_delete_arg_area_t));
    certificate_delete_arg_area_t *p_arg_area =
        reinterpret_cast<certificate_delete_arg_area_t *>(unique_ptr.get());
    std::memset(p_arg_area, 0, sizeof(certificate_delete_arg_area_t));

    KeyringModifier::buildKeyringArgs(&p_arg_area->args, request, true);

    request.setRawRequestLength((int)sizeof(certificate_delete_arg_area_t));
    Logger::getInstance().debug("Certificate delete request buffer:");
    Logger::getInstance().hexDump(reinterpret_cast<char *>(p_arg_area),
                                  request.getRawRequestLength());
    request.setRawRequestPointer(KeyringModifier::preserveRawRequest(
        reinterpret_cast<char *>(p_arg_area), request.getRawRequestLength()));

    Logger::getInstance().debug("Calling IRRSDL00 ...");
    if (function_code == CERTIFICATE_DELETE_FUNCTION_CODE)
      IRRSDL00::deleteCertificate(request, p_arg_area, false);
    else if (function_code == CERTIFICATE_REMOVE_FUNCTION_CODE)
      IRRSDL00::deleteCertificate(request, p_arg_area, true);
    Logger::getInstance().debug("Done");
  }

  // Check Return Codes
  if (request.getSAFReturnCode() > 4 or request.getRACFReturnCode() > 4) {
    request.setSEARReturnCode(4);
    // Raise Exception if Modify Failed.
    const std::string &profile_type = request.getAdminType();
    throw SEARError("unable to delete '" + profile_type + "'");
  }

  request.setSEARReturnCode(0);
}

void KeyringModifier::buildKeyringArgs(keyring_args_t *p_args,
                                       const SecurityRequest &request,
                                       bool use_keyring_owner) {
  /***************************************************************************/
  /* Set Modify Arguments                                                    */
  /***************************************************************************/
  p_args->ALET_SAF_rc   = ALET;
  p_args->ALET_RACF_rc  = ALET;
  p_args->ALET_RACF_rsn = ALET;

  std::string owner;
  if (use_keyring_owner)
    owner = request.getKeyringOwner();
  else
    owner = request.getOwner();
  std::string keyring = request.getKeyring();

  // Automatically convert lowercase userid to uppercase.
  std::transform(owner.begin(), owner.end(), owner.begin(),
                 [](unsigned char c) { return std::toupper(c); });

  // Copy userid
  std::memset(&p_args->RACF_user_id[0], 0, 10);
  p_args->RACF_user_id[0] = owner.length();
  std::memcpy(&p_args->RACF_user_id[1], owner.c_str(), owner.length());
  // Encode userid as IBM-1047.
  __a2e_l(&p_args->RACF_user_id[1], owner.length());

  // Copy keyring
  std::memset(&p_args->ring_name[0], 0, 239);
  p_args->ring_name[0] = keyring.length();
  std::memcpy(&p_args->ring_name[1], keyring.c_str(), keyring.length());
  // Encode keyring as IBM-1047.
  __a2e_l(&p_args->ring_name[1], keyring.length());
}

char *KeyringModifier::preserveRawRequest(const char *p_arg_area,
                                          const int &raw_request_length) {
  try {
    auto request_unique_ptr = std::make_unique<char[]>(raw_request_length);
    Logger::getInstance().debugAllocate(request_unique_ptr.get(), 64,
                                        raw_request_length);
    std::memset(request_unique_ptr.get(), 0, raw_request_length);
    std::memcpy(request_unique_ptr.get(), p_arg_area, raw_request_length);
    char *p_raw_request = request_unique_ptr.get();
    request_unique_ptr.release();
    return p_raw_request;
  } catch (const std::bad_alloc &ex) {
    std::perror(
        "Warn - Unable to allocate space to preserve the raw request.\n");
    return nullptr;
  }
}
}  // namespace SEAR
