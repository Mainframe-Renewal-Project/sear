#ifndef __SEAR_TEST_EXTRACT_H_
#define __SEAR_TEST_EXTRACT_H_

#define IRRSEQ00_REQUEST_SAMPLES "./tests/irrseq00/request_samples/"
#define IRRSEQ00_RESULT_SAMPLES "./tests/irrseq00/result_samples/"

/*************************************************************************/
/* Request Samples                                                       */
/*************************************************************************/
// User
#define TEST_EXTRACT_USER_REQUEST_JSON \
  IRRSEQ00_REQUEST_SAMPLES "user/test_extract_user_request.json"
#define TEST_EXTRACT_USER_REQUEST_LOWERCASE_USERID_JSON \
  IRRSEQ00_REQUEST_SAMPLES                              \
  "user/test_extract_user_request_lowercase_userid.json"
#define TEST_EXTRACT_USER_REQUEST_RAW \
  IRRSEQ00_REQUEST_SAMPLES "user/test_extract_user_request.bin"
#define TEST_EXTRACT_USER_REQUEST_REQUIRED_PARAMETER_MISSING_JSON \
  IRRSEQ00_REQUEST_SAMPLES                                        \
  "user/test_extract_user_request_required_parameter_missing.json"
#define TEST_EXTRACT_USER_REQUEST_EXTRANEOUS_PARAMETER_PROVIDED_JSON \
  IRRSEQ00_REQUEST_SAMPLES                                           \
  "user/test_extract_user_request_extraneous_parameter_provided.json"

#define TEST_EXTRACT_NEXT_USER_REQUEST_JSON \
  IRRSEQ00_REQUEST_SAMPLES "user/test_extract_next_user_request.json"
#define TEST_EXTRACT_NEXT_USER_REQUEST_RAW \
  IRRSEQ00_REQUEST_SAMPLES "user/test_extract_next_user_request.bin"

// Group
#define TEST_EXTRACT_GROUP_REQUEST_JSON \
  IRRSEQ00_REQUEST_SAMPLES "group/test_extract_group_request.json"
#define TEST_EXTRACT_GROUP_REQUEST_RAW \
  IRRSEQ00_REQUEST_SAMPLES "group/test_extract_group_request.bin"
#define TEST_EXTRACT_GROUP_REQUEST_REQUIRED_PARAMETER_MISSING_JSON \
  IRRSEQ00_REQUEST_SAMPLES                                         \
  "group/test_extract_group_request_required_parameter_missing.json"
#define TEST_EXTRACT_GROUP_REQUEST_EXTRANEOUS_PARAMETER_PROVIDED_JSON \
  IRRSEQ00_REQUEST_SAMPLES                                            \
  "group/test_extract_group_request_extraneous_parameter_provided.json"

#define TEST_EXTRACT_NEXT_GROUP_REQUEST_JSON \
  IRRSEQ00_REQUEST_SAMPLES "group/test_extract_next_group_request.json"
#define TEST_EXTRACT_NEXT_GROUP_REQUEST_RAW \
  IRRSEQ00_REQUEST_SAMPLES "group/test_extract_next_group_request.bin"

// Group Connection
#define TEST_EXTRACT_GROUP_CONNECTION_REQUEST_JSON \
  IRRSEQ00_REQUEST_SAMPLES                         \
  "group_connection/test_extract_group_connection_request.json"
#define TEST_EXTRACT_GROUP_CONNECTION_REQUEST_RAW \
  IRRSEQ00_REQUEST_SAMPLES                        \
  "group_connection/test_extract_group_connection_request.bin"
#define TEST_EXTRACT_GROUP_CONNECTION_REQUEST_REQUIRED_PARAMETER_MISSING_JSON \
  IRRSEQ00_REQUEST_SAMPLES                                                    \
  "group_connection/"                                                         \
  "test_extract_group_connection_request_required_parameter_missing.json"
#define TEST_EXTRACT_GROUP_CONNECTION_REQUEST_EXTRANEOUS_PARAMETER_PROVIDED_JSON \
  IRRSEQ00_REQUEST_SAMPLES                                                       \
  "group_connection/"                                                            \
  "test_extract_group_connection_request_extraneous_parameter_provided.json"

// RACF Options
#define TEST_EXTRACT_RACF_OPTIONS_REQUEST_JSON \
  IRRSEQ00_REQUEST_SAMPLES                     \
  "racf_options/test_extract_racf_options_request.json"
#define TEST_EXTRACT_RACF_OPTIONS_REQUEST_RAW \
  IRRSEQ00_REQUEST_SAMPLES                    \
  "racf_options/test_extract_racf_options_request.bin"
#define TEST_EXTRACT_RACF_OPTIONS_REQUEST_EXTRANEOUS_PARAMETER_PROVIDED_JSON \
  IRRSEQ00_REQUEST_SAMPLES                                                   \
  "racf_options/"                                                            \
  "test_extract_racf_options_request_extraneous_parameter_provided.json"

// Data Set
#define TEST_EXTRACT_DATASET_REQUEST_JSON \
  IRRSEQ00_REQUEST_SAMPLES "dataset/test_extract_dataset_request.json"
#define TEST_EXTRACT_DATASET_REQUEST_RAW \
  IRRSEQ00_REQUEST_SAMPLES "dataset/test_extract_dataset_request.bin"
#define TEST_EXTRACT_DATASET_REQUEST_REQUIRED_PARAMETER_MISSING_JSON \
  IRRSEQ00_REQUEST_SAMPLES                                           \
  "dataset/test_extract_dataset_request_required_parameter_missing.json"
#define TEST_EXTRACT_DATASET_REQUEST_EXTRANEOUS_PARAMETER_PROVIDED_JSON \
  IRRSEQ00_REQUEST_SAMPLES                                              \
  "dataset/test_extract_dataset_request_extraneous_parameter_provided.json"

#define TEST_EXTRACT_NEXT_DATASET_REQUEST_JSON \
  IRRSEQ00_REQUEST_SAMPLES "dataset/test_extract_next_dataset_request.json"
#define TEST_EXTRACT_NEXT_DATASET_REQUEST_RAW \
  IRRSEQ00_REQUEST_SAMPLES "dataset/test_extract_next_dataset_request.bin"

// Resource
#define TEST_EXTRACT_RESOURCE_REQUEST_JSON \
  IRRSEQ00_REQUEST_SAMPLES "resource/test_extract_resource_request.json"
#define TEST_EXTRACT_RESOURCE_REQUEST_LOWERCASE_RESOURCE_NAME_AND_CLASS_NAME_JSON \
  IRRSEQ00_REQUEST_SAMPLES                                                        \
  "resource/"                                                                     \
  "test_extract_resource_request_lowercase_resource_name_and_class_name.json"
#define TEST_EXTRACT_RESOURCE_REQUEST_RAW \
  IRRSEQ00_REQUEST_SAMPLES "resource/test_extract_resource_request.bin"
#define TEST_EXTRACT_RESOURCE_REQUEST_REQUIRED_PARAMETER_MISSING_JSON \
  IRRSEQ00_REQUEST_SAMPLES                                            \
  "resource/test_extract_resource_request_required_parameter_missing.json"
#define TEST_EXTRACT_RESOURCE_REQUEST_EXTRANEOUS_PARAMETER_PROVIDED_JSON \
  IRRSEQ00_REQUEST_SAMPLES                                               \
  "resource/test_extract_resource_request_extraneous_parameter_provided.json"

#define TEST_EXTRACT_NEXT_RESOURCE_REQUEST_JSON \
  IRRSEQ00_REQUEST_SAMPLES "resource/test_extract_next_resource_request.json"
#define TEST_EXTRACT_NEXT_RESOURCE_REQUEST_RAW \
  IRRSEQ00_REQUEST_SAMPLES "resource/test_extract_next_resource_request.bin"

/*************************************************************************/
/* Result Samples                                                        */
/*************************************************************************/
// User
#define TEST_EXTRACT_USER_RESULT_JSON \
  IRRSEQ00_RESULT_SAMPLES "user/test_extract_user_result.json"
#define TEST_EXTRACT_USER_RESULT_RAW \
  IRRSEQ00_RESULT_SAMPLES "user/test_extract_user_result.bin"
#define TEST_EXTRACT_USER_RESULT_CSDATA_JSON \
  IRRSEQ00_RESULT_SAMPLES "user/test_extract_user_result_csdata.json"
#define TEST_EXTRACT_USER_RESULT_CSDATA_RAW \
  IRRSEQ00_RESULT_SAMPLES "user/test_extract_user_result_csdata.bin"
#define TEST_EXTRACT_USER_RESULT_USER_NOT_FOUND_JSON \
  IRRSEQ00_RESULT_SAMPLES                            \
  "user/test_extract_user_result_user_not_found.json"
#define TEST_EXTRACT_USER_RESULT_PSEUDO_BOOLEAN_JSON \
  IRRSEQ00_RESULT_SAMPLES "user/test_extract_user_result_pseudo_boolean.json"
#define TEST_EXTRACT_USER_RESULT_PSEUDO_BOOLEAN_RAW \
  IRRSEQ00_RESULT_SAMPLES "user/test_extract_user_result_pseudo_boolean.bin"

#define TEST_EXTRACT_NEXT_USER_RESULT_JSON \
  IRRSEQ00_RESULT_SAMPLES "user/test_extract_next_user_result.json"
#define TEST_EXTRACT_NEXT_USER_RESULT_RAW \
  IRRSEQ00_RESULT_SAMPLES "user/test_extract_next_user_result.bin"

// Group
#define TEST_EXTRACT_GROUP_RESULT_JSON \
  IRRSEQ00_RESULT_SAMPLES "group/test_extract_group_result.json"
#define TEST_EXTRACT_GROUP_RESULT_RAW \
  IRRSEQ00_RESULT_SAMPLES "group/test_extract_group_result.bin"
#define TEST_EXTRACT_GROUP_RESULT_CSDATA_JSON \
  IRRSEQ00_RESULT_SAMPLES "group/test_extract_group_result_csdata.json"
#define TEST_EXTRACT_GROUP_RESULT_CSDATA_RAW \
  IRRSEQ00_RESULT_SAMPLES "group/test_extract_group_result_csdata.bin"
#define TEST_EXTRACT_GROUP_RESULT_GROUP_NOT_FOUND_JSON \
  IRRSEQ00_RESULT_SAMPLES                              \
  "group/test_extract_group_result_group_not_found.json"

#define TEST_EXTRACT_NEXT_GROUP_RESULT_JSON \
  IRRSEQ00_RESULT_SAMPLES "group/test_extract_next_group_result.json"
#define TEST_EXTRACT_NEXT_GROUP_RESULT_RAW \
  IRRSEQ00_RESULT_SAMPLES "group/test_extract_next_group_result.bin"

// Group Connection
#define TEST_EXTRACT_GROUP_CONNECTION_RESULT_JSON \
  IRRSEQ00_RESULT_SAMPLES                         \
  "group_connection/test_extract_group_connection_result.json"
#define TEST_EXTRACT_GROUP_CONNECTION_RESULT_RAW \
  IRRSEQ00_RESULT_SAMPLES                        \
  "group_connection/test_extract_group_connection_result.bin"
#define TEST_EXTRACT_GROUP_CONNECTION_RESULT_GROUP_CONNECTION_NOT_FOUND_JSON \
  IRRSEQ00_RESULT_SAMPLES                                                    \
  "group_connection/"                                                        \
  "test_extract_group_connection_result_group_connection_not_found.json"

// Racf Options
#define TEST_EXTRACT_RACF_OPTIONS_RESULT_JSON \
  IRRSEQ00_RESULT_SAMPLES "racf_options/test_extract_racf_options_result.json"
#define TEST_EXTRACT_RACF_OPTIONS_RESULT_RAW \
  IRRSEQ00_RESULT_SAMPLES "racf_options/test_extract_racf_options_result.bin"
#define TEST_EXTRACT_RACF_OPTIONS_RESULT_RACF_OPTIONS_NOT_FOUND_JSON \
  IRRSEQ00_RESULT_SAMPLES                                            \
  "racf_options/test_extract_racf_options_result_racf_options_not_found.json"

// Data Set
#define TEST_EXTRACT_DATASET_RESULT_JSON \
  IRRSEQ00_RESULT_SAMPLES "dataset/test_extract_dataset_result.json"
#define TEST_EXTRACT_DATASET_RESULT_RAW \
  IRRSEQ00_RESULT_SAMPLES "dataset/test_extract_dataset_result.bin"
#define TEST_EXTRACT_DATASET_RESULT_CSDATA_JSON \
  IRRSEQ00_RESULT_SAMPLES "dataset/test_extract_dataset_result_csdata.json"
#define TEST_EXTRACT_DATASET_RESULT_CSDATA_RAW \
  IRRSEQ00_RESULT_SAMPLES "dataset/test_extract_dataset_result_csdata.bin"
#define TEST_EXTRACT_DATASET_RESULT_DATASET_NOT_FOUND_JSON \
  IRRSEQ00_RESULT_SAMPLES                                  \
  "dataset/test_extract_dataset_result_dataset_not_found.json"

#define TEST_EXTRACT_NEXT_DATASET_RESULT_JSON \
  IRRSEQ00_RESULT_SAMPLES "dataset/test_extract_next_dataset_result.json"
#define TEST_EXTRACT_NEXT_DATASET_RESULT_RAW \
  IRRSEQ00_RESULT_SAMPLES "dataset/test_extract_next_dataset_result.bin"

// Resource
#define TEST_EXTRACT_RESOURCE_RESULT_JSON \
  IRRSEQ00_RESULT_SAMPLES "resource/test_extract_resource_result.json"
#define TEST_EXTRACT_RESOURCE_RESULT_RAW \
  IRRSEQ00_RESULT_SAMPLES "resource/test_extract_resource_result.bin"
#define TEST_EXTRACT_RESOURCE_RESULT_CSDATA_JSON \
  IRRSEQ00_RESULT_SAMPLES "resource/test_extract_resource_result_csdata.json"
#define TEST_EXTRACT_RESOURCE_RESULT_CSDATA_RAW \
  IRRSEQ00_RESULT_SAMPLES "resource/test_extract_resource_result_csdata.bin"
#define TEST_EXTRACT_RESOURCE_RESULT_RESOURCE_NOT_FOUND_JSON \
  IRRSEQ00_RESULT_SAMPLES                                    \
  "resource/test_extract_resource_result_resource_not_found.json"

#define TEST_EXTRACT_NEXT_RESOURCE_RESULT_JSON \
  IRRSEQ00_RESULT_SAMPLES "resource/test_extract_next_resource_result.json"
#define TEST_EXTRACT_NEXT_RESOURCE_RESULT_RAW \
  IRRSEQ00_RESULT_SAMPLES "resource/test_extract_next_resource_result.bin"

/*************************************************************************/
/* Prototypes                                                            */
/*************************************************************************/
// User
void test_generate_extract_user_request();
void test_generate_extract_user_request_lowercase_userid();
void test_parse_extract_user_result();
void test_parse_extract_user_result_csdata();
void test_parse_extract_user_result_user_not_found();
void test_parse_extract_user_result_required_parameter_missing();
void test_parse_extract_user_result_extraneous_parameter_provided();
void test_parse_extract_user_result_pseudo_boolean();

void test_generate_extract_next_user_request();
void test_parse_extract_next_user_result();

// Group
void test_generate_extract_group_request();
void test_parse_extract_group_result();
void test_parse_extract_group_result_csdata();
void test_parse_extract_group_result_group_not_found();
void test_parse_extract_group_result_required_parameter_missing();
void test_parse_extract_group_result_extraneous_parameter_provided();

void test_generate_extract_next_group_request();
void test_parse_extract_next_group_result();

// Group Connection
void test_generate_extract_group_connection_request();
void test_parse_extract_group_connection_result();
void test_parse_extract_group_connection_result_group_connection_not_found();
void test_parse_extract_group_connection_result_required_parameter_missing();
void test_parse_extract_group_connection_result_extraneous_parameter_provided();

// RACF Options
void test_generate_extract_racf_options_request();
void test_parse_extract_racf_options_result();
void test_parse_extract_racf_options_result_racf_options_not_found();
void test_parse_extract_racf_options_result_extraneous_parameter_provided();

// Data Set
void test_generate_extract_dataset_request();
void test_parse_extract_dataset_result();
void test_parse_extract_dataset_result_csdata();
void test_parse_extract_dataset_result_dataset_not_found();
void test_parse_extract_dataset_result_required_parameter_missing();
void test_parse_extract_dataset_result_extraneous_parameter_provided();

void test_generate_extract_next_dataset_request();
void test_parse_extract_next_dataset_result();

// Resource
void test_generate_extract_resource_request();
void test_generate_extract_resource_request_lowercase_resource_name_and_class_name();
void test_parse_extract_resource_result();
void test_parse_extract_resource_result_csdata();
void test_parse_extract_resource_result_resource_not_found();
void test_parse_extract_resource_result_required_parameter_missing();
void test_parse_extract_resource_result_extraneous_parameter_provided();

void test_generate_extract_next_resource_request();
void test_parse_extract_next_resource_result();

#endif
