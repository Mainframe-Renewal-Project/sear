#ifndef __SEAR_UNIT_TEST_UTILITIES_
#define __SEAR_UNIT_TEST_UTILITIES_

#include <iostream>

#ifdef __TOS_390__
// arg pointers will be 32-bit when we run on z/OS.
#define TEST_IRRSEQ00_GENERIC_REQUEST_BUFFER_SIZE 1418
#define TEST_IRRSEQ00_RACF_OPTIONS_REQUEST_BUFFER_SIZE 1372
#define TEST_IRRSDL00_KEYRING_REQUEST_BUFFER_SIZE 1310
#else
// arg pointers will be 64 bit when we run off platform.
#define TEST_IRRSEQ00_GENERIC_REQUEST_BUFFER_SIZE 1474
#define TEST_IRRSEQ00_RACF_OPTIONS_REQUEST_BUFFER_SIZE 1428
#define TEST_IRRSDL00_KEYRING_REQUEST_BUFFER_SIZE 1310
#endif

// arg area should be the same on every platform.
#define TEST_IRRSEQ00_GENERIC_ARG_AREA_SIZE 1362
#define TEST_IRRSEQ00_RACF_OPTIONS_ARG_AREA_SIZE 1316
#define TEST_IRRSDL00_KEYRING_ARG_AREA_SIZE 1310

// This result sample is used in several places.
#define TEST_PARAMETER_VALIDATION_ERROR_RESULT_JSON \
  "./tests/validation/result_samples/"              \
  "test_parameter_validation_error_result.json"

// Common
char *get_sample(const char *filename, const char *mode);
char *get_raw_sample(const char *filename);
char *get_xml_sample(const char *filename, int *length);
std::string get_json_sample(const char *filename);
void test_validation_errors(const char *test_request_json,
                            const char *test_validation_errors_result_json,
                            bool debug);

// IRRSEQ00
void check_arg_pointers(char *raw_request, bool racf_options);
void test_extract_request_generation(const char *test_extract_request_json,
                                     const char *test_extract_request_raw,
                                     bool racf_options, bool debug);
void test_parse_extract_result(const char *test_extract_request_json,
                               const char *test_extract_result_json,
                               const char *test_extract_result_raw, bool debug);
void test_parse_extract_next_result(const char *test_extract_next_request_json,
                                    const char *test_extract_next_result_json,
                                    const char *test_extract_next_result_raw,
                                    bool debug);
void test_parse_extract_result_profile_not_found(
    const char *test_extract_request_json,
    const char *test_extract_result_profile_not_found_json, bool debug);

// IRRSMO00
void test_generate_add_alter_delete_request_generation(
    const char *test_add_alter_delete_request_json,
    const char *test_add_alter_delete_request_raw,
    int irrsmo00_options_expected, bool debug);
void test_parse_add_alter_delete_result(
    const char *test_add_alter_delete_request_json,
    const char *test_add_alter_delete_result_json,
    const char *test_add_alter_delete_result_raw, bool debug);

// IRRSDL00
void test_extract_request_irrsdl00_generation(
    const char *test_extract_request_json, const char *test_extract_request_raw,
    bool debug);
void test_parse_extract_irrsdl00_result(const char *test_extract_request_json,
                                        const char *test_extract_result_json,
                                        const char *test_extract_result_raw,
                                        bool debug);
void test_parse_extract_irrsdl00_result_keyring_not_found(
    const char *test_extract_request_json,
    const char *test_extract_result_keyring_not_found_json, bool debug);

void test_add_request_irrsdl00_generation(const char *test_add_request_json,
                                          const char *test_add_request_raw,
                                          bool debug);

void test_delete_request_irrsdl00_generation(
    const char *test_delete_request_json, const char *test_delete_request_raw,
    bool debug);
#endif
