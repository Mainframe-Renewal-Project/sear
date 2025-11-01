#include "profile_extractor.hpp"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <new>
#include <sstream>

#include "sear_error.hpp"

#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

// Use htonl() to convert 32-bit values from little endian to big endian.
// use ntohl() to convert 16-bit values from big endian to little endian.
// On z/OS these macros do nothing since "network order" and z/Architecture are
// both big endian. This is only necessary for unit testing off platform.
#include <arpa/inet.h>

namespace SEAR {
void ProfileExtractor::extract(SecurityRequest &request) {
  uint32_t rc           = 0;

  uint8_t function_code = request.getFunctionCode();

  /*************************************************************************/
  /* RACF Options Extract                                                  */
  /*************************************************************************/
  if (function_code == RACF_OPTIONS_EXTRACT_FUNCTION_CODE) {
    // Build 31-bit Arg Area
    auto unique_ptr = make_unique31<racf_options_extract_underbar_arg_area_t>();
    racf_options_extract_underbar_arg_area_t *p_arg_area = unique_ptr.get();
    ProfileExtractor::buildRACFOptionsExtractRequest(p_arg_area);
    // Preserve the raw request data
    request.setRawRequestLength(
        (int)sizeof(racf_options_extract_underbar_arg_area_t));
    Logger::getInstance().debug("RACF Options extract request buffer:");
    Logger::getInstance().hexDump(reinterpret_cast<char *>(p_arg_area),
                                  request.getRawRequestLength());

    request.setRawRequestPointer(ProfileExtractor::cloneBuffer(
        reinterpret_cast<char *>(p_arg_area), request.getRawRequestLength()));

    // Call R_Admin
    Logger::getInstance().debug("Calling IRRSEQ00 ...");
    rc = callRadmin(reinterpret_cast<char *__ptr32>(&p_arg_area->arg_pointers));
    Logger::getInstance().debug("Done");

    request.setRawResultPointer(p_arg_area->args.p_result_buffer);
    // Preserve Return & Reason Codes
    request.setSAFReturnCode(ntohl(p_arg_area->args.SAF_rc));
    request.setRACFReturnCode(ntohl(p_arg_area->args.RACF_rc));
    request.setRACFReasonCode(ntohl(p_arg_area->args.RACF_rsn));
  }
  /***************************************************************************/
  /* Generic Extract                                                         */
  /*                                                                         */
  /* Use For:                                                                */
  /*   - User Extract                                                        */
  /*   - Group Extract                                                       */
  /*   - Group Connection Extract                                            */
  /*   - Resource Extract                                                    */
  /*   - Data Set Extract                                                    */
  /***************************************************************************/
  else {
    // Build 31-bit Arg Area
    auto unique_ptr = make_unique31<generic_extract_underbar_arg_area_t>();
    generic_extract_underbar_arg_area_t *p_arg_area = unique_ptr.get();
    ProfileExtractor::buildGenericExtractRequest(
        p_arg_area, request.getProfileName(), request.getClassName(),
        function_code);
    // Preserve the raw request data
    request.setRawRequestLength(
        (int)sizeof(generic_extract_underbar_arg_area_t));
    Logger::getInstance().debug("Generic extract request buffer:");
    Logger::getInstance().hexDump(reinterpret_cast<char *>(p_arg_area),
                                  request.getRawRequestLength());

    request.setRawRequestPointer(ProfileExtractor::cloneBuffer(
        reinterpret_cast<char *>(p_arg_area), request.getRawRequestLength()));

    // For search functions first try regular extract in case an existing name
    // was given as filter
    uint8_t save_function_code = function_code;
    switch (function_code) {
      case USER_EXTRACT_NEXT_FUNCTION_CODE:
        function_code                  = USER_EXTRACT_FUNCTION_CODE;
        p_arg_area->args.function_code = function_code;
        break;
      case GROUP_EXTRACT_NEXT_FUNCTION_CODE:
        function_code                  = GROUP_EXTRACT_FUNCTION_CODE;
        p_arg_area->args.function_code = function_code;
        break;
      case DATASET_EXTRACT_NEXT_FUNCTION_CODE:
        function_code                  = DATASET_EXTRACT_FUNCTION_CODE;
        p_arg_area->args.function_code = function_code;
        break;
      case RESOURCE_EXTRACT_NEXT_FUNCTION_CODE:
        function_code                  = RESOURCE_EXTRACT_FUNCTION_CODE;
        p_arg_area->args.function_code = function_code;
        break;
    }

    // Call R_Admin
    Logger::getInstance().debug("Calling IRRSEQ00 ...");
    rc = callRadmin(reinterpret_cast<char *__ptr32>(&p_arg_area->arg_pointers));
    Logger::getInstance().debug("Done");

    // In case of search and the exact filter doesn't exist as a profile,
    // retry with original function_code
    if (ntohl(p_arg_area->args.SAF_rc) == 4 &&
        ntohl(p_arg_area->args.RACF_rc) == 4 &&
        ntohl(p_arg_area->args.RACF_rsn) == 4 &&
        function_code != save_function_code) {
      function_code                  = save_function_code;
      p_arg_area->args.function_code = function_code;

      p_arg_area->arg_pointers.p_profile_extract_parms->flags |=
          htonl(0x14000000);

      // Call R_Admin
      Logger::getInstance().debug("Calling IRRSEQ00 ...");
      rc = callRadmin(
          reinterpret_cast<char *__ptr32>(&p_arg_area->arg_pointers));
      Logger::getInstance().debug("Done");
    } else {
      function_code                  = save_function_code;
      p_arg_area->args.function_code = function_code;
    }

    if (p_arg_area->args.SAF_rc == 0 &&
        p_arg_area->args.p_result_buffer != nullptr &&
        (function_code == USER_EXTRACT_NEXT_FUNCTION_CODE ||
         function_code == GROUP_EXTRACT_NEXT_FUNCTION_CODE ||
         function_code == DATASET_EXTRACT_NEXT_FUNCTION_CODE ||
         function_code == RESOURCE_EXTRACT_NEXT_FUNCTION_CODE)) {
      generic_extract_parms_results_t *p_save_generic_result;

      p_arg_area->arg_pointers.p_profile_extract_parms->flags |=
          htonl(0x14000000);

      do {
        p_save_generic_result =
            reinterpret_cast<generic_extract_parms_results_t *>(
                *p_arg_area->arg_pointers.p_p_result_buffer);

        const generic_extract_parms_results_t *p_generic_result =
            reinterpret_cast<generic_extract_parms_results_t *>(
                *p_arg_area->arg_pointers.p_p_result_buffer);
        const char *p_profile_name =
            *p_arg_area->arg_pointers.p_p_result_buffer +
            sizeof(generic_extract_parms_results_t);

        uint32_t filter_len =
            ntohl(p_arg_area->args.profile_extract_parms.profile_name_length);
        uint32_t profile_len = ntohl(p_generic_result->profile_name_length);
        if (profile_len >= filter_len &&
            ((filter_len == 1 && *p_arg_area->args.profile_name == 0x40) ||
             !std::memcmp(p_profile_name, p_arg_area->args.profile_name,
                          filter_len))) {
          Logger::getInstance().hexDump(p_profile_name, profile_len);

          auto unique_profile_name = std::make_unique<char[]>(profile_len);
          char *profile_name       = unique_profile_name.get();
          std::memcpy(profile_name, p_profile_name, profile_len);
          profile_name[profile_len] = 0;
          request.addFoundProfile(profile_name);
          unique_profile_name.release();
        } else {
          if (std::memcmp(p_profile_name, p_arg_area->args.profile_name,
                          filter_len) > 0) {
            break;
          }
        }

        p_arg_area->arg_pointers.p_profile_extract_parms =
            reinterpret_cast<generic_extract_parms_results_t *>(
                *p_arg_area->arg_pointers.p_p_result_buffer);

        // Call R_Admin
        Logger::getInstance().debug("Calling IRRSEQ00 ...");
        rc = callRadmin(
            reinterpret_cast<char *__ptr32>(&p_arg_area->arg_pointers));
        Logger::getInstance().debug("Done");

        if (p_arg_area->args.SAF_rc == 0)
          std::free(p_arg_area->arg_pointers.p_profile_extract_parms);
      } while (p_arg_area->args.SAF_rc == 0);

      *p_arg_area->arg_pointers.p_p_result_buffer =
          reinterpret_cast<char *>(p_save_generic_result);
    }

    request.setRawResultPointer(p_arg_area->args.p_result_buffer);
    // Preserve Return & Reason Codes
    request.setSAFReturnCode(ntohl(p_arg_area->args.SAF_rc));
    request.setRACFReturnCode(ntohl(p_arg_area->args.RACF_rc));
    request.setRACFReasonCode(ntohl(p_arg_area->args.RACF_rsn));
  }

  // Check Return Codes
  if (function_code == USER_EXTRACT_NEXT_FUNCTION_CODE ||
      function_code == GROUP_EXTRACT_NEXT_FUNCTION_CODE ||
      function_code == DATASET_EXTRACT_NEXT_FUNCTION_CODE ||
      function_code == RESOURCE_EXTRACT_NEXT_FUNCTION_CODE) {
    if (request.getSAFReturnCode() > 4 or request.getRACFReturnCode() > 4 or
        request.getRACFReasonCode() > 4 or rc != 0 or
        request.getRawResultPointer() == nullptr) {
      request.setSEARReturnCode(4);
      // Raise Exception if Search Failed.
      const std::string &admin_type = request.getAdminType();
      throw SEARError("unable to search '" + admin_type + "' profile '" +
                      request.getProfileName() + "'");
    }
  } else {
    if (request.getSAFReturnCode() != 0 or request.getRACFReturnCode() != 0 or
        request.getRACFReasonCode() != 0 or rc != 0 or
        request.getRawResultPointer() == nullptr) {
      request.setSEARReturnCode(4);
      // Raise Exception if Extract Failed.
      const std::string &admin_type = request.getAdminType();
      if (admin_type != "racf-options") {
        throw SEARError("unable to extract '" + admin_type + "' profile '" +
                        request.getProfileName() + "'");
      } else {
        throw SEARError("unable to extract '" + admin_type + "'");
      }
    }
  }

  std::ostringstream oss;
  oss << "IRRSEQ00 allocated in 31-bit memory at address "
      << static_cast<void *>(request.getRawResultPointer());
  Logger::getInstance().debug(oss.str());

  // We need to create a new buffer for the raw result to ensure
  // that it is allocated using "new" since the cleanup done later
  // will assume that the buffer was allocated using "new" and
  // will free the buffer using "delete". Since the 31-bit buffer
  // is allocated by irrseq00.s using '__malloc31()', we can't free
  // it using "delete" since that will result in undefined behavior.
  // Instead just create a new buffer using "make_unique()", which is
  // allocated using "new" under the covers, and free the original
  // buffer using "free()"".
  char *p_raw_result = request.getRawResultPointer();
  int raw_result_length;
  if (request.getAdminType() != "racf-options") {
    const generic_extract_parms_results_t *p_generic_result =
        reinterpret_cast<const generic_extract_parms_results_t *>(p_raw_result);
    raw_result_length = ntohl(p_generic_result->result_buffer_length);
  } else {
    const racf_options_extract_results_t *p_setropts_result =
        reinterpret_cast<const racf_options_extract_results_t *>(p_raw_result);
    raw_result_length = ntohl(p_setropts_result->result_buffer_length);
  }
  request.setRawResultPointer(
      ProfileExtractor::cloneBuffer(p_raw_result, raw_result_length));
  std::free(p_raw_result);
  request.setRawResultLength(raw_result_length);

  request.setSEARReturnCode(0);
}

void ProfileExtractor::buildGenericExtractRequest(
    generic_extract_underbar_arg_area_t *arg_area, std::string profile_name,
    std::string class_name, uint8_t function_code) {
  // Make sure buffer is clear.
  std::memset(arg_area, 0, sizeof(generic_extract_underbar_arg_area_t));

  generic_extract_args_t *args                 = &arg_area->args;
  generic_extract_arg_pointers_t *arg_pointers = &arg_area->arg_pointers;
  generic_extract_parms_results_t *profile_extract_parms =
      &args->profile_extract_parms;

  /***************************************************************************/
  /* Set Extract Arguments */
  /***************************************************************************/
  args->ALET_SAF_rc           = ALET;
  args->ALET_RACF_rc          = ALET;
  args->ALET_RACF_rsn         = ALET;
  args->ACEE                  = ACEE;
  args->result_buffer_subpool = RESULT_BUFFER_SUBPOOL;
  args->function_code         = function_code;

  // Copy profile name and class name.

  // Automatically convert lowercase profile names to uppercase.
  std::transform(profile_name.begin(), profile_name.end(), profile_name.begin(),
                 [](unsigned char c) { return std::toupper(c); });

  std::memcpy(args->profile_name, profile_name.c_str(), profile_name.length());
  // Encode profile name as IBM-1047.
  __a2e_l(args->profile_name, profile_name.length());
  if (function_code == RESOURCE_EXTRACT_FUNCTION_CODE ||
      function_code == RESOURCE_EXTRACT_NEXT_FUNCTION_CODE) {
    // Automatically convert lowercase class names to uppercase.
    std::transform(class_name.begin(), class_name.end(), class_name.begin(),
                   [](unsigned char c) { return std::toupper(c); });

    // Class name must be padded with blanks.
    std::memset(&profile_extract_parms->class_name, ' ', 8);
    std::memcpy(profile_extract_parms->class_name, class_name.c_str(),
                class_name.length());
    // Encode class name as IBM-1047.
    __a2e_l(profile_extract_parms->class_name, 8);
  }
  profile_extract_parms->profile_name_length = htonl(profile_name.length());

  if (function_code == USER_EXTRACT_NEXT_FUNCTION_CODE ||
      function_code == GROUP_EXTRACT_NEXT_FUNCTION_CODE ||
      function_code == DATASET_EXTRACT_NEXT_FUNCTION_CODE ||
      function_code == RESOURCE_EXTRACT_NEXT_FUNCTION_CODE) {
    profile_extract_parms->flags = htonl(0x4000000);
  }

  /***************************************************************************/
  /* Set Extract Argument Pointers */
  /*                                                                         */
  /* Enable transition from 64-bit XPLINK to 31-bit OSLINK. */
  /***************************************************************************/
  arg_pointers->p_work_area =
      reinterpret_cast<char *__ptr32>(&args->RACF_work_area);
  arg_pointers->p_ALET_SAF_rc   = &(args->ALET_SAF_rc);
  arg_pointers->p_SAF_rc        = &(args->SAF_rc);
  arg_pointers->p_ALET_RACF_rc  = &(args->ALET_RACF_rc);
  arg_pointers->p_RACF_rc       = &(args->RACF_rc);
  arg_pointers->p_ALET_RACF_rsn = &(args->ALET_RACF_rsn);
  arg_pointers->p_RACF_rsn      = &(args->RACF_rsn);

  arg_pointers->p_function_code = &(args->function_code);
  // Function specific parms between function code and profile name
  arg_pointers->p_profile_name          = &(args->profile_name[0]);
  arg_pointers->p_ACEE                  = &(args->ACEE);
  arg_pointers->p_result_buffer_subpool = &(args->result_buffer_subpool);
  arg_pointers->p_p_result_buffer       = &(args->p_result_buffer);

  // Turn on the hight order bit of the last argument,
  // which marks the end of the argument list.
  *(reinterpret_cast<uint32_t *__ptr32>(&arg_pointers->p_p_result_buffer)) |=
      0x80000000;
  arg_pointers->p_profile_extract_parms = profile_extract_parms;
}

void ProfileExtractor::buildRACFOptionsExtractRequest(
    racf_options_extract_underbar_arg_area_t *arg_area) {
  // Make sure buffer is clear.
  std::memset(arg_area, 0, sizeof(racf_options_extract_underbar_arg_area_t));

  racf_options_extract_args_t *args                 = &arg_area->args;
  racf_options_extract_arg_pointers_t *arg_pointers = &arg_area->arg_pointers;
  racf_options_extract_parms_t *racf_options_extract_parms =
      &args->racf_options_extract_parms;

  /***************************************************************************/
  /* Set Extract Arguments */
  /***************************************************************************/
  args->ALET_SAF_rc           = ALET;
  args->ALET_RACF_rc          = ALET;
  args->ALET_RACF_rsn         = ALET;
  args->ACEE                  = ACEE;
  args->result_buffer_subpool = RESULT_BUFFER_SUBPOOL;
  args->function_code         = RACF_OPTIONS_EXTRACT_FUNCTION_CODE;

  /***************************************************************************/
  /* Set Extract Argument Pointers */
  /*                                                                         */
  /* Enable transition from 64-bit XPLINK to 31-bit OSLINK. */
  /***************************************************************************/
  arg_pointers->p_work_area =
      reinterpret_cast<char *__ptr32>(&args->RACF_work_area);
  arg_pointers->p_ALET_SAF_rc   = &(args->ALET_SAF_rc);
  arg_pointers->p_SAF_rc        = &(args->SAF_rc);
  arg_pointers->p_ALET_RACF_rc  = &(args->ALET_RACF_rc);
  arg_pointers->p_RACF_rc       = &(args->RACF_rc);
  arg_pointers->p_ALET_RACF_rsn = &(args->ALET_RACF_rsn);
  arg_pointers->p_RACF_rsn      = &(args->RACF_rsn);

  arg_pointers->p_function_code = &(args->function_code);
  // Function specific parms between function code and profile name
  arg_pointers->p_profile_name          = &(args->profile_name[0]);
  arg_pointers->p_ACEE                  = &(args->ACEE);
  arg_pointers->p_result_buffer_subpool = &(args->result_buffer_subpool);
  arg_pointers->p_p_result_buffer       = &(args->p_result_buffer);

  // Turn on the hight order bit of the last argument,
  // which marks the end of the argument list.
  *(reinterpret_cast<uint32_t *__ptr32>(&arg_pointers->p_p_result_buffer)) |=
      0x80000000;
  arg_pointers->p_racf_options_extract_parms = racf_options_extract_parms;
}

char *ProfileExtractor::cloneBuffer(const char *p_buffer, const int &length) {
  auto request_unique_ptr = std::make_unique<char[]>(length);
  Logger::getInstance().debugAllocate(request_unique_ptr.get(), 64, length);
  std::memset(request_unique_ptr.get(), 0, length);
  std::memcpy(request_unique_ptr.get(), p_buffer, length);
  char *p_raw_request = request_unique_ptr.get();
  request_unique_ptr.release();
  return p_raw_request;
}
}  // namespace SEAR
