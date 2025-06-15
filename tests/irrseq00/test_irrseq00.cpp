#include "tests/irrseq00/test_irrseq00.hpp"

#include <arpa/inet.h>
#include <sys/stat.h>

#include <cstring>

#include "tests/unit_test_utilities.hpp"

/*************************************************************************/
/* User                                                                  */
/*************************************************************************/
void test_generate_extract_user_request() {
  test_extract_request_generation(TEST_EXTRACT_USER_REQUEST_JSON,
                                  TEST_EXTRACT_USER_REQUEST_RAW, false, false);
}

void test_generate_extract_user_request_lowercase_userid() {
  test_extract_request_generation(
      TEST_EXTRACT_USER_REQUEST_LOWERCASE_USERID_JSON,
      TEST_EXTRACT_USER_REQUEST_RAW, false, false);
}

void test_parse_extract_user_result() {
  test_parse_extract_result(TEST_EXTRACT_USER_REQUEST_JSON,
                            TEST_EXTRACT_USER_RESULT_JSON,
                            TEST_EXTRACT_USER_RESULT_RAW, false);
}

void test_parse_extract_user_result_csdata() {
  test_parse_extract_result(TEST_EXTRACT_USER_REQUEST_JSON,
                            TEST_EXTRACT_USER_RESULT_CSDATA_JSON,
                            TEST_EXTRACT_USER_RESULT_CSDATA_RAW, false);
}

void test_parse_extract_user_result_user_not_found() {
  test_parse_extract_result_profile_not_found(
      TEST_EXTRACT_USER_REQUEST_JSON,
      TEST_EXTRACT_USER_RESULT_USER_NOT_FOUND_JSON, false);
}

void test_parse_extract_user_result_required_parameter_missing() {
  test_validation_errors(
      TEST_EXTRACT_USER_REQUEST_REQUIRED_PARAMETER_MISSING_JSON,
      TEST_PARAMETER_VALIDATION_ERROR_RESULT_JSON, false);
}

void test_parse_extract_user_result_extraneous_parameter_provided() {
  test_validation_errors(
      TEST_EXTRACT_USER_REQUEST_EXTRANEOUS_PARAMETER_PROVIDED_JSON,
      TEST_PARAMETER_VALIDATION_ERROR_RESULT_JSON, false);
}

void test_parse_extract_user_result_pseudo_boolean() {
  test_parse_extract_result(TEST_EXTRACT_USER_REQUEST_JSON,
                            TEST_EXTRACT_USER_RESULT_PSEUDO_BOOLEAN_JSON,
                            TEST_EXTRACT_USER_RESULT_PSEUDO_BOOLEAN_RAW, false);
}

void test_generate_extract_next_user_request() {
  test_extract_request_generation(TEST_EXTRACT_NEXT_USER_REQUEST_JSON,
                                  TEST_EXTRACT_NEXT_USER_REQUEST_RAW, false,
                                  false);
}

void test_parse_extract_next_user_result() {
  test_parse_extract_next_result(TEST_EXTRACT_NEXT_USER_REQUEST_JSON,
                                 TEST_EXTRACT_NEXT_USER_RESULT_JSON,
                                 TEST_EXTRACT_NEXT_USER_RESULT_RAW, false);
}

/*************************************************************************/
/* Group                                                                 */
/*************************************************************************/
void test_generate_extract_group_request() {
  test_extract_request_generation(TEST_EXTRACT_GROUP_REQUEST_JSON,
                                  TEST_EXTRACT_GROUP_REQUEST_RAW, false, false);
}

void test_parse_extract_group_result() {
  test_parse_extract_result(TEST_EXTRACT_GROUP_REQUEST_JSON,
                            TEST_EXTRACT_GROUP_RESULT_JSON,
                            TEST_EXTRACT_GROUP_RESULT_RAW, false);
}

void test_parse_extract_group_result_csdata() {
  test_parse_extract_result(TEST_EXTRACT_GROUP_REQUEST_JSON,
                            TEST_EXTRACT_GROUP_RESULT_CSDATA_JSON,
                            TEST_EXTRACT_GROUP_RESULT_CSDATA_RAW, false);
}

void test_parse_extract_group_result_group_not_found() {
  test_parse_extract_result_profile_not_found(
      TEST_EXTRACT_GROUP_REQUEST_JSON,
      TEST_EXTRACT_GROUP_RESULT_GROUP_NOT_FOUND_JSON, false);
}

void test_parse_extract_group_result_required_parameter_missing() {
  test_validation_errors(
      TEST_EXTRACT_GROUP_REQUEST_REQUIRED_PARAMETER_MISSING_JSON,
      TEST_PARAMETER_VALIDATION_ERROR_RESULT_JSON, false);
}

void test_parse_extract_group_result_extraneous_parameter_provided() {
  test_validation_errors(
      TEST_EXTRACT_GROUP_REQUEST_EXTRANEOUS_PARAMETER_PROVIDED_JSON,
      TEST_PARAMETER_VALIDATION_ERROR_RESULT_JSON, false);
}

void test_generate_extract_next_group_request() {
  test_extract_request_generation(TEST_EXTRACT_NEXT_GROUP_REQUEST_JSON,
                                  TEST_EXTRACT_NEXT_GROUP_REQUEST_RAW, false,
                                  false);
}

void test_parse_extract_next_group_result() {
  test_parse_extract_next_result(TEST_EXTRACT_NEXT_GROUP_REQUEST_JSON,
                                 TEST_EXTRACT_NEXT_GROUP_RESULT_JSON,
                                 TEST_EXTRACT_NEXT_GROUP_RESULT_RAW, false);
}

/*************************************************************************/
/* Group Connection                                                      */
/*************************************************************************/
void test_generate_extract_group_connection_request() {
  test_extract_request_generation(TEST_EXTRACT_GROUP_CONNECTION_REQUEST_JSON,
                                  TEST_EXTRACT_GROUP_CONNECTION_REQUEST_RAW,
                                  false, false);
}

void test_parse_extract_group_connection_result() {
  test_parse_extract_result(TEST_EXTRACT_GROUP_CONNECTION_REQUEST_JSON,
                            TEST_EXTRACT_GROUP_CONNECTION_RESULT_JSON,
                            TEST_EXTRACT_GROUP_CONNECTION_RESULT_RAW, false);
}

void test_parse_extract_group_connection_result_group_connection_not_found() {
  test_parse_extract_result_profile_not_found(
      TEST_EXTRACT_GROUP_CONNECTION_REQUEST_JSON,
      TEST_EXTRACT_GROUP_CONNECTION_RESULT_GROUP_CONNECTION_NOT_FOUND_JSON,
      false);
}

void test_parse_extract_group_connection_result_required_parameter_missing() {
  test_validation_errors(
      TEST_EXTRACT_GROUP_CONNECTION_REQUEST_REQUIRED_PARAMETER_MISSING_JSON,
      TEST_PARAMETER_VALIDATION_ERROR_RESULT_JSON, false);
}

void test_parse_extract_group_connection_result_extraneous_parameter_provided() {
  test_validation_errors(
      TEST_EXTRACT_GROUP_CONNECTION_REQUEST_EXTRANEOUS_PARAMETER_PROVIDED_JSON,
      TEST_PARAMETER_VALIDATION_ERROR_RESULT_JSON, false);
}

/*************************************************************************/
/* RACF Options                                                          */
/*************************************************************************/
void test_generate_extract_racf_options_request() {
  test_extract_request_generation(TEST_EXTRACT_RACF_OPTIONS_REQUEST_JSON,
                                  TEST_EXTRACT_RACF_OPTIONS_REQUEST_RAW, true,
                                  false);
}

void test_parse_extract_racf_options_result() {
  test_parse_extract_result(TEST_EXTRACT_RACF_OPTIONS_REQUEST_JSON,
                            TEST_EXTRACT_RACF_OPTIONS_RESULT_JSON,
                            TEST_EXTRACT_RACF_OPTIONS_RESULT_RAW, false);
}

void test_parse_extract_racf_options_result_racf_options_not_found() {
  // This would technically never fail this way, but this tests
  // the code paths for handling an error with RACF Options extract.
  test_parse_extract_result_profile_not_found(
      TEST_EXTRACT_RACF_OPTIONS_REQUEST_JSON,
      TEST_EXTRACT_RACF_OPTIONS_RESULT_RACF_OPTIONS_NOT_FOUND_JSON, false);
}

void test_parse_extract_racf_options_result_extraneous_parameter_provided() {
  test_validation_errors(
      TEST_EXTRACT_RACF_OPTIONS_REQUEST_EXTRANEOUS_PARAMETER_PROVIDED_JSON,
      TEST_PARAMETER_VALIDATION_ERROR_RESULT_JSON, false);
}

/*************************************************************************/
/* Data Set                                                              */
/*************************************************************************/
void test_generate_extract_dataset_request() {
  test_extract_request_generation(TEST_EXTRACT_DATASET_REQUEST_JSON,
                                  TEST_EXTRACT_DATASET_REQUEST_RAW, false,
                                  false);
}

void test_parse_extract_dataset_result() {
  test_parse_extract_result(TEST_EXTRACT_DATASET_REQUEST_JSON,
                            TEST_EXTRACT_DATASET_RESULT_JSON,
                            TEST_EXTRACT_DATASET_RESULT_RAW, false);
}

void test_parse_extract_dataset_result_csdata() {
  test_parse_extract_result(TEST_EXTRACT_DATASET_REQUEST_JSON,
                            TEST_EXTRACT_DATASET_RESULT_CSDATA_JSON,
                            TEST_EXTRACT_DATASET_RESULT_CSDATA_RAW, false);
}

void test_parse_extract_dataset_result_dataset_not_found() {
  test_parse_extract_result_profile_not_found(
      TEST_EXTRACT_DATASET_REQUEST_JSON,
      TEST_EXTRACT_DATASET_RESULT_DATASET_NOT_FOUND_JSON, false);
}

void test_parse_extract_dataset_result_required_parameter_missing() {
  test_validation_errors(
      TEST_EXTRACT_DATASET_REQUEST_REQUIRED_PARAMETER_MISSING_JSON,
      TEST_PARAMETER_VALIDATION_ERROR_RESULT_JSON, false);
}

void test_parse_extract_dataset_result_extraneous_parameter_provided() {
  test_validation_errors(
      TEST_EXTRACT_DATASET_REQUEST_EXTRANEOUS_PARAMETER_PROVIDED_JSON,
      TEST_PARAMETER_VALIDATION_ERROR_RESULT_JSON, false);
}

void test_generate_extract_next_dataset_request() {
  test_extract_request_generation(TEST_EXTRACT_NEXT_DATASET_REQUEST_JSON,
                                  TEST_EXTRACT_NEXT_DATASET_REQUEST_RAW, false,
                                  false);
}

void test_parse_extract_next_dataset_result() {
  test_parse_extract_next_result(TEST_EXTRACT_NEXT_DATASET_REQUEST_JSON,
                                 TEST_EXTRACT_NEXT_DATASET_RESULT_JSON,
                                 TEST_EXTRACT_NEXT_DATASET_RESULT_RAW, false);
}

/*************************************************************************/
/* Resource                                                              */
/*************************************************************************/
void test_generate_extract_resource_request() {
  test_extract_request_generation(TEST_EXTRACT_RESOURCE_REQUEST_JSON,
                                  TEST_EXTRACT_RESOURCE_REQUEST_RAW, false,
                                  false);
}

void test_generate_extract_resource_request_lowercase_resource_name_and_class_name() {
  test_extract_request_generation(
      TEST_EXTRACT_RESOURCE_REQUEST_LOWERCASE_RESOURCE_NAME_AND_CLASS_NAME_JSON,
      TEST_EXTRACT_RESOURCE_REQUEST_RAW, false, false);
}

void test_parse_extract_resource_result() {
  test_parse_extract_result(TEST_EXTRACT_RESOURCE_REQUEST_JSON,
                            TEST_EXTRACT_RESOURCE_RESULT_JSON,
                            TEST_EXTRACT_RESOURCE_RESULT_RAW, false);
}

void test_parse_extract_resource_result_csdata() {
  test_parse_extract_result(TEST_EXTRACT_RESOURCE_REQUEST_JSON,
                            TEST_EXTRACT_RESOURCE_RESULT_CSDATA_JSON,
                            TEST_EXTRACT_RESOURCE_RESULT_CSDATA_RAW, false);
}

void test_parse_extract_resource_result_resource_not_found() {
  test_parse_extract_result_profile_not_found(
      TEST_EXTRACT_RESOURCE_REQUEST_JSON,
      TEST_EXTRACT_RESOURCE_RESULT_RESOURCE_NOT_FOUND_JSON, false);
}

void test_parse_extract_resource_result_required_parameter_missing() {
  test_validation_errors(
      TEST_EXTRACT_RESOURCE_REQUEST_REQUIRED_PARAMETER_MISSING_JSON,
      TEST_PARAMETER_VALIDATION_ERROR_RESULT_JSON, false);
}

void test_parse_extract_resource_result_extraneous_parameter_provided() {
  test_validation_errors(
      TEST_EXTRACT_RESOURCE_REQUEST_EXTRANEOUS_PARAMETER_PROVIDED_JSON,
      TEST_PARAMETER_VALIDATION_ERROR_RESULT_JSON, false);
}

void test_generate_extract_next_resource_request() {
  test_extract_request_generation(TEST_EXTRACT_NEXT_RESOURCE_REQUEST_JSON,
                                  TEST_EXTRACT_NEXT_RESOURCE_REQUEST_RAW, false,
                                  false);
}

void test_parse_extract_next_resource_result() {
  test_parse_extract_next_result(TEST_EXTRACT_NEXT_RESOURCE_REQUEST_JSON,
                                 TEST_EXTRACT_NEXT_RESOURCE_RESULT_JSON,
                                 TEST_EXTRACT_NEXT_RESOURCE_RESULT_RAW, false);
}
