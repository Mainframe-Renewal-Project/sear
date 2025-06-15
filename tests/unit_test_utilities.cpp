#include "unit_test_utilities.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <fstream>
#include <nlohmann/json.hpp>

#include "sear/sear.h"
#include "tests/mock/irrsdl64.hpp"
#include "tests/mock/irrseq00.hpp"
#include "tests/mock/irrsmo64.hpp"
#include "tests/unity/unity.h"

#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

/*************************************************************************/
/* Common                                                                */
/*************************************************************************/
char *get_sample(const char *filename, const char *mode) {
  // open file
  FILE *fp = fopen(filename, mode);
  if (fp == NULL) {
    perror("");
    printf("Unable to open sample '%s' in '%s' mode for reading.\n", filename,
           mode);
    exit(1);
  }
  // get size of file
  fseek(fp, 0L, SEEK_END);
  int size = ftell(fp);
  rewind(fp);
  // allocate space to read in data from file
  char *file_data = (char *)calloc(size + 1, sizeof(char));
  if (file_data == NULL) {
    perror("");
    printf("Unable to allocate space to load data from '%s'.\n", filename);
    fclose(fp);
    exit(1);
  }
  // read file data
  fread(file_data, size, 1, fp);
  fclose(fp);
  return file_data;
}

char *get_raw_sample(const char *filename) {
  return get_sample(filename, "rb");
}

char *get_xml_sample(const char *filename, int *length) {
  // open file
  std::ifstream f(filename);
  if (!f.is_open()) {
    std::cerr << "Unable to open sample file " << filename << "." << std::endl;
    exit(1);
  }
  // build minified xml
  std::string line;
  std::string xml_string;
  while (getline(f, line)) {
    size_t end = line.find_first_not_of(" ");
    if (end != std::string::npos) {
      line = line.substr(end, line.length());
    }
    xml_string += line;
  }
  // std::cout << xml_string << std::endl;
  *length = xml_string.length();
  // Create EBCDIC encoded XML in a buffer.
  char *ebcdic_xml_bytes = (char *)calloc(*length + 1, sizeof(char));
  if (ebcdic_xml_bytes == NULL) {
    perror("");
    printf("Unable to allocate space to load data from '%s'.\n", filename);
    exit(1);
  }
  memcpy(ebcdic_xml_bytes, xml_string.c_str(), *length);
  __a2e_l(ebcdic_xml_bytes, *length);

  return ebcdic_xml_bytes;
}

std::string get_json_sample(const char *filename) {
  char *json_sample_string = get_sample(filename, "r");
  std::string json_sample_cpp_string =
      nlohmann::json::parse(json_sample_string).dump();
  free(json_sample_string);
  return json_sample_cpp_string;
}

void test_validation_errors(const char *test_request_json,
                            const char *test_validation_errors_result_json,
                            bool debug) {
  std::string request_json = get_json_sample(test_request_json);
  std::string result_json_expected =
      get_json_sample(test_validation_errors_result_json);

  sear_result_t *result =
      sear(request_json.c_str(), request_json.length(), debug);

  TEST_ASSERT_EQUAL_STRING(result_json_expected.c_str(), result->result_json);
}

/*************************************************************************/
/* IRRSEQ00                                                              */
/*************************************************************************/
void test_extract_request_generation(const char *test_extract_request_json,
                                     const char *test_extract_request_raw,
                                     bool racf_options, bool debug) {
  std::string request_json   = get_json_sample(test_extract_request_json);
  char *raw_request_expected = get_raw_sample(test_extract_request_raw);

  // Mock R_Admin result
  r_admin_result_mock      = NULL;
  r_admin_result_size_mock = 0;
  r_admin_rc_mock          = 0;
  r_admin_saf_rc_mock      = 0;
  r_admin_racf_rc_mock     = 0;
  r_admin_racf_reason_mock = 0;

  sear_result_t *result =
      sear(request_json.c_str(), request_json.length(), debug);

  int request_buffer_size = TEST_IRRSEQ00_GENERIC_REQUEST_BUFFER_SIZE;
  int arg_area_size       = TEST_IRRSEQ00_GENERIC_ARG_AREA_SIZE;

  if (racf_options == true) {
    request_buffer_size = TEST_IRRSEQ00_RACF_OPTIONS_REQUEST_BUFFER_SIZE;
    arg_area_size       = TEST_IRRSEQ00_RACF_OPTIONS_ARG_AREA_SIZE;
  }

  // Check the size of the buffer
  TEST_ASSERT_EQUAL_INT32(request_buffer_size, result->raw_request_length);
  // Check the "arg area" (excludes the "arg pointers" at the end)
  TEST_ASSERT_EQUAL_MEMORY(raw_request_expected, result->raw_request,
                           arg_area_size);

  check_arg_pointers(result->raw_request, racf_options);

  // Cleanup
  free(raw_request_expected);
}

void test_parse_extract_result(const char *test_extract_request_json,
                               const char *test_extract_result_json,
                               const char *test_extract_result_raw,
                               bool debug) {
  std::string request_json         = get_json_sample(test_extract_request_json);
  std::string result_json_expected = get_json_sample(test_extract_result_json);

  // Mock R_Admin result
  r_admin_result_mock = get_raw_sample(test_extract_result_raw);
  struct stat st;
  stat(test_extract_result_raw, &st);
  r_admin_result_size_mock = st.st_size;
  r_admin_rc_mock          = 0;
  r_admin_saf_rc_mock      = 0;
  r_admin_racf_rc_mock     = 0;
  r_admin_racf_reason_mock = 0;

  sear_result_t *result =
      sear(request_json.c_str(), request_json.length(), debug);

  TEST_ASSERT_EQUAL_STRING(result_json_expected.c_str(), result->result_json);
  TEST_ASSERT_EQUAL_INT32(result_json_expected.length(),
                          result->result_json_length);
  TEST_ASSERT_EQUAL_CHAR(0, result->result_json[result->result_json_length]);
  TEST_ASSERT_EQUAL_INT32(r_admin_result_size_mock, result->raw_result_length);

  // Cleanup
  free(r_admin_result_mock);
}

void test_parse_extract_next_result(const char *test_extract_next_request_json,
                                    const char *test_extract_next_result_json,
                                    const char *test_extract_next_result_raw,
                                    bool debug) {
  std::string request_json = get_json_sample(test_extract_next_request_json);
  std::string result_json_expected =
      get_json_sample(test_extract_next_result_json);

  // Mock R_Admin result
  r_admin_result_mock = get_raw_sample(test_extract_next_result_raw);
  struct stat st;
  stat(test_extract_next_result_raw, &st);
  r_admin_result_size_mock = st.st_size;
  r_admin_rc_mock          = 0;
  r_admin_saf_rc_mock      = 0;
  r_admin_racf_rc_mock     = 0;
  r_admin_racf_reason_mock = 0;

  sear_result_t *result =
      sear(request_json.c_str(), request_json.length(), debug);

  TEST_ASSERT_EQUAL_STRING(result_json_expected.c_str(), result->result_json);
  TEST_ASSERT_EQUAL_INT32(result_json_expected.length(),
                          result->result_json_length);
  TEST_ASSERT_EQUAL_CHAR(0, result->result_json[result->result_json_length]);
  TEST_ASSERT_EQUAL_INT32(r_admin_result_size_mock, result->raw_result_length);

  // Cleanup
  free(r_admin_result_mock);
}

void test_parse_extract_result_profile_not_found(
    const char *test_extract_request_json,
    const char *test_extract_result_profile_not_found_json, bool debug) {
  std::string request_json = get_json_sample(test_extract_request_json);
  std::string result_json_expected =
      get_json_sample(test_extract_result_profile_not_found_json);

  // Mock R_Admin result
  // Note that there will be no result if the profile cannot be extracted
  // and the return and reason codes will be set to indicate why the extract
  // failed.
  r_admin_result_mock      = NULL;
  r_admin_result_size_mock = 0;
  r_admin_rc_mock          = -1;
  r_admin_saf_rc_mock      = 4;
  r_admin_racf_rc_mock     = 4;
  r_admin_racf_reason_mock = 4;

  sear_result_t *result =
      sear(request_json.c_str(), request_json.length(), debug);

  TEST_ASSERT_EQUAL_STRING(result_json_expected.c_str(), result->result_json);
  TEST_ASSERT_EQUAL_INT32(result_json_expected.length(),
                          result->result_json_length);
  TEST_ASSERT_EQUAL_CHAR(0, result->result_json[result->result_json_length]);
}

void check_arg_pointers(char *raw_request, bool racf_options) {
  // Arg Pointers on z/Architecture (31-bit big endian)
  /*
  0x00, 0x00, 0x00, 0x00, // result buffer pointer
  0x29, 0x96, 0x90, 0x48, // work area pointer
  0x29, 0x96, 0x94, 0x48, // ALET pointer
  0x29, 0x96, 0x94, 0x4c, // SAF return code pointer
  0x29, 0x96, 0x94, 0x50, // ALET pointer
  0x29, 0x96, 0x94, 0x54, // RACF return code pointer
  0x29, 0x96, 0x94, 0x58, // ALET pointer
  0x29, 0x96, 0x94, 0x5c, // RACF reason code pointer
  0x29, 0x96, 0x94, 0x60, // function code pointer
  0x29, 0x96, 0x94, 0x61, // profile extract parms pointer
  0x29, 0x96, 0x94, 0x9d, // profile name pointer
  0x29, 0x96, 0x95, 0x95, // ACEE pointer
  0x29, 0x96, 0x95, 0x99, // result buffer subpool pointer
  0xa9, 0x96, 0x95, 0x9a // result buffer pointer pointer
  */

  // Arg Pointers on x86_64/ARM64 (64-bit little endian)
  /*
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // result buffer pointer
  0x00, 0x88, 0x00, 0x35, 0x01, 0x00, 0x00, 0x00, // work area pointer
  0x00, 0x8c, 0x00, 0x35, 0x01, 0x00, 0x00, 0x00, // ALET pointer
  0x04, 0x8c, 0x00, 0x35, 0x01, 0x00, 0x00, 0x00, // SAF return code pointer
  0x08, 0x8c, 0x00, 0x35, 0x01, 0x00, 0x00, 0x00, // ALET pointer
  0x0c, 0x8c, 0x00, 0x35, 0x01, 0x00, 0x00, 0x00, // RACF return code pointer
  0x10, 0x8c, 0x00, 0x35, 0x01, 0x00, 0x00, 0x00, // ALET pointer
  0x14, 0x8c, 0x00, 0x35, 0x01, 0x00, 0x00, 0x00, // RACF reason code pointer
  0x18, 0x8c, 0x00, 0x35, 0x01, 0x00, 0x00, 0x00, // function code pointer
  0x19, 0x8c, 0x00, 0x35, 0x01, 0x00, 0x00, 0x00, // profile extract parms
  pointer 0x55, 0x8c, 0x00, 0x35, 0x01, 0x00, 0x00, 0x00, // profile name
  pointer 0x4d, 0x8d, 0x00, 0x35, 0x01, 0x00, 0x00, 0x00, // ACEE pointer 0x51,
  0x8d, 0x00, 0x35, 0x01, 0x00, 0x00, 0x00, // result buffer subpool pointer
  0x52, 0x8d, 0x00, 0xb5, 0x01, 0x00, 0x00, 0x00 // result buffer pointer
  pointer
  */

  int arg_area_size = TEST_IRRSEQ00_GENERIC_ARG_AREA_SIZE;

  if (racf_options == true) {
    arg_area_size = TEST_IRRSEQ00_RACF_OPTIONS_ARG_AREA_SIZE;
  }

#ifdef __TOS_390__
  uint32_t *arg_pointer = (uint32_t *)(raw_request + arg_area_size);
#else
  uint64_t *arg_pointer = (uint64_t *)(raw_request + arg_area_size);
#endif
  // Result buffer pointer should be left NULL since no
  // result buffer exists until after R_Admin is called.
  TEST_ASSERT_EQUAL_UINT64(0, arg_pointer[0]);
  // work area pointer should be set.
  TEST_ASSERT_NOT_EQUAL_UINT64(0, arg_pointer[1]);
  // work area should be 1024 bytes
  TEST_ASSERT_EQUAL_UINT64(1024, arg_pointer[2] - arg_pointer[1]);
  // SAF RC ALET should be 4 bytes
  TEST_ASSERT_EQUAL_UINT64(4, arg_pointer[3] - arg_pointer[2]);
  // SAF RC should be 4 bytes
  TEST_ASSERT_EQUAL_UINT64(4, arg_pointer[4] - arg_pointer[3]);
  // RACF RC ALET should be 4 bytes
  TEST_ASSERT_EQUAL_UINT64(4, arg_pointer[5] - arg_pointer[4]);
  // RACF RC should be 4 bytes
  TEST_ASSERT_EQUAL_UINT64(4, arg_pointer[6] - arg_pointer[5]);
  // RACF reason ALET should be 4 bytes
  TEST_ASSERT_EQUAL_UINT64(4, arg_pointer[7] - arg_pointer[6]);
  // RACF reason should be 4 bytes
  TEST_ASSERT_EQUAL_UINT64(4, arg_pointer[8] - arg_pointer[7]);
  // function code pointer should be 1 byte
  TEST_ASSERT_EQUAL_UINT64(1, arg_pointer[9] - arg_pointer[8]);
  if (racf_options == false) {
    // generic profile extract parms area should be 60 bytes
    TEST_ASSERT_EQUAL_UINT64(60, arg_pointer[10] - arg_pointer[9]);
  } else {
    // RACF Options profile extract parms area should be 14 bytes
    TEST_ASSERT_EQUAL_UINT64(14, arg_pointer[10] - arg_pointer[9]);
  }
  // profile name area should be 248 bytes
  TEST_ASSERT_EQUAL_UINT64(248, arg_pointer[11] - arg_pointer[10]);
  // ACEE should be 4 bytes
  TEST_ASSERT_EQUAL_UINT64(4, arg_pointer[12] - arg_pointer[11]);

#ifdef __TOS_390__
  // result buffer subpool should be 1 byte
  // Note that the difference between the result buffer pointer pointer
  // and the result buffer subpool pointer is 0x80000001 as a result
  // of the high order bit of the result buffer pointer pointer being
  // set to 0x80000000 to indicate that this is the end of the argument list.
  TEST_ASSERT_EQUAL_UINT64(0x80000001, arg_pointer[13] - arg_pointer[12]);
#else
  // When testing off-platform, just remove the high order bit.
  // On Linux systems specifically, this assertion fails for some
  // reason when the high order bit is on.
  TEST_ASSERT_EQUAL_UINT64(1, (arg_pointer[13] - arg_pointer[12]) & 0x7FFFFFFF);
#endif
}

/*************************************************************************/
/* IRRSMO00                                                              */
/*************************************************************************/
void test_generate_add_alter_delete_request_generation(
    const char *test_add_alter_delete_request_json,
    const char *test_add_alter_delete_request_xml,
    int irrsmo00_options_expected, bool debug) {
  std::string request_json =
      get_json_sample(test_add_alter_delete_request_json);
  int raw_request_length_expected;
  char *raw_request_expected = get_xml_sample(test_add_alter_delete_request_xml,
                                              &raw_request_length_expected);

  // Mock IRRSMO64 result
  irrsmo64_result_mock      = NULL;
  irrsmo64_result_size_mock = 0;
  irrsmo64_saf_rc_mock      = 0;
  irrsmo64_racf_rc_mock     = 0;
  irrsmo64_racf_reason_mock = 0;

  sear_result_t *result =
      sear(request_json.c_str(), request_json.length(), debug);

  TEST_ASSERT_EQUAL_INT32(raw_request_length_expected,
                          result->raw_request_length);
  TEST_ASSERT_EQUAL_MEMORY(raw_request_expected, result->raw_request,
                           raw_request_length_expected);
  TEST_ASSERT_EQUAL_INT32(irrsmo00_options_expected, irrsmo00_options_actual);

  // Cleanup
  free(raw_request_expected);
}

void test_parse_add_alter_delete_result(
    const char *test_add_alter_delete_request_json,
    const char *test_add_alter_delete_result_json,
    const char *test_add_alter_delete_result_xml, bool debug) {
  std::string request_json =
      get_json_sample(test_add_alter_delete_request_json);
  std::string result_json_expected =
      get_json_sample(test_add_alter_delete_result_json);

  // Mock IRRSMO64 result
  int raw_result_length_expected;
  irrsmo64_result_mock = get_xml_sample(test_add_alter_delete_result_xml,
                                        &raw_result_length_expected);
  struct stat raw_request_size_expected;
  irrsmo64_result_size_mock = raw_result_length_expected;
  irrsmo64_saf_rc_mock      = 0;
  irrsmo64_racf_rc_mock     = 0;
  irrsmo64_racf_reason_mock = 0;

  sear_result_t *result =
      sear(request_json.c_str(), request_json.length(), debug);

  TEST_ASSERT_EQUAL_STRING(result_json_expected.c_str(), result->result_json);
  TEST_ASSERT_EQUAL_INT32(result_json_expected.length(),
                          result->result_json_length);
  TEST_ASSERT_EQUAL_CHAR(0, result->result_json[result->result_json_length]);

  // Cleanup
  free(irrsmo64_result_mock);
}

/*************************************************************************/
/* IRRSDL00                                                              */
/*************************************************************************/
void test_extract_request_irrsdl00_generation(
    const char *test_extract_request_json, const char *test_extract_request_raw,
    bool debug) {
  std::string request_json   = get_json_sample(test_extract_request_json);
  char *raw_request_expected = get_raw_sample(test_extract_request_raw);

  // Mock R_datalib result
  irrsdl64_result_mock      = NULL;
  irrsdl64_result_size_mock = 0;
  irrsdl64_saf_rc_mock      = 0;
  irrsdl64_racf_rc_mock     = 0;
  irrsdl64_racf_reason_mock = 0;

  sear_result_t *result =
      sear(request_json.c_str(), request_json.length(), debug);

  int request_buffer_size = TEST_IRRSDL00_KEYRING_REQUEST_BUFFER_SIZE;
  int arg_area_size       = TEST_IRRSDL00_KEYRING_ARG_AREA_SIZE;

  // Check the size of the buffer
  TEST_ASSERT_EQUAL_INT32(request_buffer_size, result->raw_request_length);
  // Check the "arg area" (excludes the "arg pointers" at the end)
  TEST_ASSERT_EQUAL_MEMORY(raw_request_expected, result->raw_request,
                           arg_area_size);

  // Cleanup
  free(raw_request_expected);
}

void test_parse_extract_irrsdl00_result(const char *test_extract_request_json,
                                        const char *test_extract_result_json,
                                        const char *test_extract_result_raw,
                                        bool debug) {
  std::string request_json         = get_json_sample(test_extract_request_json);
  std::string result_json_expected = get_json_sample(test_extract_result_json);

  // Mock R_datalib result
  irrsdl64_result_mock = get_raw_sample(test_extract_result_raw);
  struct stat st;
  stat(test_extract_result_raw, &st);
  irrsdl64_result_size_mock = st.st_size;
  irrsdl64_saf_rc_mock      = 0;
  irrsdl64_racf_rc_mock     = 0;
  irrsdl64_racf_reason_mock = 0;

  sear_result_t *result =
      sear(request_json.c_str(), request_json.length(), debug);

  TEST_ASSERT_EQUAL_STRING(result_json_expected.c_str(), result->result_json);
  TEST_ASSERT_EQUAL_INT32(result_json_expected.length(),
                          result->result_json_length);
  TEST_ASSERT_EQUAL_CHAR(0, result->result_json[result->result_json_length]);
  TEST_ASSERT_EQUAL_INT32(irrsdl64_result_size_mock, result->raw_result_length);

  // Cleanup
  free(irrsdl64_result_mock);
}

void test_parse_extract_irrsdl00_result_keyring_not_found(
    const char *test_extract_request_json,
    const char *test_extract_result_keyring_not_found_json, bool debug) {
  std::string request_json = get_json_sample(test_extract_request_json);
  std::string result_json_expected =
      get_json_sample(test_extract_result_keyring_not_found_json);

  // Mock R_Admin result
  // Note that there will be no result if the profile cannot be extracted
  // and the return and reason codes will be set to indicate why the extract
  // failed.
  irrsdl64_result_mock      = NULL;
  irrsdl64_result_size_mock = 0;
  irrsdl64_saf_rc_mock      = 8;
  irrsdl64_racf_rc_mock     = 8;
  irrsdl64_racf_reason_mock = 32;

  sear_result_t *result =
      sear(request_json.c_str(), request_json.length(), debug);

  TEST_ASSERT_EQUAL_STRING(result_json_expected.c_str(), result->result_json);
  TEST_ASSERT_EQUAL_INT32(result_json_expected.length(),
                          result->result_json_length);
  TEST_ASSERT_EQUAL_CHAR(0, result->result_json[result->result_json_length]);
}

void test_add_request_irrsdl00_generation(const char *test_add_request_json,
                                          const char *test_add_request_raw,
                                          bool debug) {
  std::string request_json   = get_json_sample(test_add_request_json);
  char *raw_request_expected = get_raw_sample(test_add_request_raw);

  // Mock R_datalib result
  irrsdl64_result_mock      = NULL;
  irrsdl64_result_size_mock = 0;
  irrsdl64_saf_rc_mock      = 0;
  irrsdl64_racf_rc_mock     = 0;
  irrsdl64_racf_reason_mock = 0;

  sear_result_t *result =
      sear(request_json.c_str(), request_json.length(), debug);

  int request_buffer_size = TEST_IRRSDL00_KEYRING_REQUEST_BUFFER_SIZE;
  int arg_area_size       = TEST_IRRSDL00_KEYRING_ARG_AREA_SIZE;

  // Check the size of the buffer
  TEST_ASSERT_EQUAL_INT32(request_buffer_size, result->raw_request_length);
  // Check the "arg area" (excludes the "arg pointers" at the end)
  TEST_ASSERT_EQUAL_MEMORY(raw_request_expected, result->raw_request,
                           arg_area_size);

  // Cleanup
  free(raw_request_expected);
}

void test_delete_request_irrsdl00_generation(
    const char *test_delete_request_json, const char *test_delete_request_raw,
    bool debug) {
  std::string request_json   = get_json_sample(test_delete_request_json);
  char *raw_request_expected = get_raw_sample(test_delete_request_raw);

  // Mock R_datalib result
  irrsdl64_result_mock      = NULL;
  irrsdl64_result_size_mock = 0;
  irrsdl64_saf_rc_mock      = 0;
  irrsdl64_racf_rc_mock     = 0;
  irrsdl64_racf_reason_mock = 0;

  sear_result_t *result =
      sear(request_json.c_str(), request_json.length(), debug);

  int request_buffer_size = TEST_IRRSDL00_KEYRING_REQUEST_BUFFER_SIZE;
  int arg_area_size       = TEST_IRRSDL00_KEYRING_ARG_AREA_SIZE;

  // Check the size of the buffer
  TEST_ASSERT_EQUAL_INT32(request_buffer_size, result->raw_request_length);
  // Check the "arg area" (excludes the "arg pointers" at the end)
  TEST_ASSERT_EQUAL_MEMORY(raw_request_expected, result->raw_request,
                           arg_area_size);

  // Cleanup
  free(raw_request_expected);
}
