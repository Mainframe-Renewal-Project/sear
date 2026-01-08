#include "profile_post_processor.hpp"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "conversion.hpp"
#include "sear_error.hpp"

// Use ntohl() to convert 32-bit values from big endian to little endian.
// use ntohs() to convert 16-bit values from big endian to little endian.
// On z/OS these macros do nothing since "network order" and z/Architecture are
// both big endian. This is only necessary for unit testing off platform.
#include <arpa/inet.h>

#include "irrseq00.hpp"
#include "key_map.hpp"

#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

namespace SEAR {
void ProfilePostProcessor::postProcessGeneric(SecurityRequest &request) {
  nlohmann::json profile;
  profile["profile"]            = nlohmann::json::object();

  const std::string &admin_type = request.getAdminType();

  // Profile Pointers and Information
  const char *p_profile = request.getRawResultPointer();
  const generic_extract_parms_results_t *p_generic_result =
      reinterpret_cast<const generic_extract_parms_results_t *>(p_profile);

  Logger::getInstance().debug("Raw generic profile extract result:");
  Logger::getInstance().hexDump(p_profile, request.getRawResultLength());

  // Segment Variables
  int first_segment_offset = sizeof(generic_extract_parms_results_t);
  first_segment_offset += ntohl(p_generic_result->profile_name_length);
  const generic_segment_descriptor_t *p_segment =
      reinterpret_cast<const generic_segment_descriptor_t *>(
          p_profile + first_segment_offset);
  // Field Variables
  std::string sear_field_key;
  char sear_field_type;

  // Repeat Group Variables
  std::vector<nlohmann::json> repeat_group;
  int repeat_group_count;
  int repeat_group_element_count;
  std::string sear_repeat_field_key;
  char sear_repeat_field_type;

  // Post Process Segments
  for (int i = 1; i <= ntohl(p_generic_result->segment_count); i++) {
    std::string segment_key =
        ProfilePostProcessor::postProcessKey(p_segment->name, 8);
    profile["profile"][segment_key] = nlohmann::json::object();
    // Post Process Fields
    const generic_field_descriptor_t *p_field =
        reinterpret_cast<const generic_field_descriptor_t *>(
            p_profile + ntohl(p_segment->field_descriptor_offset));
    for (int j = 1; j <= ntohl(p_segment->field_count); j++) {
      sear_field_key = ProfilePostProcessor::postProcessFieldKey(
          admin_type, segment_key, p_field->name);
      sear_field_type = get_trait_type(admin_type, segment_key, sear_field_key);
      if (!(ntohs(p_field->type) & t_repeat_field_header)) {
        // Post Process Non-Repeat Fields
        ProfilePostProcessor::processGenericField(
            profile["profile"][segment_key][sear_field_key], p_field, p_profile,
            sear_field_type);
      } else {
        // Post Process Repeat Fields
        repeat_group_count = ntohl(
            p_field->field_data_length_repeat_group_count.repeat_group_count);
        repeat_group_element_count =
            ntohl(p_field->field_data_offset_repeat_group_element_count
                      .repeat_group_element_count);
        // Post Process Each Repeat Group
        for (int k = 1; k <= repeat_group_count; k++) {
          repeat_group.push_back(nlohmann::json::object());
          // Post Process Each Repeat Group Field
          for (int l = 1; l <= repeat_group_element_count; l++) {
            p_field++;
            sear_repeat_field_key = ProfilePostProcessor::postProcessFieldKey(
                admin_type, segment_key, p_field->name);
            sear_repeat_field_type =
                get_trait_type(admin_type, segment_key, sear_repeat_field_key);
            ProfilePostProcessor::processGenericField(
                repeat_group[k - 1][sear_repeat_field_key], p_field, p_profile,
                sear_repeat_field_type);
          }
        }
        profile["profile"][segment_key][sear_field_key] = repeat_group;
        repeat_group.clear();
      }
      p_field++;
    }
    p_segment++;
  }
  request.setIntermediateResultJSON(profile);
}

void ProfilePostProcessor::postProcessSearchGeneric(SecurityRequest &request) {
  nlohmann::json profiles;

  std::vector<std::string> repeat_group_profiles;

  std::vector<char *> found_profiles = request.getFoundProfiles();

  for (int i = 0; i < found_profiles.size(); i++) {
    int len = std::strlen(found_profiles[i]);
    if (len > 0) {
      std::string profile_name =
          ProfilePostProcessor::decodeEBCDICBytes(found_profiles[i], len);
      if (profile_name != " " && profile_name != "") {
        repeat_group_profiles.push_back(profile_name);
      }
    }
    free(found_profiles[i]);
  }

  profiles["profiles"] = repeat_group_profiles;

  request.setIntermediateResultJSON(profiles);
}

void ProfilePostProcessor::postProcessRACFOptions(SecurityRequest &request) {
  nlohmann::json profile;
  profile["profile"] = nlohmann::json::object();

  // Profile Pointers and Information
  const char *p_profile = request.getRawResultPointer();

  Logger::getInstance().debug("Raw RACF Options extract result:");
  Logger::getInstance().hexDump(p_profile, request.getRawResultLength());

  // Segment Variables
  const racf_options_segment_descriptor_t *p_segment =
      reinterpret_cast<const racf_options_segment_descriptor_t *>(
          p_profile + sizeof(racf_options_extract_results_t));

  // Field Variables
  const racf_options_field_descriptor_t *p_field =
      reinterpret_cast<const racf_options_field_descriptor_t *>(
          p_profile + sizeof(racf_options_extract_results_t) +
          sizeof(racf_options_segment_descriptor_t));
  std::vector<std::string> list_field_data;
  const char *p_list_field_data;

  // Post Process Base Segment
  std::string segment_key =
      ProfilePostProcessor::postProcessKey(p_segment->name, 8);
  profile["profile"][segment_key] = nlohmann::json::object();

  // Post Process Fields
  for (int i = 1; i <= ntohs(p_segment->field_count); i++) {
    std::string sear_field_key = ProfilePostProcessor::postProcessFieldKey(
        "racf-options", segment_key, p_field->name);
    char field_type =
        get_trait_type("racf-options", segment_key, sear_field_key);
    int field_length = ntohs(p_field->field_length);
    if (field_length != 0) {
      if (field_type == TRAIT_TYPE_REPEAT) {
        // Post Process List Fields
        p_list_field_data = reinterpret_cast<const char *>(p_field) +
                            sizeof(racf_options_field_descriptor_t);
        for (int j = 0; j < field_length / 9; j++) {
          list_field_data.push_back(
              ProfilePostProcessor::decodeEBCDICBytes(p_list_field_data, 8));
          p_list_field_data += 9;
        }
        profile["profile"][segment_key][sear_field_key] = list_field_data;
        list_field_data.clear();
      } else {
        // Post Process String & Number Fields
        std::string field_data = ProfilePostProcessor::decodeEBCDICBytes(
            reinterpret_cast<const char *>(p_field) +
                sizeof(racf_options_field_descriptor_t),
            field_length);
        if (field_type == TRAIT_TYPE_UINT) {
          // Number
          profile["profile"][segment_key][sear_field_key] =
              std::stoi(field_data);
        } else {
          // String
          profile["profile"][segment_key][sear_field_key] = field_data;
        }
      }
    } else if (field_type == TRAIT_TYPE_BOOLEAN) {
      // Post Process Boolean Fields
      if (p_field->flag == 0xe8) {  // 0xe8 is 'Y' in EBCDIC.
        profile["profile"][segment_key][sear_field_key] = true;
      } else {
        profile["profile"][segment_key][sear_field_key] = false;
      }
    } else {
      // Post Process All Non-Boolean Fields Without a Value
      profile["profile"][segment_key][sear_field_key] = nullptr;
    }
    p_field = reinterpret_cast<const racf_options_field_descriptor_t *>(
        reinterpret_cast<const char *>(p_field) +
        sizeof(racf_options_field_descriptor_t) + field_length);
  }
  request.setIntermediateResultJSON(profile);
}

// There are a bunch of these weird offset fields
// This function allow offset fields to easily be processed
void ProfilePostProcessor::postprocessRRSFOffsetField(nlohmann::json &profile, const std::string &key, const char *p_profile, int offset) {
  const racf_rrsf_offset_field_t *p_field =
    reinterpret_cast<const racf_rrsf_offset_field_t *>(p_profile + offset);
  
  // Only create the key if there actually is any data in the offset field, avoids empty quotes
  if (p_field->length > 0) {
    profile[key] = ProfilePostProcessor::decodeEBCDICBytes(p_field->data,p_field->length);
  }
}

//////////////////////////////////////////////////////////////////////////
// RRSF post processing                                                 //
//////////////////////////////////////////////////////////////////////////
void ProfilePostProcessor::postProcessRACFRRSF(SecurityRequest &request) {
  nlohmann::json profile;
  profile["profile"] = nlohmann::json::object();

  // Profile pointers and information
  const char *p_profile = request.getRawResultPointer();

  Logger::getInstance().debug("Raw RACF RRSF extract result:");
  Logger::getInstance().hexDump(p_profile, request.getRawResultLength());

  // RRSF variables
  const racf_rrsf_extract_results_t *rrsf_extract_result =
      reinterpret_cast<const racf_rrsf_extract_results_t *>(p_profile);
  
  profile["profile"]["base"]["base:subsystem_name"] = ProfilePostProcessor::decodeEBCDICBytes(rrsf_extract_result->racf_subsystem_name, 4);
  profile["profile"]["base"]["base:subsystem_userid"] = ProfilePostProcessor::decodeEBCDICBytes(rrsf_extract_result->racf_subsystem_userid, 8);
  profile["profile"]["base"]["base:subsystem_operator_prefix"] = ProfilePostProcessor::decodeEBCDICBytes(rrsf_extract_result->subsystem_prefix, 8);
  profile["profile"]["base"]["base:number_of_defined_nodes"] = rrsf_extract_result->number_of_rrsf_nodes;

  // Post process nodes if any are defined
  if (rrsf_extract_result->number_of_rrsf_nodes > 0) {
    // Retrieve local node index
    const int &local_node = rrsf_extract_result->rrsf_node_index;

    // Node definitions start at 544, per IBM documentation,
    // it dynamically calculates it in case it ever changes to be beyond 544
    int first_node_offset = sizeof(racf_rrsf_extract_results_t) - sizeof(racf_rrsf_node_definitions_t);

    // Node definitions to be added to result JSON
    std::vector<nlohmann::json> nodes;
    for (int i = 1; i <= ntohl(rrsf_extract_result->number_of_rrsf_nodes); i++) {
      
      const racf_rrsf_node_definitions_t *p_nodes =
      reinterpret_cast<const racf_rrsf_node_definitions_t *>(p_profile + first_node_offset);
      
      nlohmann::json node_definition;

      if (i == local_node) {
        node_definition["base:is_local_node"] = true;
      } else {
        node_definition["base:is_local_node"] = false;
      }

      node_definition["base:node_name"] = ProfilePostProcessor::decodeEBCDICBytes(p_nodes->rrsf_node_name,8);
      node_definition["base:multisystem_node_name"] = ProfilePostProcessor::decodeEBCDICBytes(p_nodes->rrsf_multinode_system_node_name,8);
      node_definition["base:date_of_last_received_work"] = ProfilePostProcessor::decodeEBCDICBytes(p_nodes->date_of_last_received_work,8);
      node_definition["base:time_of_last_received_work"] = ProfilePostProcessor::decodeEBCDICBytes(p_nodes->time_of_last_received_work,8);
      node_definition["base:date_of_last_sent_work"] = ProfilePostProcessor::decodeEBCDICBytes(p_nodes->date_of_last_sent_work,8);
      node_definition["base:time_of_last_sent_work"] = ProfilePostProcessor::decodeEBCDICBytes(p_nodes->time_of_last_sent_work,8);
      node_definition["base:node_state"] = p_nodes->rrsf_node_state;

      ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:node_description", p_profile, p_nodes->offset_rrsf_node_description);
      ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:partner_node_dynamic_parse_level",p_profile, p_nodes->offset_partner_node_parse_level);

      // Workspace dataset information
      ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:workspace_dataset_prefix", p_profile, p_nodes->offset_rrsf_node_workspace_dataset_prefix);
      ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:workspace_dataset_name", p_profile, p_nodes->offset_workspace_dataset_wdsqual);
      ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:workspace_dataset_sms_management_class", p_profile, p_nodes->offset_rrsf_workspace_sms_management_class);
      ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:workspace_dataset_sms_storage_class", p_profile, p_nodes->offset_rrsf_workspace_sms_storage_class);
      ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:workspace_dataset_sms_data_class", p_profile, p_nodes->offset_rrsf_workspace_data_class);
      ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:workspace_dataset_volume", p_profile, p_nodes->offset_rrsf_workspace_dataset_volume);

      node_definition["base:workspace_file_size"] = p_nodes->rrsf_workspace_file_size;

      // inmsg and outmsg dataset information
      ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:in_message_dataset_name", p_profile, p_nodes->offset_inmsg_dataset_name);
      ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:out_message_dataset_name", p_profile, p_nodes->offset_outmsg_dataset_name);

      ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:temporary_in_message_dataset_name", p_profile, p_nodes->offset_inmsg2_dataset_name);
      ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:temporary_out_message_dataset_name", p_profile, p_nodes->offset_outmsg2_dataset_name);

      node_definition["base:in_message_records"] = p_nodes->inmsg_records;
      node_definition["base:out_message_records"] = p_nodes->outmsg_records;
      node_definition["base:temporary_in_message_records"] = p_nodes->inmsg2_records;
      node_definition["base:temporary_out_message_records"] = p_nodes->outmsg2_records;
      node_definition["base:in_message_extents"] = p_nodes->inmsg_extents;
      node_definition["base:out_message_extents"] = p_nodes->outmsg_extents;
      node_definition["base:in_message2_extents"] = p_nodes->inmsg2_extents;
      node_definition["base:out_message2_extents"] = p_nodes->outmsg2_extents;

      // Partner node information
      node_definition["base:partner_node_operating_system_version"] = p_nodes->partner_node_os_version;
      node_definition["base:partner_node_template_release_level"] = p_nodes->binary_partner_node_template_release_level;
      node_definition["base:partner_node_template_service_level"] = p_nodes->binary_partner_node_template_service_level;

      if (p_nodes->tcpip_listener_status == 2) {
        node_definition["base:tcpip_listener_status_active"] = true;
      } else {
        node_definition["base:tcpip_listener_status_active"] = false;
      } 

      if (p_nodes->appc_listener_status == 2) {
        node_definition["base:appc_listener_status_active"] = true;
      } else {
        node_definition["base:appc_listener_status_active"] = false;
      } 

      // Determines which protocol the RRSF node is using and adds it to the result JSON
      if (p_nodes->rrsf_protocol == 01) {
        node_definition["base:node_protocol"] = "appc";

        // These are only relevant if system is using APPC, instead of the modern TCP/IP
        ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:appc_modename", p_profile, p_nodes->offset_appc_modename);
        ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:appc_lu_name", p_profile, p_nodes->offset_appc_lu_name);
        ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:appc_tp_name", p_profile, p_nodes->offset_appc_tp_name);
        ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:appc_netname", p_profile, p_nodes->offset_appc_netname);
      } else if (p_nodes->rrsf_protocol == 02) {
        node_definition["base:node_protocol"] = "tcpip";

        // These are only relevant if system is using TCPIP for RRSF
        ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:resolved_tcpip_address", p_profile, p_nodes->offset_tcpip_address_resolved_by_system);
        ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:target_tcpip_address", p_profile, p_nodes->offset_tcpip_address_target_command);
        ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:tcpip_port", p_profile, p_nodes->offset_tcpip_port);
        ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:tcpip_attls_rule", p_profile, p_nodes->offset_tcpip_tls_rule);
        ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:tcpip_attls_cipher", p_profile, p_nodes->offset_tcpip_cipher_policy);
        ProfilePostProcessor::postprocessRRSFOffsetField(node_definition, "base:tcpip_attls_certificate_user", p_profile, p_nodes->offset_tcpip_certificate_user);
      } else {
        node_definition["base:node_protocol"] = "none";
      }

      node_definition["base:requests_denied"] = p_nodes->node_requests_denied;

      // Add node definition to result JSON
      nodes.push_back(node_definition);

      // Increment to next node offset
      first_node_offset = first_node_offset + sizeof(racf_rrsf_node_definitions_t);  
    }
    // Append node definitions to result JSON after processing them
    profile["profile"]["base"]["base:nodes"] = nodes;
  }

  if (rrsf_extract_result->bit_flags == RRSF_FULLRRSFCOMM_ACTIVE) {
    profile["profile"]["base"]["base:full_rrsf_communication_active"] = true;
  } else {
    profile["profile"]["base"]["base:full_rrsf_communication_active"] = false;
  }

  if (rrsf_extract_result->bit_flags == RRSF_SET_AUTODIRECT_ACTIVE) {
    profile["profile"]["base"]["base:full_autodirect_active"] = true;
  } else {
    profile["profile"]["base"]["base:full_autodirect_active"] = false;
  }

  if (rrsf_extract_result->bit_flags == RRSF_SET_AUTODIRECT_APP_UPDATES) {
    profile["profile"]["base"]["base:autodirect_application_updates"] = true;
  } else {
    profile["profile"]["base"]["base:autodirect_application_updates"] = false;
  }

  if (rrsf_extract_result->bit_flags == RRSF_SET_AUTO_PASSWORD_DIRECTION) {
    profile["profile"]["base"]["base:autodirect_passwords"] = true;
  } else {
    profile["profile"]["base"]["base:autodirect_passwords"] = false;
  }

  if (rrsf_extract_result->bit_flags == RRSF_SET_TRACE_APPC_ACTIVE) {
    profile["profile"]["base"]["base:appc_trace_active"] = true;
  } else {
    profile["profile"]["base"]["base:appc_trace_active"] = false;
  }

  if (rrsf_extract_result->bit_flags == RRSF_SET_TRACE_IMAGE_ACTIVE) {
    profile["profile"]["base"]["base:image_trace_active"] = true;
  } else {
    profile["profile"]["base"]["base:image_trace_active"] = false;
  }
  
  if (rrsf_extract_result->bit_flags == RRSF_SET_TRACE_SSL_ACTIVE) {
    profile["profile"]["base"]["base:ssl_trace_active"] = true;
  } else {
    profile["profile"]["base"]["base:ssl_trace_active"] = false;
  }

  if (rrsf_extract_result->bit_flags == RRSF_PRIVILEGED_ATTRIBUTE) {
    profile["profile"]["base"]["base:privileged_attribute_on"] = true;
  } else {
    profile["profile"]["base"]["base:privileged_attribute_on"] = false;
  }

  if (rrsf_extract_result->bit_flags == RRSF_TRUSTED_ATTRIBUTE) {
    profile["profile"]["base"]["base:trusted_attribute_on"] = true;
  } else {
    profile["profile"]["base"]["base:trusted_attribute_on"] = false;
  }

  if (rrsf_extract_result->bit_flags == RRSF_NOT_ENOUGH_SPACE) {
      request.setSEARReturnCode(4);
      // Raise Exception if RRSF extract Failed.
      throw SEARError("Not enough memory to extract RRSF settings");
  }
  
  request.setIntermediateResultJSON(profile);
}

void ProfilePostProcessor::processGenericField(
    nlohmann::json &json_field, const generic_field_descriptor_t *p_field,
    const char *p_profile, const char sear_field_type) {
  if (ntohs(p_field->type) & t_boolean_field) {
    // Post Process Boolean Fields
    if (ntohl(p_field->flags) & f_boolean_field) {
      json_field = true;
    } else {
      json_field = false;
    }
  } else {
    // Post Process Generic Fields
    int field_length =
        ntohl(p_field->field_data_length_repeat_group_count.field_data_length);
    std::string field_data = ProfilePostProcessor::decodeEBCDICBytes(
        p_profile + ntohl(p_field->field_data_offset_repeat_group_element_count
                              .field_data_offset),
        field_length);
    if (field_data == "") {
      // Set Empty Fields to 'null'
      json_field = nullptr;
    } else if (sear_field_type == TRAIT_TYPE_UINT) {
      // Cast Integer Fields
      json_field = std::stoi(field_data);
    } else if (sear_field_type == TRAIT_TYPE_PSEUDO_BOOLEAN) {
      // Convert Pseudo Boolean Fields
      if (field_data == "YES") {
        json_field = true;
      } else {
        json_field = false;
      }
    } else {
      // Treat All Other Fields as Strings
      json_field = field_data;
    }
  }
}

std::string ProfilePostProcessor::postProcessFieldKey(
    const std::string &admin_type, const std::string &segment,
    const char *p_raw_field_key) {
  std::string field_key =
      ProfilePostProcessor::postProcessKey(p_raw_field_key, 8);
  const char *sear_field_key =
      get_sear_key(admin_type.c_str(), segment.c_str(), field_key.c_str());
  if (sear_field_key == nullptr) {
    return "experimental:" + field_key;
  }
  if (sear_field_key + std::strlen(sear_field_key) - 1) {
    if (!(*(sear_field_key + std::strlen(sear_field_key) - 1) == '*')) {
      return sear_field_key;
    }
  }
  return segment + ":" + field_key;
}

std::string ProfilePostProcessor::postProcessKey(const char *p_source_key,
                                                 int length) {
  std::string post_processed_key =
      ProfilePostProcessor::decodeEBCDICBytes(p_source_key, length);
  // Convert to lowercase
  std::transform(post_processed_key.begin(), post_processed_key.end(),
                 post_processed_key.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return post_processed_key;
}

std::string ProfilePostProcessor::decodeEBCDICBytes(const char *p_ebcdic_bytes,
                                                    int length) {
  auto ebcdic_bytes_unique_ptr          = std::make_unique<char[]>(length);
  ebcdic_bytes_unique_ptr.get()[length] = 0;
  // Decode bytes
  std::strncpy(ebcdic_bytes_unique_ptr.get(), p_ebcdic_bytes, length);
  
  std::string ebcdic_string = std::string(ebcdic_bytes_unique_ptr.get());

  std::string utf8_string = toUTF8(ebcdic_string, "IBM-1047");

  size_t end = utf8_string.find_last_not_of(" ");

  if (end != std::string::npos) {
    return utf8_string.substr(0, end + 1);
  }
  return utf8_string;
}
}  // namespace SEAR

