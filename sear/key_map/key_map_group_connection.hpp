#ifndef __SEAR_KEY_MAP_GROUP_CONNECTION_H_
#define __SEAR_KEY_MAP_GROUP_CONNECTION_H_

#include <stdbool.h>

#include "key_map_structs.hpp"

const trait_key_mapping_t GROUP_CONNECTION_BASE_SEGMENT_MAP[]{
    {
     "base:automatic_data_set_protection",     "adsp",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:auditor",  "auditor",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:authority",     "auth",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:connection_create_date", "cgauthda",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:connection_used_count", "cginitct",
     TRAIT_TYPE_UINT, {false, false, false, false},
     },
    {
     "base:connection_last_used_date", "cgljdate",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:connection_last_used_time", "cgljtime",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:group",    "group",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:group_access",   "grpacc",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:operations",     "oper",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:owner",    "owner",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:resume_date",   "resume",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:revoke_date",   "revoke",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:revoked", "revokefl",
     TRAIT_TYPE_BOOLEAN, {false, false, false, false},
     },
    {
     "base:special",  "special",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:universal_access",     "uacc",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     }
};

const segment_key_mapping_t GROUP_CONNECTION_SEGMENT_KEY_MAP[] = {
    {"base", field_count(GROUP_CONNECTION_BASE_SEGMENT_MAP),
     GROUP_CONNECTION_BASE_SEGMENT_MAP}
};

#endif
