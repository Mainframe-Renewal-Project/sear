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
    std::string profile_name =
        ProfilePostProcessor::decodeEBCDICBytes(found_profiles[i], len);
    repeat_group_profiles.push_back(profile_name);
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
  
  profile["profile"]["rrsf:base"]["base:subsystem_name"] = ProfilePostProcessor::decodeEBCDICBytes(rrsf_extract_result->racf_subsystem_name, 4);
  profile["profile"]["rrsf:base"]["base:subsystem_userid"] = ProfilePostProcessor::decodeEBCDICBytes(rrsf_extract_result->racf_subsystem_userid, 8);
  profile["profile"]["rrsf:base"]["base:subsystem_operator_prefix"] = ProfilePostProcessor::decodeEBCDICBytes(rrsf_extract_result->subsystem_prefix, 8);
  profile["profile"]["rrsf:base"]["base:number_of_defined_nodes"] = rrsf_extract_result->number_of_rrsf_nodes;

  // Post process nodes if any are defined
  if (rrsf_extract_result->number_of_rrsf_nodes) {
    int first_node_offset = 544;

    // Node definitions
    std::vector<nlohmann::json> nodes;
    for (int i = 1; i <= ntohl(rrsf_extract_result->number_of_rrsf_nodes); i++) {
        const racf_rrsf_node_definitions_t *p_nodes =
        reinterpret_cast<const racf_rrsf_node_definitions_t *>(first_node_offset);

        nlohmann::json node_definition;
        node_definition["base:node_name"] = ProfilePostProcessor::decodeEBCDICBytes(p_nodes->rrsf_node_name,8);
        node_definition["base:date_of_last_received_work"] = ProfilePostProcessor::decodeEBCDICBytes(p_nodes->date_of_last_received_work,8);
        node_definition["base:time_of_last_received_work"] = ProfilePostProcessor::decodeEBCDICBytes(p_nodes->time_of_last_received_work,8);
        node_definition["base:node_state"] = p_nodes->rrsf_node_state;
        if (p_nodes->rrsf_protocol == 01) {
          node_definition["base:node_protocol"] = "appc";
        } else if (p_nodes->rrsf_protocol == 02) {
          node_definition["base:node_protocol"] = "tcp";
        } else {
          node_definition["base:node_protocol"] = "none";
        }
        nodes.push_back(node_definition);

        first_node_offset = first_node_offset + sizeof(p_nodes);  
    }
    profile["profile"]["rrsf:base"]["base:nodes"] = nodes;
  }

  if (rrsf_extract_result->bit_flags == RRSF_FULLRRSFCOMM_ACTIVE) {
    profile["profile"]["rrsf:base"]["base:full_rrsf_communication_active"] = true;
  } else {
    profile["profile"]["rrsf:base"]["base:full_rrsf_communication_active"] = false;
  }

  if (rrsf_extract_result->bit_flags == RRSF_SET_AUTODIRECT_ACTIVE) {
    profile["profile"]["rrsf:base"]["base:full_autodirect_active"] = true;
  } else {
    profile["profile"]["rrsf:base"]["base:full_autodirect_active"] = false;
  }

  if (rrsf_extract_result->bit_flags == RRSF_SET_AUTODIRECT_APP_UPDATES) {
    profile["profile"]["rrsf:base"]["base:autodirect_application_updates"] = true;
  } else {
    profile["profile"]["rrsf:base"]["base:autodirect_application_updates"] = false;
  }

  if (rrsf_extract_result->bit_flags == RRSF_SET_AUTO_PASSWORD_DIRECTION) {
    profile["profile"]["rrsf:base"]["base:autodirect_passwords"] = true;
  } else {
    profile["profile"]["rrsf:base"]["base:autodirect_passwords"] = false;
  }

  if (rrsf_extract_result->bit_flags == RRSF_SET_TRACE_APPC_ACTIVE) {
    profile["profile"]["rrsf:base"]["base:appc_trace_active"] = true;
  } else {
    profile["profile"]["rrsf:base"]["base:appc_trace_active"] = false;
  }

  if (rrsf_extract_result->bit_flags == RRSF_SET_TRACE_IMAGE_ACTIVE) {
    profile["profile"]["rrsf:base"]["base:image_trace_active"] = true;
  } else {
    profile["profile"]["rrsf:base"]["base:image_trace_active"] = false;
  }
  
  if (rrsf_extract_result->bit_flags == RRSF_SET_TRACE_SSL_ACTIVE) {
    profile["profile"]["rrsf:base"]["base:ssl_trace_active"] = true;
  } else {
    profile["profile"]["rrsf:base"]["base:ssl_trace_active"] = false;
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

