#ifndef __RACFU_KEY_MAP_RACF_OPTIONS_H_
#define __RACFU_KEY_MAP_RACF_OPTIONS_H_

#include <stdbool.h>

#include "key_map_structs.hpp"

const trait_key_mapping_t RACF_OPTIONS_BASE_SEGMENT_MAP[]{
    {
     "base:add_creator_to_access_list", "addcreat",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:automatic_data_set_protection",     "adsp",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:application_logon_auditing", "applaudt",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:audit_classes",    "audit",
     TRAIT_TYPE_REPEAT,   {false, true, true, false},
     },
    {
     "base:uncataloged_data_set_access",  "catdsns",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:active_classes", "classact",
     TRAIT_TYPE_REPEAT,   {false, true, true, false},
     },
    {
     "base:statistics_classes", "classtat",
     TRAIT_TYPE_REPEAT,   {false, true, true, false},
     },
    {
     "base:log_racf_command_violations",  "cmdviol",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:security_label_compatibility_mode", "compmode",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:enhanced_generic_naming",      "egn",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:erase_data_sets_on_delete",    "erase",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:erase_data_sets_on_delete_all", "eraseall",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:erase_data_sets_on_delete_security_level", "erasesec",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:generic_command_classes",   "gencmd",
     TRAIT_TYPE_REPEAT,   {false, true, true, false},
     },
    {
     "base:generic_profile_checking_classes",  "generic",
     TRAIT_TYPE_REPEAT,   {false, true, true, false},
     },
    {
     "base:generic_profile_sharing_classes",  "genlist",
     TRAIT_TYPE_REPEAT,   {false, true, true, false},
     },
    {
     "base:generic_owner", "genowner",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:global_access_classes",   "global",
     TRAIT_TYPE_REPEAT,   {false, true, true, false},
     },
    {
     "base:list_of_groups_access_checking",  "grplist",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:password_history",  "history",
     TRAIT_TYPE_UINT,   {true, false, false, true},
     },
    {
     "base:revoke_inactive_userids_interval", "inactive",
     TRAIT_TYPE_UINT,   {true, false, false, true},
     },
    {
     "base:record_user_verification_statistics", "initstat",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:max_password_change_interval", "interval",
     TRAIT_TYPE_UINT,   {true, false, false, true},
     },
    {
     "base:jes_batch", "jesbatch",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:jes_early_verification", "jesearly",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:jes_network_user",   "jesnje",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:jes_undefined_user", "jesundef",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:jes_execution_batch_monitoring",   "jesxbm",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:kerberos_encryption_level",  "kerblvl",
     TRAIT_TYPE_UINT,  {true, false, false, false},
     },
    {
     "base:audit_log_always_classes", "logalwys",
     TRAIT_TYPE_REPEAT,  {true, false, false, false},
     },
    {
     "base:audit_log_default_classes", "logdeflt",
     TRAIT_TYPE_REPEAT,  {true, false, false, false},
     },
    {
     "base:audit_log_failure_classes",  "logfail",
     TRAIT_TYPE_REPEAT,  {true, false, false, false},
     },
    {
     "base:audit_log_never_classes", "lognever",
     TRAIT_TYPE_REPEAT,  {true, false, false, false},
     },
    {
     "base:audit_log_success_classes",  "logsucc",
     TRAIT_TYPE_REPEAT,  {true, false, false, false},
     },
    {
     "base:min_password_change_interval", "minchang",
     TRAIT_TYPE_UINT,  {true, false, false, false},
     },
    {
     "base:mixed_case_password_support", "mixdcase",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:multi_level_security_address_space", "mlactive",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:multi_level_security_file_system",     "mlfs",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:multi_level_security_interprocess",    "mlipc",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:multi_level_security_file_names",  "mlnames",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:multi_level_security_logon",  "mlquiet",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:multi_level_security_declassification",      "mls",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:multi_level_security_label_alteration", "mlstable",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:profile_modelling",    "model",
     TRAIT_TYPE_BOOLEAN,  {false, false, false, true},
     },
    {
     "base:profile_modelling_generation_data_group",   "modgdg",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:profile_modelling_group", "modgroup",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:profile_modelling_user",  "moduser",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:log_operator_actions", "operaudt",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:passphrase_change_interval",   "phrint",
     TRAIT_TYPE_UINT,  {true, false, false, false},
     },
    {
     "base:data_set_single_level_name_prefix_protection",   "prefix",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:primary_language", "primlang",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:protect_all_data_sets",  "protall",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:password_encryption_algorithm",   "pwdalg",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:special_character_password_support",  "pwdspec",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:raclist",  "raclist",
     TRAIT_TYPE_REPEAT,   {false, true, true, false},
     },
    {
     "base:log_real_data_set_name",  "realdsn",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:refresh",  "refresh",
     TRAIT_TYPE_BOOLEAN,  {true, false, false, false},
     },
    {
     "base:tape_data_set_security_retention_period",    "retpd",
     TRAIT_TYPE_UINT,  {true, false, false, false},
     },
    {
     "base:max_incorrect_password_attempts",   "revoke",
     TRAIT_TYPE_UINT,   {true, false, false, true},
     },
    {
     "base:password_rules",    "rules",
     TRAIT_TYPE_BOOLEAN,  {false, false, false, true},
     },
    {
     "base:password_rule_1",    "rule1",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:password_rule_2",    "rule2",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:password_rule_3",    "rule3",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:password_rule_4",    "rule4",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:password_rule_5",    "rule5",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:password_rule_6",    "rule6",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:password_rule_7",    "rule7",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:password_rule_8",    "rule8",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:rvary_status_password_format", "rvarstfm",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:rvary_status_password", "rvarstpw",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:rvary_switch_password_format", "rvarswfm",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:rvary_switch_password", "rvarswpw",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:log_commands_issuesd_by_special_users",   "saudit",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:security_label_control", "seclabct",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:secondary_language",  "seclang",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:max_session_key_interval",  "sessint",
     TRAIT_TYPE_UINT,   {true, false, false, true},
     },
    {
     "base:security_label_auditing", "slabaudt",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:security_label_system",  "slbysys",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:security_level_auditing", "slevaudt",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:tape_data_set_protection",  "tapedsn",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:terminal_universal_access", "terminal",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:password_expiration_warning",  "warning",
     TRAIT_TYPE_UINT,   {true, false, false, true},
     },
    {
     "base:program_control", "whenprog",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     }
};

const segment_key_mapping_t RACF_OPTIONS_SEGMENT_KEY_MAP[] = {
    {"base", field_count(RACF_OPTIONS_BASE_SEGMENT_MAP),
     RACF_OPTIONS_BASE_SEGMENT_MAP}
};

#endif
