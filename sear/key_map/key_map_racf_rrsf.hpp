#ifndef __SEAR_KEY_MAP_RACF_RRSF_H_
#define __SEAR_KEY_MAP_RACF_RRSF_H_

#include <stdbool.h>

#include "key_map_structs.hpp"

const trait_key_mapping_t RACF_RRSF_BASE_SEGMENT_MAP[]{

};

const segment_key_mapping_t RACF_RRSF_SEGMENT_KEY_MAP[] = {
    {"base", field_count(RACF_RRSF_BASE_SEGMENT_MAP),
     RACF_RRSF_BASE_SEGMENT_MAP}
};

#endif
