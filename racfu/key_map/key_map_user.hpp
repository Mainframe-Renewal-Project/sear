#ifndef __RACFU_KEY_MAP_USER_H_
#define __RACFU_KEY_MAP_USER_H_

#include <stdbool.h>

#include "key_map_structs.hpp"

const trait_key_mapping_t USER_BASE_SEGMENT_MAP[]{
    {
     "base:automatic_data_set_protection",     "adsp",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:auditor",  "auditor",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:default_group_authority",     "auth",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:security_category", "category",
     TRAIT_TYPE_STRING,   {false, true, true, false},
     },
    {
     "base:security_categories",  "numctgy",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "base:class_authorization",   "clauth",
     TRAIT_TYPE_STRING,   {false, true, true, false},
     },
    {
     "base:class_authorizations",    "clcnt",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "base:group_connections", "connects",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "base:group_connection_automatic_data_set_protection",    "cadsp",
     TRAIT_TYPE_BOOLEAN, {false, false, false, false},
     },
    {
     "base:group_connection_auditor", "cauditor",
     TRAIT_TYPE_BOOLEAN, {false, false, false, false},
     },
    {
     "base:group_connection_create_date",  "cauthda",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:group_connection_group",   "cgroup",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:group_connection_data_set_access",  "cgrpacc",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:group_connection_used_count",  "cinitct",
     TRAIT_TYPE_UINT, {false, false, false, false},
     },
    {
     "base:group_connection_last_connect_date",  "cljdate",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:group_connection_last_connect_time",  "cljtime",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:group_connection_operations",    "coper",
     TRAIT_TYPE_BOOLEAN, {false, false, false, false},
     },
    {
     "base:group_connection_owner",   "cowner",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:group_connection_resume_date",  "cresume",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:group_connection_revoke_date",  "crevoke",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:group_connection_revoked", "crevokfl",
     TRAIT_TYPE_BOOLEAN, {false, false, false, false},
     },
    {
     "base:group_connection_special", "cspecial",
     TRAIT_TYPE_BOOLEAN, {false, false, false, false},
     },
    {
     "base:group_connection_universal_access",    "cuacc",
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
     "base:default_group",  "dfltgrp",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:password_expired",  "expired",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:mfa_factors",  "factorn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "base:mfa_active",  "facactv",
     TRAIT_TYPE_BOOLEAN, {false, false, false, false},
     },
    {
     "base:factor_tag_*",  "factag*",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:factor_value_*",  "facval*",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:group",    "group",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:group_data_set_access",   "grpacc",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:has_passphrase", "hasphras",
     TRAIT_TYPE_BOOLEAN, {false, false, false, false},
     },
    {
     "base:has_password",   "haspwd",
     TRAIT_TYPE_BOOLEAN, {false, false, false, false},
     },
    {
     "base:last_access_date", "lastdate",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:last_access_time", "lasttime",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:mfa_password_fallback",  "mfaflbk",
     TRAIT_TYPE_BOOLEAN, {false, false, false, false},
     },
    {
     "base:mfa_policy", "mfapolnm",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:mfa_policies",  "mfapoln",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "base:model_data_set",    "model",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:name",     "name",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:require_operator_id_card",  "oidcard",
     TRAIT_TYPE_BOOLEAN,  {false, false, false, true},
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
     "base:password_change_date", "passdate",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:password_change_interval",  "passint",
     TRAIT_TYPE_UINT, {false, false, false, false},
     },
    {
     "base:password", "password",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:passphrase",   "phrase",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:passphrase_change_date",  "phrdate",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:passphrase_change_interval",   "phrint",
     TRAIT_TYPE_UINT, {false, false, false, false},
     },
    {
     "base:passphrase_enveloped",   "pphenv",
     TRAIT_TYPE_BOOLEAN, {false, false, false, false},
     },
    {
     "base:protected", "protectd",
     TRAIT_TYPE_BOOLEAN, {false, false, false, false},
     },
    {
     "base:password_enveloped",   "pwdenv",
     TRAIT_TYPE_BOOLEAN, {false, false, false, false},
     },
    {
     "base:restrict_global_access_checking",     "rest",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
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
     "base:audit_responsibility",  "roaudit",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:security_label", "seclabel",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:security_level", "seclevel",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:special",  "special",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:universal_access",     "uacc",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:audit_logging",   "uaudit",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:logon_allowed_day", "whendays",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:logon_allowed_days", "whendyct",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "base:logon_allowed_when_service",  "whensrv",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:logon_allowed_time", "whentime",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     }
};

const trait_key_mapping_t USER_CICS_KEY_MAP[]{
    {
     "cics:operator_class",  "opclass",
     TRAIT_TYPE_STRING,     {true, true, true, true},
     },
    {
     "cics:operator_classes", "opclassn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "cics:operator_id",  "opident",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cics:operator_priority",   "opprty",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cics:resource_security_level_key",   "rslkey",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cics:resource_security_level_keys",  "rslkeyn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "cics:timeout",  "timeout",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cics:transaction_security_level_key",   "tslkey",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cics:transaction_security_level_keys",  "tslkeyn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "cics:force_signoff_when_xrf_takeover",  "xrfsoff",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     }
};

const trait_key_mapping_t USER_CSDATA_KEY_MAP[]{
    {
     "csdata:*", "*",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t USER_DCE_KEY_MAP[]{
    {
     "dce:auto_login",  "autolog",
     TRAIT_TYPE_BOOLEAN, {true, false, false, true},
     },
    {
     "dce:name",  "dcename",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "dce:home_cell", "homecell",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "dce:home_cell_uuid", "homeuuid",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "dce:uuid",     "uuid",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t USER_DFP_KEY_MAP[]{
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

const trait_key_mapping_t USER_EIM_KEY_MAP[]{
    {
     "eim:ldap_bind_profile", "ldapprof",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t USER_KERB_KEY_MAP[]{
    {
     "kerb:encryption_algorithm",  "encrypt",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "kerb:encryption_algorithms", "encryptn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "kerb:name", "kerbname",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "kerb:key_from",  "keyfrom",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "kerb:key_version",  "keyvers",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "kerb:max_ticket_life", "maxtktlf",
     TRAIT_TYPE_UINT,   {true, false, false, true},
     }
};

const trait_key_mapping_t USER_LANGUAGE_KEY_MAP[]{
    {
     "language:primary", "primary",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "language:secondary",  "second",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t USER_LNOTES_KEY_MAP[]{
    {
     "lnotes:zos_short_name", "sname",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t USER_MFA_KEY_MAP[]{
    {
     "mfa:factor",   "factor",
     TRAIT_TYPE_STRING, {true, false, false, false},
     },
    {
     "mfa:active",  "facactv",
     TRAIT_TYPE_BOOLEAN,  {true, false, false, true},
     },
    {
     "mfa:tags",  "factags",
     TRAIT_TYPE_STRING,   {true, false, true, true},
     },
    {
     "mfa:password_fallback",  "mfaflbk",
     TRAIT_TYPE_BOOLEAN,  {true, false, false, true},
     },
    {
     "mfa:mfa_policy", "mfapolnm",
     TRAIT_TYPE_STRING,  {false, true, true, false},
     }
};

const trait_key_mapping_t USER_NDS_KEY_MAP[]{
    {
     "nds:username", "uname",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t USER_NETVIEW_KEY_MAP[]{
    {
     "netview:default_mcs_console_name", "consname",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "netview:security_control_check",      "ctl",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "netview:domain",  "domains",
     TRAIT_TYPE_STRING,     {true, true, true, true},
     },
    {
     "netview:domains", "domainsn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "netview:logon_commands",       "ic",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "netview:receive_unsolicited_messages", "msgrecvr",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "netview:operator_graphic_monitor_facility_administration_allowed", "ngmfadmn",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "netview:operator_graphic_monitor_facility_display_authority", "ngmfvspn",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "netview:operator_scope_classes",  "opclass",
     TRAIT_TYPE_STRING,     {true, true, true, true},
     }
};

const trait_key_mapping_t USER_OMVS_KEY_MAP[]{
    {
     "omvs:max_address_space_size",   "assize",
     TRAIT_TYPE_UINT,  {true, false, false, true},
     },
    {
     "omvs:auto_uid",  "autouid",
     TRAIT_TYPE_BOOLEAN, {true, false, false, false},
     },
    {
     "omvs:max_cpu_time",  "cputime",
     TRAIT_TYPE_UINT,  {true, false, false, true},
     },
    {
     "omvs:max_files_per_process", "fileproc",
     TRAIT_TYPE_UINT,  {true, false, false, true},
     },
    {
     "omvs:home_directory",     "home",
     TRAIT_TYPE_STRING,  {true, false, false, true},
     },
    {
     "omvs:max_non_shared_memory", "memlimit",
     TRAIT_TYPE_STRING,  {true, false, false, true},
     },
    {
     "omvs:max_file_mapping_pages", "mmaparea",
     TRAIT_TYPE_UINT,  {true, false, false, true},
     },
    {
     "omvs:max_processes", "procuser",
     TRAIT_TYPE_UINT,  {true, false, false, true},
     },
    {
     "omvs:default_shell",  "program",
     TRAIT_TYPE_STRING,  {true, false, false, true},
     },
    {
     "omvs:shared",   "shared",
     TRAIT_TYPE_BOOLEAN, {true, false, false, false},
     },
    {
     "omvs:max_shared_memory", "shmemmax",
     TRAIT_TYPE_STRING,  {true, false, false, true},
     },
    {
     "omvs:max_threads",  "threads",
     TRAIT_TYPE_UINT,  {true, false, false, true},
     },
    {
     "omvs:uid",      "uid",
     TRAIT_TYPE_UINT,  {true, false, false, true},
     }
};

const trait_key_mapping_t USER_OPERPARM_KEY_MAP[]{
    {
     "operparm:alternate_console_group",   "altgrp",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "operparm:receive_automated_messages",     "auto",
     TRAIT_TYPE_PSEUDO_BOOLEAN,   {true, false, false, true},
     },
    {
     "operparm:command_target_system",   "cmdsys",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "operparm:receive_delete_operator_messages",      "dom",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "operparm:receive_hardcopy_messages",       "hc",
     TRAIT_TYPE_PSEUDO_BOOLEAN,   {true, false, false, true},
     },
    {
     "operparm:receive_internal_console_messages",   "intids",
     TRAIT_TYPE_PSEUDO_BOOLEAN,   {true, false, false, true},
     },
    {
     "operparm:console_searching_key",      "key",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "operparm:message_level",    "level",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "operparm:message_levels",   "leveln",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "operparm:log_command_responses",   "logcmd",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "operparm:message_format",    "mform",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "operparm:migration_id",    "migid",
     TRAIT_TYPE_PSEUDO_BOOLEAN,   {true, false, false, true},
     },
    {
     "operparm:monitor_event",  "monitor",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "operparm:monitor_events", "monitorn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "operparm:message_scope",   "mscope",
     TRAIT_TYPE_STRING,     {true, true, true, true},
     },
    {
     "operparm:message_scopes",  "mscopen",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "operparm:console_authority", "operauth",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "operparm:console_authorities", "operautn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "operparm:receive_routing_code", "routcode",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "operparm:receive_routing_codes", "routcodn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "operparm:message_queue_storage",  "storage",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "operparm:receive_undelivered_messages",       "ud",
     TRAIT_TYPE_PSEUDO_BOOLEAN,   {true, false, false, true},
     },
    {
     "operparm:receive_unknown_console_id_messages",  "unknids",
     TRAIT_TYPE_PSEUDO_BOOLEAN,   {true, false, false, true},
     }
};

const trait_key_mapping_t USER_OVM_KEY_MAP[]{
    {
     "ovm:file_system_root",   "fsroot",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "ovm:home_directory",    "vhome",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "ovm:default_shell", "vprogram",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "ovm:uid",     "vuid",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t USER_PROXY_KEY_MAP[]{
    {
     "proxy:bind_distinguished_name",   "binddn",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "proxy:bind_password",   "bindpw",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "proxy:ldap_host", "ldaphost",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t USER_TSO_KEY_MAP[]{
    {
     "tso:account_number",  "acctnum",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "tso:logon_command",  "command",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "tso:sysout_destination_id",     "dest",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "tso:hold_class", "hldclass",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "tso:job_class", "jobclass",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "tso:max_region_size",  "maxsize",
     TRAIT_TYPE_UINT, {true, false, false, true},
     },
    {
     "tso:message_class", "msgclass",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "tso:logon_procedure",     "proc",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "tso:security_label", "seclabel",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "tso:default_region_size",     "size",
     TRAIT_TYPE_UINT, {true, false, false, true},
     },
    {
     "tso:sysout_class", "sysoutcl",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "tso:data_set_allocation_unit",     "unit",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "tso:user_data", "userdata",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t USER_WORKATTR_KEY_MAP[]{
    {
     "workattr:account_number", "waaccnt",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "workattr:sysout_address_1", "waaddr1",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "workattr:sysout_address_2", "waaddr2",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "workattr:sysout_address_3", "waaddr3",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "workattr:sysout_address_4", "waaddr4",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "workattr:sysout_building",  "wabldg",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "workattr:sysout_department",  "wadept",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "workattr:sysout_user",  "waname",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "workattr:sysout_room",  "waroom",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "workattr:sysout_email", "waemail",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const segment_key_mapping_t USER_SEGMENT_KEY_MAP[] = {
    {    "base", field_count(USER_BASE_SEGMENT_MAP), USER_BASE_SEGMENT_MAP},
    {    "cics",     field_count(USER_CICS_KEY_MAP),     USER_CICS_KEY_MAP},
    {  "csdata",   field_count(USER_CSDATA_KEY_MAP),   USER_CSDATA_KEY_MAP},
    {     "dce",      field_count(USER_DCE_KEY_MAP),      USER_DCE_KEY_MAP},
    {     "dfp",      field_count(USER_DFP_KEY_MAP),      USER_DFP_KEY_MAP},
    {     "eim",      field_count(USER_EIM_KEY_MAP),      USER_EIM_KEY_MAP},
    {    "kerb",     field_count(USER_KERB_KEY_MAP),     USER_KERB_KEY_MAP},
    {"language", field_count(USER_LANGUAGE_KEY_MAP), USER_LANGUAGE_KEY_MAP},
    {  "lnotes",   field_count(USER_LNOTES_KEY_MAP),   USER_LNOTES_KEY_MAP},
    {     "mfa",      field_count(USER_MFA_KEY_MAP),      USER_MFA_KEY_MAP},
    {     "nds",      field_count(USER_NDS_KEY_MAP),      USER_NDS_KEY_MAP},
    { "netview",  field_count(USER_NETVIEW_KEY_MAP),  USER_NETVIEW_KEY_MAP},
    {    "omvs",     field_count(USER_OMVS_KEY_MAP),     USER_OMVS_KEY_MAP},
    {"operparm", field_count(USER_OPERPARM_KEY_MAP), USER_OPERPARM_KEY_MAP},
    {     "ovm",      field_count(USER_OVM_KEY_MAP),      USER_OVM_KEY_MAP},
    {   "proxy",    field_count(USER_PROXY_KEY_MAP),    USER_PROXY_KEY_MAP},
    {     "tso",      field_count(USER_TSO_KEY_MAP),      USER_TSO_KEY_MAP},
    {"workattr", field_count(USER_WORKATTR_KEY_MAP), USER_WORKATTR_KEY_MAP}
};

#endif
