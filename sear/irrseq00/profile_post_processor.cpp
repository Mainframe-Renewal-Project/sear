#include "profile_post_processor.hpp"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// Use ntohl() to convert 32-bit values from big endian to little endian.
// use ntohs() to convert 16-bit values from big endian to little endian.
// On z/OS these macros do nothing since "network order" and z/Architecture are
// both big endian. This is only necessary for unit testing off platform.
#include <arpa/inet.h>

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
  auto ascii_bytes_unique_ptr          = std::make_unique<char[]>(length);
  ascii_bytes_unique_ptr.get()[length] = 0;
  // Decode bytes
  std::strncpy(ascii_bytes_unique_ptr.get(), p_ebcdic_bytes, length);
  __e2a_l(ascii_bytes_unique_ptr.get(), length);
  std::string ascii_string = std::string(ascii_bytes_unique_ptr.get());
  // Convert to lowercase
  size_t end = ascii_string.find_last_not_of(" ");
  if (end != std::string::npos) {
    return ascii_string.substr(0, end + 1);
  }
  return ascii_string;
}
}  // namespace SEAR
