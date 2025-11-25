#ifndef __SEAR_KEY_MAP_H_
#define __SEAR_KEY_MAP_H_

#include <cstdint>
#include <nlohmann/json.hpp>

#include "key_map_dataset.hpp"
#include "key_map_group.hpp"
#include "key_map_group_connection.hpp"
#include "key_map_permission.hpp"
#include "key_map_racf_options.hpp"
#include "key_map_resource.hpp"
#include "key_map_structs.hpp"
#include "key_map_user.hpp"

// clang-format off
const key_mapping_t KEY_MAP[] = {
    { 
     "dataset",
     segment_count(DATASET_SEGMENT_KEY_MAP),
     DATASET_SEGMENT_KEY_MAP
     },
    { 
     "group", 
     segment_count(GROUP_SEGMENT_KEY_MAP),
     GROUP_SEGMENT_KEY_MAP
     },
    {
     "group-connection", 
     segment_count(GROUP_CONNECTION_SEGMENT_KEY_MAP),
     GROUP_CONNECTION_SEGMENT_KEY_MAP 
     },
    { 
     "permission",
     segment_count(PERMISSION_SEGMENT_KEY_MAP),
     PERMISSION_SEGMENT_KEY_MAP
     },
    {
     "racf-options",
     segment_count(RACF_OPTIONS_SEGMENT_KEY_MAP),
     RACF_OPTIONS_SEGMENT_KEY_MAP
     },
    {
     "resource",
     segment_count(RESOURCE_SEGMENT_KEY_MAP),
     RESOURCE_SEGMENT_KEY_MAP
     },
    {
     "user",
     segment_count(USER_SEGMENT_KEY_MAP),
     USER_SEGMENT_KEY_MAP
     }
};
// clang-format on

const char *get_sear_key(const char *profile_type, const char *segment,
                         const char *racf_key);

const char *get_racf_key(const char *profile_type, const char *segment,
                         const char *sear_key, int8_t trait_type,
                         int8_t trait_operator);

const char get_trait_type(const std::string &profile_type,
                          const std::string &segment,
                          const std::string &sear_key);

int8_t map_operator(std::string trait_operator);
int8_t map_trait_type(const nlohmann::json &trait);
std::string decode_data_type(uint8_t data_type_code);

#endif
