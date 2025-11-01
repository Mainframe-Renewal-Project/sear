#include "key_map.hpp"

#include <stdio.h>

#include <cstring>

static const trait_key_mapping_t *get_key_mapping(
    const char *profile_type,  // The profile type (i.e., 'user')
    const char *segment,       // The segment      (i.e., 'omvs')
    const char *racf_key,      // The RACF key     (i.e., 'program')
    const char *sear_key,      // The SEAR key    (i.e., 'omvs:default_shell')
    int8_t trait_type,         // The trait type   (i.e.,  'TRAIT_TYPE_UINT')
    int8_t trait_operator,     // The operator     (i.e.,  'OPERATOR_SET')
    bool extract);             // Set to 'true' to get the SEAR Key
                               // Set to 'false' to get the RACF Key

static bool check_trait_type(int8_t actual, int8_t expected);

static bool check_trait_operator(int8_t trait_operator,
                                 const operators_allowed_t *operators_allowed);

const char *get_sear_key(const char *profile_type, const char *segment,
                         const char *racf_key) {
  const trait_key_mapping_t *key_mapping =
      get_key_mapping(profile_type, segment, racf_key, nullptr, TRAIT_TYPE_NULL,
                      OPERATOR_ANY, true);
  if (key_mapping == nullptr) {
    return nullptr;
  }
  return key_mapping->sear_key;
}

const char *get_racf_key(const char *profile_type, const char *segment,
                         const char *sear_key, int8_t trait_type,
                         int8_t trait_operator) {
  const trait_key_mapping_t *key_mapping =
      get_key_mapping(profile_type, segment, nullptr, sear_key, trait_type,
                      trait_operator, false);
  if (key_mapping == nullptr) {
    return nullptr;
  }
  return key_mapping->racf_key;
}

const char get_trait_type(const std::string &profile_type,
                          const std::string &segment,
                          const std::string &sear_key) {
  const trait_key_mapping_t *key_mapping =
      get_key_mapping(profile_type.c_str(), segment.c_str(), nullptr,
                      sear_key.c_str(), TRAIT_TYPE_NULL, OPERATOR_ANY, false);
  if (key_mapping == nullptr) {
    return TRAIT_TYPE_BAD;
  }
  return key_mapping->trait_type;
}

static const trait_key_mapping_t *get_key_mapping(
    const char *profile_type, const char *segment, const char *racf_key,
    const char *sear_key, int8_t trait_type, int8_t trait_operator,
    bool extract) {
  bool trait_type_good;
  bool trait_operator_good;
  // Search for segment key mappings for the provided profile type
  for (int i = 0; i < sizeof(KEY_MAP) / sizeof(key_mapping_t); i++) {
    if (strcmp(profile_type, KEY_MAP[i].profile_type) == 0) {
      // Find the trait key mappings for the provided segment
      for (int j = 0; j < KEY_MAP[i].size; j++) {
        if (strcmp(segment, KEY_MAP[i].segments[j].segment) == 0) {
          // Find the trait key mapping.
          for (int k = 0; k < KEY_MAP[i].segments[j].size; k++) {
            // Get the SEAR key mapping for profile extract
            if (extract == true) {
              size_t functional_racf_key_length =
                  strlen(KEY_MAP[i].segments[j].traits[k].racf_key);
              if (KEY_MAP[i]
                      .segments[j]
                      .traits[k]
                      .racf_key[functional_racf_key_length - 1] == '*') {
                functional_racf_key_length--;
              } else {
                functional_racf_key_length = strlen(racf_key);
              }
              if (strncmp(racf_key, KEY_MAP[i].segments[j].traits[k].racf_key,
                          functional_racf_key_length) == 0) {
                return &KEY_MAP[i].segments[j].traits[k];
              }
            }
            // Get the RACF key mapping for add/alter/delete
            else {
              size_t functional_sear_key_length =
                  strlen(KEY_MAP[i].segments[j].traits[k].sear_key);
              bool wildcard = false;
              if (KEY_MAP[i]
                      .segments[j]
                      .traits[k]
                      .sear_key[functional_sear_key_length - 1] == '*') {
                functional_sear_key_length--;
                wildcard = true;
              }
              if (strncmp(sear_key, KEY_MAP[i].segments[j].traits[k].sear_key,
                          functional_sear_key_length) == 0 &&
                  (wildcard ||
                   functional_sear_key_length == strlen(sear_key))) {
                // Check trait type
                trait_type_good = check_trait_type(
                    trait_type, KEY_MAP[i].segments[j].traits[k].trait_type);
                if (trait_type_good == false) {
                  return nullptr;
                }
                // Check trait operator
                trait_operator_good = check_trait_operator(
                    trait_operator,
                    &KEY_MAP[i].segments[j].traits[k].operators_allowed);
                if (trait_operator_good == false) {
                  return nullptr;
                }
                return &KEY_MAP[i].segments[j].traits[k];
              }
            }
          }
        }
      }
    }
  }
  return nullptr;
}

static bool check_trait_type(int8_t actual, int8_t expected) {
  if (actual == TRAIT_TYPE_NULL) {
    return true;
  }
  if (actual != expected) {
    return false;
  }
  return true;
}

static bool check_trait_operator(int8_t trait_operator,
                                 const operators_allowed_t *operators_allowed) {
  switch (trait_operator) {
    case OPERATOR_ANY:
      return true;
    case OPERATOR_SET:
      return operators_allowed->set_allowed;
    case OPERATOR_ADD:
      return operators_allowed->add_allowed;
    case OPERATOR_REMOVE:
      return operators_allowed->remove_allowed;
    case OPERATOR_DELETE:
      return operators_allowed->delete_allowed;
    default:
      return false;
  }
}

int8_t map_operator(std::string trait_operator) {
  if (trait_operator.empty()) {
    return OPERATOR_ANY;
  }
  std::transform(trait_operator.begin(), trait_operator.end(),
                 trait_operator.begin(), ::tolower);
  if (trait_operator == "set") {
    return OPERATOR_SET;
  }
  if (trait_operator == "add") {
    return OPERATOR_ADD;
  }
  if (trait_operator == "remove") {
    return OPERATOR_REMOVE;
  }
  if (trait_operator == "delete") {
    return OPERATOR_DELETE;
  }
  return OPERATOR_BAD;
}

int8_t map_trait_type(const nlohmann::json &trait) {
  if (trait.is_null()) {
    return TRAIT_TYPE_NULL;
  }
  if (trait.is_boolean()) {
    return TRAIT_TYPE_BOOLEAN;
  }
  if (trait.is_string() or trait.is_array()) {
    return TRAIT_TYPE_STRING;
  }
  if (trait.is_number_unsigned()) {
    return TRAIT_TYPE_UINT;
  }
  return TRAIT_TYPE_BAD;
}

std::string decode_data_type(uint8_t data_type_code) {
  switch (data_type_code) {
    case TRAIT_TYPE_BOOLEAN:
      return "a 'boolean";
    case TRAIT_TYPE_UINT:
      return "an 'unsigned integer";
    case TRAIT_TYPE_STRING:
      return "a 'string";
    default:
      return "any data type";
  }
}
