#include "irrseq00.hpp"
#include "tests/irrsdl00/test_irrsdl00.hpp"
#include "tests/irrseq00/test_irrseq00.hpp"
#include "tests/irrsmo00/test_irrsmo00.hpp"
#include "tests/unity/unity.h"
#include "tests/validation/test_parameter_validation.hpp"

void setUp() {}

void tearDown() {}

int main() {
  UNITY_BEGIN();

  /*************************************************************************/
  /* Validation                                                            */
  /*************************************************************************/
  RUN_TEST(test_handle_syntax_error);
  RUN_TEST(test_handle_syntax_error_not_json);
  RUN_TEST(test_handle_syntax_error_binary_data);
  RUN_TEST(test_parse_no_parameters_provided_error);
  RUN_TEST(test_parse_junk_json_error);
  RUN_TEST(test_parse_parameters_junk_error);
  RUN_TEST(test_parse_parameters_missing_error);
  RUN_TEST(test_parse_extraneous_and_missing_parameters_error);
  RUN_TEST(test_parse_parameters_nonstring_error);

  /*************************************************************************/
  /* IRRSMO00                                                              */
  /*************************************************************************/
  // User
  RUN_TEST(test_generate_add_user_request);
  RUN_TEST(test_generate_alter_user_request);
  RUN_TEST(test_generate_alter_user_csdata_request);
  RUN_TEST(test_generate_delete_user_request);
  RUN_TEST(test_parse_add_user_result);
  RUN_TEST(test_parse_delete_user_result);
  RUN_TEST(test_parse_add_user_result_user_already_exists);
  RUN_TEST(test_parse_add_user_parameter_errors);
  RUN_TEST(test_parse_add_user_trait_errors);
  RUN_TEST(test_parse_add_user_no_xml_data_error);
  RUN_TEST(test_parse_alter_user_no_xml_data_error);
  RUN_TEST(test_parse_alter_user_traits_not_json_error);
  RUN_TEST(test_parse_irrsmo00_errors_result);
  RUN_TEST(test_parse_delete_user_trait_error_result);
  RUN_TEST(test_generate_alter_user_request_pseudo_boolean);
  // Group
  RUN_TEST(test_generate_add_group_request);
  RUN_TEST(test_generate_alter_group_request);
  RUN_TEST(test_generate_alter_group_csdata_request);
  RUN_TEST(test_generate_delete_group_request);
  RUN_TEST(test_parse_add_group_result);
  RUN_TEST(test_parse_delete_group_result);
  RUN_TEST(test_parse_add_group_result_group_already_exists);
  RUN_TEST(test_parse_add_group_parameter_errors);
  RUN_TEST(test_parse_add_group_trait_errors);
  // Group Connection
  RUN_TEST(test_generate_alter_group_connection_request);
  RUN_TEST(test_generate_delete_group_connection_request);
  RUN_TEST(test_parse_alter_group_connection_result);
  RUN_TEST(test_parse_delete_group_connection_result);
  RUN_TEST(test_parse_alter_group_connection_parameter_errors);
  RUN_TEST(test_parse_alter_group_connection_trait_errors);
  // Racf Options
  RUN_TEST(test_generate_alter_racf_options_request);
  RUN_TEST(test_parse_alter_racf_options_result);
  RUN_TEST(test_parse_alter_racf_options_parameter_errors);
  RUN_TEST(test_parse_alter_racf_options_trait_errors);
  // Data Set
  RUN_TEST(test_generate_add_dataset_request);
  RUN_TEST(test_generate_alter_dataset_request);
  RUN_TEST(test_generate_alter_dataset_csdata_request);
  RUN_TEST(test_generate_delete_dataset_request);
  RUN_TEST(test_parse_add_dataset_result);
  RUN_TEST(test_parse_delete_dataset_result);
  RUN_TEST(test_parse_add_dataset_result_dataset_already_exists);
  RUN_TEST(test_parse_add_dataset_parameter_errors);
  RUN_TEST(test_parse_add_dataset_trait_errors);
  // Resource
  RUN_TEST(test_generate_add_resource_request);
  RUN_TEST(test_generate_alter_resource_request);
  RUN_TEST(test_generate_alter_resource_csdata_request);
  RUN_TEST(test_generate_delete_resource_request);
  RUN_TEST(test_parse_add_resource_result);
  RUN_TEST(test_parse_delete_resource_result);
  RUN_TEST(test_parse_add_resource_result_resource_already_exists);
  RUN_TEST(test_parse_add_resource_parameter_errors);
  RUN_TEST(test_parse_add_resource_trait_errors);
  // Permission
  RUN_TEST(test_generate_alter_permission_dataset_request);
  RUN_TEST(test_generate_alter_permission_resource_request);
  RUN_TEST(test_generate_delete_permission_resource_request);
  RUN_TEST(test_parse_alter_permission_dataset_result);
  RUN_TEST(test_parse_alter_permission_resource_result);
  RUN_TEST(test_parse_delete_permission_resource_result);
  RUN_TEST(test_parse_alter_permission_dataset_parameter_errors);
  RUN_TEST(test_parse_alter_permission_dataset_with_class_parameter_error);
  RUN_TEST(test_parse_alter_permission_resource_parameter_errors);
  RUN_TEST(
      test_parse_alter_permission_resource_class_set_to_dataset_lowercase_parameter_error);
  RUN_TEST(
      test_parse_alter_permission_resource_class_set_to_dataset_uppercase_parameter_error);
  RUN_TEST(test_parse_alter_permission_resource_with_volume_parameter_error);
  RUN_TEST(test_parse_alter_permission_trait_errors);

  /*************************************************************************/
  /* IRRSEQ00                                                              */
  /*************************************************************************/
  // User
  RUN_TEST(test_generate_extract_user_request);
  RUN_TEST(test_generate_extract_user_request_lowercase_userid);
  RUN_TEST(test_parse_extract_user_result);
  RUN_TEST(test_parse_extract_user_result_csdata);
  RUN_TEST(test_parse_extract_user_result_user_not_found);
  RUN_TEST(test_parse_extract_user_result_required_parameter_missing);
  RUN_TEST(test_parse_extract_user_result_extraneous_parameter_provided);
  RUN_TEST(test_parse_extract_user_result_pseudo_boolean);

  RUN_TEST(test_generate_extract_next_user_request);
  RUN_TEST(test_parse_extract_next_user_result);

  // Group
  RUN_TEST(test_generate_extract_group_request);
  RUN_TEST(test_parse_extract_group_result);
  RUN_TEST(test_parse_extract_group_result_csdata);
  RUN_TEST(test_parse_extract_group_result_group_not_found);
  RUN_TEST(test_parse_extract_group_result_required_parameter_missing);
  RUN_TEST(test_parse_extract_group_result_extraneous_parameter_provided);

  RUN_TEST(test_generate_extract_next_group_request);
  RUN_TEST(test_parse_extract_next_group_result);

  // Group Connection
  RUN_TEST(test_generate_extract_group_connection_request);
  RUN_TEST(test_parse_extract_group_connection_result);
  RUN_TEST(
      test_parse_extract_group_connection_result_group_connection_not_found);
  RUN_TEST(
      test_parse_extract_group_connection_result_required_parameter_missing);
  RUN_TEST(
      test_parse_extract_group_connection_result_extraneous_parameter_provided);
  // RACF Options
  RUN_TEST(test_generate_extract_racf_options_request);
  RUN_TEST(test_parse_extract_racf_options_result);
  RUN_TEST(test_parse_extract_racf_options_result_racf_options_not_found);
  RUN_TEST(
      test_parse_extract_racf_options_result_extraneous_parameter_provided);
  // Data Set
  RUN_TEST(test_generate_extract_dataset_request);
  RUN_TEST(test_parse_extract_dataset_result);
  RUN_TEST(test_parse_extract_dataset_result_csdata);
  RUN_TEST(test_parse_extract_dataset_result_dataset_not_found);
  RUN_TEST(test_parse_extract_dataset_result_required_parameter_missing);
  RUN_TEST(test_parse_extract_dataset_result_extraneous_parameter_provided);

  RUN_TEST(test_generate_extract_next_dataset_request);
  RUN_TEST(test_parse_extract_next_dataset_result);

  // Resource
  RUN_TEST(test_generate_extract_resource_request);
  RUN_TEST(
      test_generate_extract_resource_request_lowercase_resource_name_and_class_name);
  RUN_TEST(test_parse_extract_resource_result);
  RUN_TEST(test_parse_extract_resource_result_csdata);
  RUN_TEST(test_parse_extract_resource_result_resource_not_found);
  RUN_TEST(test_parse_extract_resource_result_required_parameter_missing);
  RUN_TEST(test_parse_extract_resource_result_extraneous_parameter_provided);

  RUN_TEST(test_generate_extract_next_resource_request);
  RUN_TEST(test_parse_extract_next_resource_result);

  /*************************************************************************/
  /* IRRSDL00                                                              */
  /*************************************************************************/
  // Keyring
  RUN_TEST(test_generate_extract_keyring_request);
  RUN_TEST(test_parse_extract_keyring_result);
  RUN_TEST(test_parse_extract_keyring_result_keyring_not_found);
  RUN_TEST(test_parse_extract_keyring_result_required_parameter_missing);

  RUN_TEST(test_generate_add_keyring_request);

  RUN_TEST(test_generate_delete_keyring_request);

  return UNITY_END();
}
