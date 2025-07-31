#include "trait_validation.hpp"

#include <algorithm>
#include <cstdint>
#include <nlohmann/json.hpp>
#include <regex>
#include <string>

#include "key_map.hpp"
#include "sear_error.hpp"

void validate_traits(const std::string& profile_type,
                     SEAR::SecurityRequest& request) {
  // Parses the json for the traits (segment-trait information) passed in a
  // json object and validates the structure, format and types of this data
  std::string item_segment, item_trait, item_operator;
  const char* translatedKey;

  std::regex segment_trait_key_regex{R"~((([a-z]*):*)([a-z]*):(.*))~"};
  std::smatch segment_trait_key_data;

  std::vector<std::string> errors;

  const nlohmann::json& traits = request.getTraits();

  for (const auto& item : traits.items()) {
    if (!regex_match(item.key(), segment_trait_key_data,
                     segment_trait_key_regex)) {
      // Track any entries that do not match proper syntax
      errors.push_back("'" + item.key() +
                       "' is not in '<segment>:<trait>' or "
                       "'<operator>:<segment>:<trait>' format");
      continue;
    }
    if (segment_trait_key_data[3] == "") {
      item_operator = "";
      item_segment  = segment_trait_key_data[2];
    } else {
      item_operator = segment_trait_key_data[2];
      item_segment  = segment_trait_key_data[3];
    }
    item_trait = segment_trait_key_data[4];

    // Get passed operation and validate it
    int8_t init_trait_operator = map_operator(item_operator);
    int8_t trait_operator      = init_trait_operator;
    if (trait_operator == OPERATOR_BAD) {
      errors.push_back("'" + item_operator + "' is not a valid trait operator");
      continue;
    }
    int8_t trait_type = map_trait_type(item.value());
    if ((trait_operator == OPERATOR_DELETE) &&
        (trait_type != TRAIT_TYPE_NULL)) {
      errors.push_back("'delete' operator for '" + item_segment + ":" +
                       item_trait + "' can only be used with a 'null' value");
      continue;
    }
    if (trait_type == TRAIT_TYPE_NULL) {
      // Validate that NULL is not used with non-delete operator specified
      if ((trait_operator != OPERATOR_ANY) &&
          (trait_operator != OPERATOR_DELETE)) {
        errors.push_back("'" + item_operator + "' operator for '" +
                         item_segment + ":" + item_trait +
                         "' can NOT be used with a 'null' value");
        continue;
      }
      trait_operator = OPERATOR_DELETE;
    }
    if (trait_type == TRAIT_TYPE_BOOLEAN) {
      // Set operator based on boolean value
      trait_operator = (item.value()) ? OPERATOR_SET : OPERATOR_DELETE;
    }
    int8_t expected_type = get_trait_type(profile_type, item_segment,
                                          item_segment + ":" + item_trait);
    // Validate Segment-Trait by ensuring a TRAIT_TYPE is found
    if (expected_type == TRAIT_TYPE_BAD) {
      errors.push_back("'" + item_segment + ":" + item_trait +
                       "' is not a valid trait");
      continue;
    }
    if ((expected_type == TRAIT_TYPE_BOOLEAN) &&
        (trait_type == TRAIT_TYPE_NULL) &&
        (trait_operator != init_trait_operator)) {
      // Validate that NULL is not used for Boolean Segment-Traits
      if (item_operator.empty()) {
        item_operator = "set";
      }
      errors.push_back("'" + item_operator + "' operator for '" + item_segment +
                       ":" + item_trait +
                       +"' can NOT be used with a 'null' value");
      continue;
    }
    validate_json_value_to_string(reinterpret_cast<const nlohmann::json&>(item),
                                  expected_type, errors);
    // Ensure that the type of data provided for the trait matches the
    // expected TRAIT_TYPE
    if ((trait_type != expected_type) && !(trait_type == TRAIT_TYPE_NULL) &&
        ((expected_type != TRAIT_TYPE_PSEUDO_BOOLEAN) ||
         (trait_type != TRAIT_TYPE_BOOLEAN))) {
      if (expected_type == TRAIT_TYPE_REPEAT &&
          trait_type == TRAIT_TYPE_STRING) {
        trait_type = TRAIT_TYPE_REPEAT;
      } else {
        errors.push_back("'" + item.key() + "' must be " +
                         decode_data_type(expected_type) + "' value");
        continue;
      }
    }
    if (expected_type == TRAIT_TYPE_PSEUDO_BOOLEAN) {
      trait_type = TRAIT_TYPE_PSEUDO_BOOLEAN;
    }
    translatedKey = get_racf_key(profile_type.c_str(), item_segment.c_str(),
                                 (item_segment + ":" + item_trait).c_str(),
                                 trait_type, trait_operator);
    // If we could not find the RACF key with this function, the operation is
    // bad because we check the Segment-Trait combination above
    if ((translatedKey == NULL) && (trait_operator == init_trait_operator)) {
      errors.push_back("'" + item_operator + "' is not a valid operator for '" +
                       item_segment + ":" + item_trait + "'");
    } else if ((translatedKey == NULL) && (trait_type != TRAIT_TYPE_NULL)) {
      // Validate that the boolean-influenced operator is allowed
      std::string value = item.value().get<bool>() ? "true" : "false";
      errors.push_back("'" + value + "' is not a valid value for '" +
                       item_segment + ":" + item_trait + "'");
    } else if (translatedKey == NULL) {
      // Validate that NULL is not used for Segment-Traits that don't allow
      // DELETE
      errors.push_back("'" + item_segment + ":" + item_trait +
                       "' can NOT be used with a 'null' value");
    }
    // Passed all of our validation so we go around the loop again
  }
  if (!errors.empty()) {
    request.setSEARReturnCode(8);
    throw SEAR::SEARError(errors);
  }
}

void validate_json_value_to_string(const nlohmann::json& trait,
                                   char expected_type,
                                   std::vector<std::string>& errors) {
  if (trait.is_string()) {
    return;
  }
  if (trait.is_array()) {
    for (const auto& item : trait.items()) {
      if (!item.value().is_string()) {
        errors.push_back("'" + item.key() + "' must be " +
                         decode_data_type(expected_type) + "' value");
        return;
      }
    }
  }
}
