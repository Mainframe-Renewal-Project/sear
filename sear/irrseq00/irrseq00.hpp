#ifndef __IRRSEQ00_H_
#define __IRRSEQ00_H_

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>

#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

#define PROFILE_NAME_MAX_LENGTH 247

/*************************************************************************/
/* Function Codes                                                        */
/*************************************************************************/
const uint8_t RACF_OPTIONS_EXTRACT_FUNCTION_CODE     = 0x16;
const uint8_t RRSF_EXTRACT_FUNCTION_CODE             = 0x21;
const uint8_t USER_EXTRACT_FUNCTION_CODE             = 0x19;
const uint8_t USER_EXTRACT_NEXT_FUNCTION_CODE        = 0x1a;
const uint8_t GROUP_EXTRACT_FUNCTION_CODE            = 0x1b;
const uint8_t GROUP_EXTRACT_NEXT_FUNCTION_CODE       = 0x1c;
const uint8_t GROUP_CONNECTION_EXTRACT_FUNCTION_CODE = 0x1d;
const uint8_t RESOURCE_EXTRACT_FUNCTION_CODE         = 0x1f;
const uint8_t RESOURCE_EXTRACT_NEXT_FUNCTION_CODE    = 0x20;
const uint8_t DATASET_EXTRACT_FUNCTION_CODE          = 0x22;
const uint8_t DATASET_EXTRACT_NEXT_FUNCTION_CODE     = 0x23;

/*************************************************************************/
/* Field Descriptor Information                                          */
/*************************************************************************/
// Field types
const uint16_t t_member_repeat_group = 0x8000;  // member of a repeat group
const uint16_t t_reserved            = 0x4000;  // reserved
const uint16_t t_boolean_field       = 0x2000;  // flag (boolean) field
const uint16_t t_repeat_field_header = 0x1000;  // repeat field header

// Field descriptor flags
const uint32_t f_boolean_field = 0x80000000;  // value of a boolean field
const uint32_t f_output_only   = 0x40000000;  // output-only field

#pragma pack(push, 1)  // Don't byte align structure members.

/*************************************************************************/
/* Generic Extract Structures                                            */
/*                                                                       */
/* Use For:                                                              */
/*   - User Extract                                                      */
/*   - Group Extract                                                     */
/*   - Group Connection Extract                                          */
/*   - Resource Extract                                                  */
/*   - Data Set Extract                                                  */
/*************************************************************************/
typedef struct {
  char eyecatcher[4];             // 'PXTR'
  uint32_t result_buffer_length;  // result buffer length
  uint8_t subpool;                // subpool of result buffer
  uint8_t version;                // parameter list version
  uint8_t reserved_1[2];          // reserved
  char class_name[8];             // class name - upper case, blank pad
  uint32_t profile_name_length;   // length of profile name
  char reserved_2[2];             // reserved
  char volume[6];                 // volume (for data set extract)
  char reserved_3[4];             // reserved
  uint32_t flags;                 // see flag constants below
  uint32_t segment_count;         // number of segments
  char reserved_4[16];            // reserved
                                  // start of extracted data
} generic_extract_parms_results_t;
// Note: This structure is used for both input & output.

typedef struct {
  char RACF_work_area[1024];
  // return and reason codes
  uint32_t ALET_SAF_rc;
  uint32_t SAF_rc;
  uint32_t ALET_RACF_rc;
  uint32_t RACF_rc;
  uint32_t ALET_RACF_rsn;
  uint32_t RACF_rsn;
  // extract function to perform
  uint8_t function_code;
  generic_extract_parms_results_t profile_extract_parms;
  // Max of 247 + 1 for null terimnator
  char profile_name[PROFILE_NAME_MAX_LENGTH + 1];
  // Result area for the service
  uint32_t ACEE;
  uint8_t result_buffer_subpool;
  // R_admin returns data here
  char *__ptr32 p_result_buffer;
} generic_extract_args_t;

typedef struct {
  char *__ptr32 p_work_area;
  // return and reason code
  uint32_t *__ptr32 p_ALET_SAF_rc;
  uint32_t *__ptr32 p_SAF_rc;
  uint32_t *__ptr32 p_ALET_RACF_rc;
  uint32_t *__ptr32 p_RACF_rc;
  uint32_t *__ptr32 p_ALET_RACF_rsn;
  uint32_t *__ptr32 p_RACF_rsn;
  // extract function to perform
  uint8_t *__ptr32 p_function_code;
  generic_extract_parms_results_t *__ptr32 p_profile_extract_parms;
  char *__ptr32 p_profile_name;
  // Result area for the service
  uint32_t *__ptr32 p_ACEE;
  uint8_t *__ptr32 p_result_buffer_subpool;
  // R_admin returns data here
  char *__ptr32 *__ptr32 p_p_result_buffer;
} generic_extract_arg_pointers_t;

// 31-bit for IRRSEQ00 arguments.
typedef struct {
  generic_extract_args_t args;
  generic_extract_arg_pointers_t arg_pointers;
} generic_extract_underbar_arg_area_t;

/*************************************************************************/
/* Generic Segment/Field Descriptor Structures                           */
/*                                                                       */
/* Used to interpret extracted generic profile data                      */
/*************************************************************************/
typedef struct {
  char name[8];                      // segment name, upper case, blank padded
  uint32_t flags;                    //
  uint32_t field_count;              // number of fields
  char reserved_1[4];                // reserved
  uint32_t field_descriptor_offset;  // offset to first field descriptor
  char reserved_2[16];               // reserved
                                     // start of next segment descriptor
} generic_segment_descriptor_t;

typedef union {
  uint32_t field_data_length;   // length of field data or ...
  uint32_t repeat_group_count;  // number of repeat groups
} generic_field_data_length_repeat_group_count_t;

typedef union {
  uint32_t field_data_offset;           // offset to field data or ...
  uint32_t repeat_group_element_count;  // number of elems in repeat field hdrs
} generic_field_data_offset_repeat_group_element_count_t;

typedef struct {
  char name[8];  // field name, upper case, blank padded
  uint16_t type;
  char reserved_1[2];
  uint32_t flags;
  generic_field_data_length_repeat_group_count_t
      field_data_length_repeat_group_count;
  char rserved_2[4];
  generic_field_data_offset_repeat_group_element_count_t
      field_data_offset_repeat_group_element_count;
  char reserved_3[16];
  // start of next field descriptor
} generic_field_descriptor_t;

/*************************************************************************/
/* RACF Options Extract Structures                                       */
/*                                                                       */
/* Specific to RACF Options Extract.                                     */
/*************************************************************************/
typedef struct {
  uint32_t request_flags;
  uint8_t reserved_1[10];
} racf_options_extract_parms_t;

typedef struct {
  char RACF_work_area[1024];
  // return and reason codes
  uint32_t ALET_SAF_rc;
  uint32_t SAF_rc;
  uint32_t ALET_RACF_rc;
  uint32_t RACF_rc;
  uint32_t ALET_RACF_rsn;
  uint32_t RACF_rsn;
  // extract function to perform
  uint8_t function_code;
  racf_options_extract_parms_t racf_options_extract_parms;
  // Max of 247 + 1 for null terimnator
  char profile_name[PROFILE_NAME_MAX_LENGTH + 1];
  // Result area for the service
  uint32_t ACEE;
  uint8_t result_buffer_subpool;
  // R_admin returns data here
  char *__ptr32 p_result_buffer;
} racf_options_extract_args_t;

typedef struct {
  char *__ptr32 p_work_area;
  // return and reason code
  uint32_t *__ptr32 p_ALET_SAF_rc;
  uint32_t *__ptr32 p_SAF_rc;
  uint32_t *__ptr32 p_ALET_RACF_rc;
  uint32_t *__ptr32 p_RACF_rc;
  uint32_t *__ptr32 p_ALET_RACF_rsn;
  uint32_t *__ptr32 p_RACF_rsn;
  // extract function to perform
  uint8_t *__ptr32 p_function_code;
  racf_options_extract_parms_t *__ptr32 p_racf_options_extract_parms;
  char *__ptr32 p_profile_name;
  // Result area for the service
  uint32_t *__ptr32 p_ACEE;
  uint8_t *__ptr32 p_result_buffer_subpool;
  // R_admin returns data here
  char *__ptr32 *__ptr32 p_p_result_buffer;
} racf_options_extract_arg_pointers_t;

// 31-bit for IRRSEQ00 arguments.
typedef struct {
  racf_options_extract_args_t args;
  racf_options_extract_arg_pointers_t arg_pointers;
} racf_options_extract_underbar_arg_area_t;

/*************************************************************************/
/* RACF Options Segment/Field Descriptor Structures                      */
/*                                                                       */
/* Used to interpret extracted RACF Options profile data                 */
/*************************************************************************/
typedef struct {
  char eyecatcher[4];
  uint32_t result_buffer_length;
  char reserved_2[4];
  uint16_t segment_count;
  // Start of first segment descriptor.
} racf_options_extract_results_t;

typedef struct {
  char name[8];
  uint8_t flag;
  uint16_t field_count;
  // Start of first field descriptor
} racf_options_segment_descriptor_t;

typedef struct {
  char name[8];
  uint8_t flag;
  uint16_t field_length;
  // Start of next field descriptor, next segment, or end of data
} racf_options_field_descriptor_t;

typedef struct {
  char key[8 + 1];
  char type;
} racf_options_field_type_t;

/*************************************************************************/
/* RRSF Options Extract Structures                                       */
/*                                                                       */
/* Specific to RACF RRSF Extract.                                        */
/*************************************************************************/

typedef struct {
  uint32_t length;
  char data;
} offset_field_t;

typedef struct {
  char rrsf_node_name[8];
  char rrsf_multinode_system_node_name[8];
  uint8_t rrsf_protocol;
  uint8_t rrsf_node_state;
  uint16_t reserved_space[2];
  char date_of_last_received_work[8];
  char time_of_last_received_work[8];
  char date_of_last_sent_work[8];
  char time_of_last_sent_work[8];
  char partner_node[4];
  uint32_t binary_partner_template_release_level;
  uint32_t binary_partner_template_service_level;
  offset_field_t offset_partner_node_parse_level;
  offset_field_t offset_rrsf_node_description;
  offset_field_t offset_rrsf_node_workspace_dataset;
  offset_field_t offset_rrsf_workspace_sms_management_class;
  offset_field_t offset_rrsf_workspace_sms_storage_class;
  offset_field_t offset_rrsf_workspace_dataset_volume;
  uint32_t rrsf_workspace_file_size;
  offset_field_t offset_workspace_dataset_wdsqual;
  uint32_t bit_flags;
  offset_field_t offset_inmsg_dataset_name;
  uint32_t inmsg_records;
  uint32_t inmsg_extents;
  offset_field_t offset_outmsg_dataset_name;
  uint32_t outmsg_records;
  uint32_t outmsg_extents;
  offset_field_t offset_inmsg2_dataset_name;
  uint32_t inmsg2_records;
  uint32_t inmsg2_extents;
  offset_field_t offset_outmsg2_dataset_name;
  uint32_t outmsg2_records;
  uint32_t outmsg2_extents;
  uint32_t node_requests_denied;
} racf_rrsf_node_definitions_t;

typedef struct {
  char node_notification_destination[8];
  char userid_notification_destination[8];
  char output_level[6];
  char notify_level[6];
} racf_rrsf_set_settings_t;

typedef struct {
  char eyecatcher[4];
  uint32_t subpool_buffer_length;
  uint32_t result_buffer_length;
  uint32_t bit_flags;
  char subsystem_prefix[8];
  uint32_t rrsf_node_index;
  uint8_t automatic_command_redirection;
  racf_rrsf_set_settings_t command_redirection_settings;
  uint8_t automatic_password_redirection;
  racf_rrsf_set_settings_t password_redirection_settings;
  uint8_t password_synchronization;
  racf_rrsf_set_settings_t password_synchronization_settings;
  uint8_t automatic_redirection_application_updates;
  racf_rrsf_set_settings_t application_updates_redirection_settings;
  uint32_t number_of_rrsf_nodes;
  char racf_subsystem_name[4];
  char racf_subsystem_userid[8];
  char reserved_space[52];
  racf_rrsf_node_definitions_t node_definitions;
} racf_rrsf_extract_results_t;

typedef struct {
  char RACF_work_area[1024];
  // return and reason codes
  uint32_t ALET_SAF_rc;
  uint32_t SAF_rc;
  uint32_t ALET_RACF_rc;
  uint32_t RACF_rc;
  uint32_t ALET_RACF_rsn;
  uint32_t RACF_rsn;
  // extract function to perform
  uint8_t function_code;
  uint8_t parameter_list;
  char profile_name[PROFILE_NAME_MAX_LENGTH + 1];
  // Result area for the service
  uint32_t ACEE;
  uint8_t result_buffer_subpool;
  // R_admin returns data here
  char *__ptr32 p_result_buffer;
} racf_rrsf_extract_args_t;

typedef struct {
  char *__ptr32 p_work_area;
  // return and reason code
  uint32_t *__ptr32 p_ALET_SAF_rc;
  uint32_t *__ptr32 p_SAF_rc;
  uint32_t *__ptr32 p_ALET_RACF_rc;
  uint32_t *__ptr32 p_RACF_rc;
  uint32_t *__ptr32 p_ALET_RACF_rsn;
  uint32_t *__ptr32 p_RACF_rsn;
  // extract function to perform
  uint8_t *__ptr32 p_function_code;
  uint8_t *__ptr32 parameter_list = 0;
  char *__ptr32 p_profile_name;
  // Result area for the service
  uint32_t *__ptr32 p_ACEE;
  uint8_t *__ptr32 p_result_buffer_subpool;
  // R_admin returns data here
  char *__ptr32 *__ptr32 p_p_result_buffer;
} racf_rrsf_extract_arg_pointers_t;

// 31-bit for IRRSEQ00 arguments.
typedef struct {
  racf_rrsf_extract_args_t args;
  racf_rrsf_extract_arg_pointers_t arg_pointers;
} racf_rrsf_extract_underbar_arg_area_t;

#pragma pack(pop)  // Restore default structure packing options.

// Glue code to call IRRSEQ00 assembler code.
extern "C" uint32_t callRadmin(char *__ptr32);

#endif
