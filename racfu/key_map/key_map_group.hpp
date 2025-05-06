#ifndef __RACFU_KEY_MAP_GROUP_H_
#define __RACFU_KEY_MAP_GROUP_H_

#include <stdbool.h>

#include "key_map_structs.hpp"

const trait_key_mapping_t GROUP_BASE_SEGMENT_MAP[]{
    {
     "base:connected_users", "connects",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "base:connected_user_authority",    "gauth",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:connected_userid",  "guserid",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:create_date", "creatdat",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:installation_data",     "data",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:data_set_model",    "model",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:owner",    "owner",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:subgroups", "subgrpct",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "base:subgroup", "subgroup",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:superior_group", "supgroup",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:terminal_universal_access", "termuacc",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:universal", "universl",
     TRAIT_TYPE_BOOLEAN,  {true, false, false, false},
     }
};

const trait_key_mapping_t GROUP_CSDATA_KEY_MAP[]{
    {
     "csdata:*", "*",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t GROUP_DFP_KEY_MAP[]{
    {
     "dfp:data_application", "dataappl",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "dfp:data_class", "dataclas",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "dfp:management_class", "mgmtclas",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "dfp:storage_class", "storclas",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t GROUP_OMVS_KEY_MAP[]{
    {
     "omvs:auto_gid", "autogid",
     TRAIT_TYPE_BOOLEAN, {true, false, false, false},
     },
    {
     "omvs:gid",     "gid",
     TRAIT_TYPE_UINT,  {true, false, false, true},
     },
    {
     "omvs:shared",  "shared",
     TRAIT_TYPE_STRING, {true, false, false, false},
     }
};

const trait_key_mapping_t GROUP_OVM_KEY_MAP[]{
    {
     "ovm:gid", "gid",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t GROUP_TME_KEY_MAP[]{
    {
     "tme:roles", "roles",
     TRAIT_TYPE_STRING, {true, false, false, false},
     }
};

const segment_key_mapping_t GROUP_SEGMENT_KEY_MAP[] = {
    {  "base", field_count(GROUP_BASE_SEGMENT_MAP), GROUP_BASE_SEGMENT_MAP},
    {"csdata",   field_count(GROUP_CSDATA_KEY_MAP),   GROUP_CSDATA_KEY_MAP},
    {   "dfp",      field_count(GROUP_DFP_KEY_MAP),      GROUP_DFP_KEY_MAP},
    {  "omvs",     field_count(GROUP_OMVS_KEY_MAP),     GROUP_OMVS_KEY_MAP},
    {   "ovm",      field_count(GROUP_OVM_KEY_MAP),      GROUP_OVM_KEY_MAP},
    {   "tme",      field_count(GROUP_TME_KEY_MAP),      GROUP_TME_KEY_MAP}
};

#endif
