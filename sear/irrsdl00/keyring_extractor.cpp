#include "keyring_extractor.hpp"

#include "irrsdl00.hpp"
#include "sear_error.hpp"

namespace SEAR {
void KeyringExtractor::extract(SecurityRequest &request) {
  uint8_t function_code = request.getFunctionCode();

  /*************************************************************************/
  /* Keyring Extract                                                       */
  /*************************************************************************/
  if (function_code == KEYRING_EXTRACT_FUNCTION_CODE) {
    std::string owner   = request.getOwner();
    std::string keyring = request.getKeyring();

    auto unique_ptr =
        std::make_unique<char[]>(sizeof(keyring_extract_arg_area_t));
    keyring_extract_arg_area_t *p_arg_area =
        reinterpret_cast<keyring_extract_arg_area_t *>(unique_ptr.get());

    KeyringExtractor::buildKeyringExtractRequest(p_arg_area, owner, keyring,
                                                 function_code);

    request.setRawRequestLength((int)sizeof(keyring_extract_arg_area_t));
    Logger::getInstance().debug("Keyring extract request buffer:");
    Logger::getInstance().hexDump(reinterpret_cast<char *>(p_arg_area),
                                  request.getRawRequestLength());
    request.setRawRequestPointer(KeyringExtractor::preserveRawRequest(
        reinterpret_cast<char *>(p_arg_area), request.getRawRequestLength()));

    Logger::getInstance().debug("Calling IRRSDL00 ...");
    IRRSDL00::extractKeyring(request, p_arg_area);
    Logger::getInstance().debug("Done");
  }

  // Check Return Codes
  if (request.getSAFReturnCode() != 0 or request.getRACFReturnCode() != 0 or
      request.getRACFReasonCode() != 0 or
      request.getRawResultPointer() == nullptr) {
    request.setSEARReturnCode(4);
    // Raise Exception if Extract Failed.
    const std::string &profile_type = request.getAdminType();
    throw SEARError("unable to extract '" + profile_type + "'");
  }

  request.setSEARReturnCode(0);
}

void KeyringExtractor::buildKeyringExtractRequest(
    keyring_extract_arg_area_t *p_arg_area, std::string &owner,
    const std::string &keyring, uint8_t function_code) {
  std::memset(p_arg_area, 0, sizeof(keyring_extract_arg_area_t));

  /***************************************************************************/
  /* Set Extract Arguments                                                   */
  /***************************************************************************/
  p_arg_area->args.ALET_SAF_rc   = ALET;
  p_arg_area->args.ALET_RACF_rc  = ALET;
  p_arg_area->args.ALET_RACF_rsn = ALET;

  // Automatically convert lowercase userid to uppercase.
  std::transform(owner.begin(), owner.end(), owner.begin(),
                 [](unsigned char c) { return std::toupper(c); });

  // Copy userid
  std::memset(&p_arg_area->args.RACF_user_id[0], 0, 10);
  p_arg_area->args.RACF_user_id[0] = owner.length();
  std::memcpy(&p_arg_area->args.RACF_user_id[1], owner.c_str(), owner.length());
  // Encode userid as IBM-1047.
  __a2e_l(&p_arg_area->args.RACF_user_id[1], owner.length());

  // Copy keyring
  std::memset(&p_arg_area->args.ring_name[0], 0, 239);
  p_arg_area->args.ring_name[0] = keyring.length();
  std::memcpy(&p_arg_area->args.ring_name[1], keyring.c_str(),
              keyring.length());
  // Encode keyring as IBM-1047.
  __a2e_l(&p_arg_area->args.ring_name[1], keyring.length());
}

char *KeyringExtractor::preserveRawRequest(const char *p_arg_area,
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
