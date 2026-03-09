#ifndef __SEAR_KEY_MAP_RESOURCE_H_
#define __SEAR_KEY_MAP_RESOURCE_H_

#include <stdbool.h>

#include "key_map_structs.hpp"

const trait_key_mapping_t RESOURCE_BASE_SEGMENT_MAP[]{
    {
     "base:access_list",   "aclcnt",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "base:access_count",  "aclacnt",
     TRAIT_TYPE_UINT, {false, false, false, false},
     },
    {
     "base:access_type",   "aclacs",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:access_id",    "aclid",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:conditional_access_list",  "acl2cnt",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "base:conditional_access_count", "acl2acnt",
     TRAIT_TYPE_UINT, {false, false, false, false},
     },
    {
     "base:conditional_access_type",  "acl2acs",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:conditional_access_class", "acl2cond",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:conditional_access_entity",  "acl2ent",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:conditional_access_id",   "acl2id",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:alter_access_count",  "acsaltr",
     TRAIT_TYPE_UINT, {false, false, false, false},
     },
    {
     "base:control_access_count",  "acscntl",
     TRAIT_TYPE_UINT, {false, false, false, false},
     },
    {
     "base:read_access_count",  "acsread",
     TRAIT_TYPE_UINT, {false, false, false, false},
     },
    {
     "base:update_access_count",  "acsupdt",
     TRAIT_TYPE_UINT, {false, false, false, false},
     },
    {
     "base:application_data", "appldata",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:audit_alter",  "audaltr",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:audit_control",  "audcntl",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:audit_none",  "audnone",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:audit_read",  "audread",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:audit_update",  "audupdt",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:security_category", "category",
     TRAIT_TYPE_STRING,    {true, true, true, false},
     },
    {
     "base:security_categories",  "numctgy",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
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
     "base:model_profile_class",   "fclass",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:model_profile_generic", "fgeneric",
     TRAIT_TYPE_BOOLEAN,  {true, false, false, false},
     },
    {
     "base:model_profile", "fprofile",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:model_profile_volume",  "fvolume",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:global_audit_alter", "gaudaltr",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:global_audit_control", "gaudcntl",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:global_audit_none", "gaudnone",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:global_audit_read", "gaudread",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:global_audit_update", "gaudupdt",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:is_generic",  "generic",
     TRAIT_TYPE_BOOLEAN, {false, false, false, false},
     },
    {
     "base:last_change_date",  "lchgdat",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:level",    "level",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:last_reference_date",  "lrefdat",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "base:member",   "member",
     TRAIT_TYPE_STRING,    {true, true, true, false},
     },
    {
     "base:members",   "member",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "base:notify_userid",   "notify",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:owner",    "owner",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:auditing",   "raudit",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "base:global_auditing",  "rgaudit",
     TRAIT_TYPE_STRING, {false, false, false, false},
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
     "base:single_dataset_tape_volume", "singldsn",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:time_zone", "timezone",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "base:tape_vtoc",    "tvtoc",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:universal_access",     "uacc",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:volume",   "volume",
     TRAIT_TYPE_STRING,   {false, true, true, false},
     },
    {
     "base:volumes",   "volcnt",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "base:warn_on_insufficient_access",  "warning",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "base:terminal_access_allowed_day", "whendays",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "base:terminal_access_allowed_days", "whendyct",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "base:terminal_access_allowed_time", "whentime",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     }
};

const trait_key_mapping_t RESOURCE_CDTINFO_KEY_MAP[]{
    {
     "cdtinfo:case_allowed",  "cdtcase",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cdtinfo:default_racroute_return_code", "cdtdftrc",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cdtinfo:valid_first_character", "cdtfirst",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cdtinfo:valid_first_characters",  "cdtfirn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "cdtinfo:generic_profile_checking",   "cdtgen",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cdtinfo:generic_profile_sharing",  "cdtgenl",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cdtinfo:grouping_class_name", "cdtgroup",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cdtinfo:key_qualifiers", "cdtkeyql",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cdtinfo:manditory_access_control_processing",   "cdtmac",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cdtinfo:max_length", "cdtmaxln",
     TRAIT_TYPE_UINT,   {true, false, false, true},
     },
    {
     "cdtinfo:max_length_entityx", "cdtmaxlx",
     TRAIT_TYPE_UINT,   {true, false, false, true},
     },
    {
     "cdtinfo:member", "cdtmembr",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cdtinfo:operations",  "cdtoper",
     TRAIT_TYPE_PSEUDO_BOOLEAN,   {true, false, false, true},
     },
    {
     "cdtinfo:valid_other_character", "cdtother",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cdtinfo:valid_other_characters",  "cdtothn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "cdtinfo:posit_number", "cdtposit",
     TRAIT_TYPE_UINT,   {true, false, false, true},
     },
    {
     "cdtinfo:profiles_allowed", "cdtprfal",
     TRAIT_TYPE_PSEUDO_BOOLEAN,   {true, false, false, true},
     },
    {
     "cdtinfo:raclist_allowed",  "cdtracl",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "cdtinfo:send_enf_signal_on_profile_creation",  "cdtsigl",
     TRAIT_TYPE_PSEUDO_BOOLEAN,   {true, false, false, true},
     },
    {
     "cdtinfo:security_label_required", "cdtslreq",
     TRAIT_TYPE_PSEUDO_BOOLEAN,   {true, false, false, true},
     },
    {
     "cdtinfo:default_universal_access",  "cdtuacc",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     }
};

const trait_key_mapping_t RESOURCE_CFDEF_KEY_MAP[]{
    {
     "cfdef:custom_field_data_type", "cfdtype",
     TRAIT_TYPE_STRING, {true, false, false, false},
     },
    {
     "cfdef:valid_first_characters", "cffirst",
     TRAIT_TYPE_STRING, {true, false, false, false},
     },
    {
     "cfdef:help_text",  "cfhelp",
     TRAIT_TYPE_STRING, {true, false, false, false},
     },
    {
     "cfdef:list_heading_text",  "cflist",
     TRAIT_TYPE_STRING, {true, false, false, false},
     },
    {
     "cfdef:mixed_case_allowed", "cfmixed",
     TRAIT_TYPE_PSEUDO_BOOLEAN, {true, false, false, false},
     },
    {
     "cfdef:min_numeric_value", "cfmnval",
     TRAIT_TYPE_UINT,  {true, false, false, true},
     },
    {
     "cfdef:max_field_length", "cfmxlen",
     TRAIT_TYPE_UINT, {true, false, false, false},
     },
    {
     "cfdef:max_numeric_value", "cfmxval",
     TRAIT_TYPE_UINT,  {true, false, false, true},
     },
    {
     "cfdef:valid_other_characters", "cfother",
     TRAIT_TYPE_STRING, {true, false, false, false},
     },
    {
     "cfdef:validation_rexx_exec", "cfvalrx",
     TRAIT_TYPE_STRING,  {true, false, false, true},
     }
};

const trait_key_mapping_t RESOURCE_CSDATA_KEY_MAP[]{
    {
     "csdata:*", "*",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t RESOURCE_DLFDATA_KEY_MAP[]{
    {
     "dlfdata:job_name",  "jobname",
     TRAIT_TYPE_STRING,     {true, true, true, true},
     },
    {
     "dlfdata:job_names", "jobnmcnt",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "dlfdata:retain_object_after_use",   "retain",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
};

const trait_key_mapping_t RESOURCE_EIM_KEY_MAP[]{
    {
     "eim:domain_distinguished_name", "domaindn",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "eim:kerberos_registry",  "kerbreg",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "eim:local_registry", "localreg",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "eim:options",  "options",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "eim:x509_registry",  "x509reg",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t RESOURCE_KERB_KEY_MAP[]{
    {
     "kerb:validate_addresses", "chkaddrs",
     TRAIT_TYPE_PSEUDO_BOOLEAN,   {true, false, false, true},
     },
    {
     "kerb:default_ticket_life", "deftktlf",
     TRAIT_TYPE_UINT,   {true, false, false, true},
     },
    {
     "kerb:encryption_algorithm",  "encrypt",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "kerb:encryption_algorithms", "encryptn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "kerb:realm_name", "kerbname",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "kerb:key_version",  "keyvers",
     TRAIT_TYPE_STRING, {false, false, false, false},
     },
    {
     "kerb:max_ticket_life", "maxtktlf",
     TRAIT_TYPE_UINT,   {true, false, false, true},
     },
    {
     "kerb:min_ticket_life", "mintktlf",
     TRAIT_TYPE_UINT,   {true, false, false, true},
     },
    {
     "kerb:password", "password",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     }
};

const trait_key_mapping_t RESOURCE_ICSF_KEY_MAP[]{
    {
     "icsf:certificate_label",  "crtlbls",
     TRAIT_TYPE_STRING,     {true, true, true, true},
     },
    {
     "icsf:certificate_labels", "crtlblct",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "icsf:exportable_public_keys",   "export",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "icsf:symmetric_export_public_key",  "keylbls",
     TRAIT_TYPE_STRING,     {true, true, true, true},
     },
    {
     "icsf:symmetric_export_public_keys", "keylblct",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "icsf:symmetric_cpacf_rewrap",  "scpwrap",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "icsf:symmetric_cpacf_rewrap_return",   "scpret",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     },
    {
     "icsf:asymetric_key_usage",    "usage",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "icsf:key_usage_options",  "usagect",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     }
};

const trait_key_mapping_t RESOURCE_ICTX_KEY_MAP[]{
    {
     "ictx:use_identity_map",    "domap",
     TRAIT_TYPE_BOOLEAN, {true, false, false, true},
     },
    {
     "ictx:require_identity_mapping",   "mapreq",
     TRAIT_TYPE_BOOLEAN, {true, false, false, true},
     },
    {
     "ictx:identity_map_timeout", "maptimeo",
     TRAIT_TYPE_UINT, {true, false, false, true},
     },
    {
     "ictx:cache_application_provided_identity_map",   "usemap",
     TRAIT_TYPE_BOOLEAN, {true, false, false, true},
     }
};

const trait_key_mapping_t RESOURCE_IDTPARMS_KEY_MAP[]{
    {
     "idtparms:pkcs11_token_name", "sigtoken",
     TRAIT_TYPE_STRING,  {true, false, false, true},
     },
    {
     "idtparms:pkcs11_sequence_number",  "sigseqn",
     TRAIT_TYPE_UINT,  {true, false, false, true},
     },
    {
     "idtparms:pkcs11_category",   "sigcat",
     TRAIT_TYPE_STRING,  {true, false, false, true},
     },
    {
     "idtparms:signature_algorithm",   "sigalg",
     TRAIT_TYPE_STRING,  {true, false, false, true},
     },
    {
     "idtparms:identity_token_timeout", "idttimeo",
     TRAIT_TYPE_UINT, {true, false, false, false},
     },
    {
     "idtparms:use_for_any_application",  "anyappl",
     TRAIT_TYPE_PSEUDO_BOOLEAN,  {true, false, false, true},
     }
};

const trait_key_mapping_t RESOURCE_JES_KEY_MAP[]{
    {
     "jes:icsf_key_label", "keylabel",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t RESOURCE_MFPOLICY_KEY_MAP[]{
    {
     "mfpolicy:factor",  "factors",
     TRAIT_TYPE_STRING,     {true, true, true, true},
     },
    {
     "mfpolicy:factors", "factorsn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "mfpolicy:token_timeout",  "timeout",
     TRAIT_TYPE_UINT, {false, false, false, false},
     },
    {
     "mfpolicy:reuse_token",    "reuse",
     TRAIT_TYPE_BOOLEAN,   {true, false, false, true},
     }
};

const trait_key_mapping_t RESOURCE_PROXY_KEY_MAP[]{
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

const trait_key_mapping_t RESOURCE_SESSION_KEY_MAP[]{
    {
     "session:security_checking_level",  "convsec",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "session:session_key_interval", "interval",
     TRAIT_TYPE_UINT, {true, false, false, true},
     },
    {
     "session:locked",     "lock",
     TRAIT_TYPE_BOOLEAN, {true, false, false, true},
     },
    {
     "session:session_key",  "sesskey",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t RESOURCE_SIGVER_KEY_MAP[]{
    {
     "sigver:fail_program_load_condition", "failload",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "sigver:log_signature_verification_events", "sigaudit",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "sigver:signature_required",  "sigreqd",
     TRAIT_TYPE_BOOLEAN, {true, false, false, true},
     }
};

const trait_key_mapping_t RESOURCE_SSIGNON_KEY_MAP[]{
    {
     "ssignon:encrypt_legacy_pass_ticket_key", "keycrypt",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "ssignon:enhanced_pass_ticket_label", "ptkeylab",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "ssignon:enhanced_pass_ticket_type",   "pttype",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "ssignon:enhanced_pass_ticket_timeout",  "pttimeo",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "ssignon:enhanced_pass_ticket_replay", "ptreplay",
     TRAIT_TYPE_BOOLEAN, {true, false, false, true},
     },
    {
     "ssignon:legacy_pass_ticket_label", "keylabel",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "ssignon:mask_legacy_pass_ticket_key",  "keymask",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t RESOURCE_STDATA_KEY_MAP[]{
    {
     "stdata:group",    "group",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "stdata:privileged", "privlege",
     TRAIT_TYPE_BOOLEAN, {true, false, false, true},
     },
    {
     "stdata:trace",    "trace",
     TRAIT_TYPE_BOOLEAN, {true, false, false, true},
     },
    {
     "stdata:trusted",  "trusted",
     TRAIT_TYPE_BOOLEAN, {true, false, false, true},
     },
    {
     "stdata:userid",     "user",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t RESOURCE_SVFMR_KEY_MAP[]{
    {
     "svfmr:parameter_list_name", "parmname",
     TRAIT_TYPE_STRING, {true, false, false, true},
     },
    {
     "svfmr:script_name",   "script",
     TRAIT_TYPE_STRING, {true, false, false, true},
     }
};

const trait_key_mapping_t RESOURCE_TME_KEY_MAP[]{
    {
     "tme:child", "children",
     TRAIT_TYPE_STRING,     {true, true, true, true},
     },
    {
     "tme:children",   "childn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "tme:group",   "groups",
     TRAIT_TYPE_STRING,     {true, true, true, true},
     },
    {
     "tme:groups",   "groupn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "tme:parent",   "parent",
     TRAIT_TYPE_STRING,   {true, false, false, true},
     },
    {
     "tme:resource", "resource",
     TRAIT_TYPE_STRING,     {true, true, true, true},
     },
    {
     "tme:resources",     "resn",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     },
    {
     "tme:role",    "roles",
     TRAIT_TYPE_STRING,  {true, false, false, false},
     },
    {
     "tme:roles",    "rolen",
     TRAIT_TYPE_REPEAT, {false, false, false, false},
     }
};

const segment_key_mapping_t RESOURCE_SEGMENT_KEY_MAP[] = {
    {    "base", field_count(RESOURCE_BASE_SEGMENT_MAP),RESOURCE_BASE_SEGMENT_MAP                                                        },
    { "cdtinfo",  field_count(RESOURCE_CDTINFO_KEY_MAP),
     RESOURCE_CDTINFO_KEY_MAP                                                     },
    {   "cfdef",    field_count(RESOURCE_CFDEF_KEY_MAP),    RESOURCE_CFDEF_KEY_MAP},
    {  "csdata",   field_count(RESOURCE_CSDATA_KEY_MAP),   RESOURCE_CSDATA_KEY_MAP},
    { "dlfdata",  field_count(RESOURCE_DLFDATA_KEY_MAP),
     RESOURCE_DLFDATA_KEY_MAP                                                     },
    {     "eim",      field_count(RESOURCE_EIM_KEY_MAP),      RESOURCE_EIM_KEY_MAP},
    {    "kerb",     field_count(RESOURCE_KERB_KEY_MAP),     RESOURCE_KERB_KEY_MAP},
    {    "icsf",     field_count(RESOURCE_ICSF_KEY_MAP),     RESOURCE_ICSF_KEY_MAP},
    {    "ictx",     field_count(RESOURCE_ICTX_KEY_MAP),     RESOURCE_ICTX_KEY_MAP},
    {"idtparms", field_count(RESOURCE_IDTPARMS_KEY_MAP),
     RESOURCE_IDTPARMS_KEY_MAP                                                    },
    {     "jes",      field_count(RESOURCE_JES_KEY_MAP),      RESOURCE_JES_KEY_MAP},
    {"mfpolicy", field_count(RESOURCE_MFPOLICY_KEY_MAP),
     RESOURCE_MFPOLICY_KEY_MAP                                                    },
    {   "proxy",    field_count(RESOURCE_PROXY_KEY_MAP),    RESOURCE_PROXY_KEY_MAP},
    { "session",  field_count(RESOURCE_SESSION_KEY_MAP),
     RESOURCE_SESSION_KEY_MAP                                                     },
    {  "sigver",   field_count(RESOURCE_SIGVER_KEY_MAP),   RESOURCE_SIGVER_KEY_MAP},
    { "ssignon",  field_count(RESOURCE_SSIGNON_KEY_MAP),
     RESOURCE_SSIGNON_KEY_MAP                                                     },
    {  "stdata",   field_count(RESOURCE_STDATA_KEY_MAP),   RESOURCE_STDATA_KEY_MAP},
    {   "svfmr",    field_count(RESOURCE_SVFMR_KEY_MAP),    RESOURCE_SVFMR_KEY_MAP},
    {     "tme",      field_count(RESOURCE_TME_KEY_MAP),      RESOURCE_TME_KEY_MAP}
};

#endif
