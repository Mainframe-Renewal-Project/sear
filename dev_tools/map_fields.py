import json

valid_segment_traits = {}

valid_segment_traits["u_admin"] = {
            "base": {
                "base:automatic_data_set_protection": "adsp",
                "base:auditor": "auditor",
                "base:default_group_authority": "auth",
                "base:security_categories": "category",
                "base:class_authorizations": "clauth",
                "base:installation_data": "data",
                "base:default_group": "defgroup",
                "base:password_expired": "expired",
                "base:group": "group",
                "base:group_data_set_access": "grpacc",
                "base:model_data_set": "model",
                "base:name": "name",
                "base:require_operator_id_card": "oidcard",
                "base:operations": "oper",
                "base:owner": "owner",
                "base:password": "password",
                "base:passphrase": "phrase",
                "base:restrict_global_access_checking": "rest",
                "base:resume_date": "resumedate",
                "base:revoke_date": "revokedate",
                "base:audit_responsibility": "roaudit",
                "base:security_label": "seclabel",
                "base:security_level": "seclevel",
                "base:special": "special",
                "base:universal_access": "uacc",
                "base:audit_logging": "uaudit",
                "base:logon_allowed_days": "whendays",
                "base:logon_allowed_time": "whentime",
            },
            "cics": {
                "cics:operator_classes": "opclass",
                "cics:operator_id": "opident",
                "cics:operator_priority": "opprty",
                "cics:rsl_key": "rslkey",
                "cics:timeout": "timeout",
                "cics:tsl_key": "tslkey",
                "cics:xrf_sign_off": "force",
            },
            "dce": {
                "dce:auto_login": "autolog",
                "dce:name": "dcename",
                "dce:home_cell": "homecell",
                "dce:home_cell_uuid": "homeuuid",
                "dce:uuid": "uuid",
            },
            "dfp": {
                "dfp:data_application": "dataappl",
                "dfp:data_class": "dataclas",
                "dfp:management_class": "mgmtclass",
                "dfp:storage_class": "storclas",
            },
            "eim": {"eim:ldap_bind_profile": "ldapprof"},
            "kerb": {
                "kerb:encryption_algorithm": "encrypt",
                "kerb:name": "kerbname",
                "kerb:max_ticket_life": "maxtktlf",
            },
            "language": {
                "language:primary": "primary",
                "language:secondary": "secondary",
            },
            "lnotes": {"lnotes:zos_short_name": "sname"},
            "mfa": {
                "mfa:factor": "factor",
                "mfa:active": "facactv",
                "mfa:tags": "factags",
                "mfa:password_fallback": "mfaflbk",
                "mfa:policy": "mfapolnm",
            },
            "nds": {"nds:username": "uname"},
            "netview": {
                "netview:default_console": "consid",
                "netview:security_check": "secctl",
                "netview:domains": "nvdomains",
                "netview:logon_commands": "ic",
                "netview:recieve_unsolicited_messages": "msgrec",
                "netview:graphic_monitor_facility_admin": "ngmfadmn",
                "netview:view_span": "gmfadmin",
                "netview:operator_scope_classes": "opclass",
            },
            "omvs": {
                "omvs:max_address_space_size": "assize",
                "omvs:auto_uid": "autouid",
                "omvs:max_cpu_time": "cputime",
                "omvs:max_files_per_process": "filemax",
                "omvs:home_directory": "home",
                "omvs:max_non_shared_memory": "memlim",
                "omvs:max_file_mapping_pages": "mmaparea",
                "omvs:max_processes": "procmax",
                "omvs:default_shell": "pgm",
                "omvs:shared": "shared",
                "omvs:max_shared_memory": "shmemmax",
                "omvs:max_threads": "threads",
                "omvs:uid": "uid",
            },
            "operparm": {
                "operparm:alternate_console_group": "altgrp",
                "operparm:recieve_automated_messages": "auto",
                "operparm:command_target_systems": "cmdsys",
                "operparm:recieve_delete_operator_messages": "dom",
                "operparm:recieve_hardcopy_messages": "hc",
                "operparm:recieve_internal_console_messages": "intid",
                "operparm:console_searching_key": "key",
                "operparm:message_level": "level",
                "operparm:log_command_responses": "logcmd",
                "operparm:message_format": "mform",
                "operparm:migration_id": "migid",
                "operparm:events_to_monitor": "mon",
                "operparm:message_scope": "mscope",
                "operparm:operator_command_authority": "auth",
                "operparm:recieve_routing_codes": "routcode",
                "operparm:message_queue_storage": "storage",
                "operparm:recieve_undelivered_messages": "ud",
                "operparm:recieve_messages_from_unknown_console_ids": "unkids",
            },
            "ovm": {
                "ovm:file_system_root": "fsroot",
                "ovm:home_directory": "vhome",
                "ovm:default_shell": "vprogram",
                "ovm:uid": "vuid",
            },
            "proxy": {
                "proxy:bind_distinguished_name": "binddn",
                "proxy:bind_password": "bindpw",
                "proxy:ldap_host": "ldaphost",
            },
            "tso": {
                "tso:account_number": "acctnum",
                "tso:logon_command": "command",
                "tso:sysout_destination_id": "dest",
                "tso:hold_class": "holdclass",
                "tso:job_class": "jobclass",
                "tso:max_region_size": "maxsize",
                "tso:message_class": "msgclass",
                "tso:logon_procedure": "proc",
                "tso:security_label": "seclabel",
                "tso:default_region_size": "size",
                "tso:sysout_class": "sysclass",
                "tso:data_set_allocation_unit": "unit",
                "tso:user_data": "userdata",
            },
            "workattr": {
                "workattr:account_number": "waaccnt",
                "workattr:sysout_address_1": "waaddr1",
                "workattr:sysout_address_2": "waaddr2",
                "workattr:sysout_address_3": "waaddr3",
                "workattr:sysout_address_4": "waaddr4",
                "workattr:sysout_building": "wabldg",
                "workattr:sysout_department": "wadept",
                "workattr:sysout_user": "waname",
                "workattr:sysout_room": "waroom",
                "workattr:sysout_email": "waemail",
            },
        }

valid_segment_traits["perm_admin"] = {
            "base": {
                "base:access": "access",
                "base:delete": "racf:delete",
                "base:model_profile_class": "racf:fclass",
                "base:model_profile": "racf:fprofile",
                "base:model_profile_generic": "racf:fgeneric",
                "base:model_profile_volume": "racf:fvolume",
                "base:auth_id": "authid",
                "base:reset": "racf:reset",
                "base:volume": "racf:volume",
                "base:when_partner_lu_name": "racf:whenappc",
                "base:when_console": "racf:whencons",
                "base:when_jes": "racf:whenjes",
                "base:when_program": "racf:whenprog",
                "base:when_servauth": "racf:whenserv",
                "base:when_sms": "racf:whensms",
                "base:when_db2_role": "racf:whensqlr",
                "base:when_service": "racf:whensrv",
                "base:when_system": "racf:whensys",
                "base:when_terminal": "racf:whenterm",
            }
        }

valid_segment_traits["gc_admin"] = {
            "base": {
                "base:automatic_data_set_protection": "racf:adsp",
                "base:auditor": "racf:auditor",
                "base:group_authority": "racf:auth",
                "base:group": "racf:group",
                "base:group_access": "racf:grpacc",
                "base:operations": "racf:oper",
                "base:owner": "racf:owner",
                "base:resume": "racf:resume",
                "base:revoke": "racf:revoke",
                "base:special": "racf:special",
                "base:universal_access": "racf:uacc",
            }
        }

valid_segment_traits["d_admin"] = {
            "base": {
                "base:alter_volume": "racf:altvol",
                "base:audit_alter": "racf:audaltr",
                "base:audit_control": "racf:audcntl",
                "base:audit_none": "racf:audnone",
                "base:audit_read": "racf:audread",
                "base:audit_update": "racf:audupdt",
                "base:security_categories": "racf:category",
                "base:installation_data": "racf:data",
                "base:erase_data_sets_on_delete": "racf:erase",
                "base:model_profile_class": "racf:fclass",
                "base:model_profile_generic": "racf:fgeneric",
                "base:tape_data_set_file_sequence_number": "racf:fileseq",
                "base:model_profile": "racf:from",
                "base:model_profile_volume": "racf:fvolume",
                "base:global_audit_alter": "racf:gaudaltr",
                "base:global_audit_control": "racf:gaudcntl",
                "base:global_audit_none": "racf:gaudnone",
                "base:global_audit_read": "racf:gaudread",
                "base:global_audit_update": "racf:gaudupdt",
                "base:level": "racf:level",
                "base:data_set_model_profile": "racf:model",
                "base:notify_userid": "racf:notify",
                "base:owner": "racf:owner",
                "base:tape_data_set_security_retention_period": "racf:retpd",
                "base:security_label": "racf:seclabel",
                "base:security_level": "racf:seclevel",
                "base:generic_not_allowed": "racf:set",
                "base:generic_allowed": "racf:setonly",
                "base:use_tape_data_set_profile": "racf:tape",
                "base:universal_access": "racf:uacc",
                "base:data_set_allocation_unit": "racf:unit",
                "base:volumes": "racf:volume",
                "base:warn_on_insufficient_access": "racf:warning",
            },
            "dfp": {"dfp:owner": "racf:resowner", "dfp:ckds_data_key": "racf:datakey"},
            "tme": {"tme:roles": "racf:roles"},
        }

valid_segment_traits["g_admin"] = {
            "base": {
                "base:installation_data": "racf:data",
                "base:data_set_model": "racf:model",
                "base:owner": "racf:owner",
                "base:superior_group": "racf:supgroup",
                "base:terminal_universal_access": "racf:termuacc",
                "base:universal": "racf:universl",
            },
            "dfp": {
                "dfp:data_application": "dataappl",
                "dfp:data_class": "dataclas",
                "dfp:management_class": "mgmtclas",
                "dfp:storage_class": "storclas",
            },
            "omvs": {
                "omvs:auto_gid": "racf:autogid",
                "omvs:gid": "gid",
                "omvs:shared": "racf:shared",
            },
            "ovm": {"ovm:gid": "racf:gid"},
            "tme": {"tme:roles": "racf:roles"},
        }

valid_segment_traits["p_admin"] = {
            "base": {
                "base:application_data": "racf:appldata",
                "base:audit_alter": "racf:audaltr",
                "base:audit_control": "racf:audcntl",
                "base:audit_none": "racf:audnone",
                "base:audit_read": "racf:audread",
                "base:audit_update": "racf:audupdt",
                "base:security_categories": "racf:category",
                "base:installation_data": "racf:data",
                "base:model_profile_class": "racf:fclass",
                "base:model_profile_generic": "racf:fgeneric",
                "base:model_profile": "racf:fprofile",
                "base:model_profile_volume": "racf:fvolume",
                "base:global_audit_alter": "racf:gaudaltr",
                "base:global_audit_control": "racf:gaudcntl",
                "base:global_audit_none": "racf:gaudnone",
                "base:global_audit_read": "racf:gaudread",
                "base:global_audit_update": "racf:gaudupdt",
                "base:level": "racf:level",
                "base:member": "racf:member",
                "base:notify_userid": "racf:notify",
                "base:owner": "racf:owner",
                "base:security_label": "racf:seclabel",
                "base:security_level": "racf:seclevel",
                "base:single_data_set_tape_volume": "racf:singldsn",
                "base:time_zone": "racf:timezone",
                "base:tape_vtoc": "racf:tvtoc",
                "base:universal_access": "racf:uacc",
                "base:volumes": "racf:volume",
                "base:warn_on_insufficient_access": "racf:warning",
                "base:terminal_access_allowed_days": "racf:whendays",
                "base:terminal_access_allowed_time": "racf:whentime",
            },
            "cdtinfo": {
                "cdtinfo:case_allowed": "case",
                "cdtinfo:default_racroute_return_code": "defaultrc",
                "cdtinfo:valid_first_characters": "first",
                "cdtinfo:generic_profile_checking": "generic",
                "cdtinfo:generic_profile_sharing": "genlist",
                "cdtinfo:grouping_class_name": "grouping",
                "cdtinfo:key_qualifiers": "keyqual",
                "cdtinfo:mandatory_access_control_processing": "macprocessing",
                "cdtinfo:max_length": "maxlenx",
                "cdtinfo:max_length_entityx": "maxlength",
                "cdtinfo:member_class_name": "member",
                "cdtinfo:operations": "operations",
                "cdtinfo:valid_other_characters": "other",
                "cdtinfo:posit_number": "posit",
                "cdtinfo:profiles_allowed": "profilesallowed",
                "cdtinfo:raclist_allowed": "raclist",
                "cdtinfo:send_enf_signal_on_profile_creation": "signal",
                "cdtinfo:security_label_required": "seclabelrequired",
                "cdtinfo:default_universal_access": "defaultuacc",
            },
            "cfdef": {
                "cfdef:custom_field_data_type": "type",
                "cfdef:valid_first_characters": "first",
                "cfdef:help_text": "help",
                "cfdef:list_heading_text": "listhead",
                "cfdef:mixed_case_allowed": "mixed",
                "cfdef:min_numeric_value": "minvalue",
                "cfdef:max_field_length": "mxlength",
                "cfdef:max_numeric_value": "maxvalue",
                "cfdef:valid_other_characters": "other",
                "cfdef:validation_rexx_exec": "racf:cfvalrx",
            },
            "dlfdata": {
                "dlfdata:job_names": "racf:jobname",
                "dlfdata:retain": "racf:retain",
            },
            "eim": {
                "eim:domain_distinguished_name": "domaindn",
                "eim:kerberos_registry": "kerberg",
                "eim:local_registry": "localreg",
                "eim:options": "options",
                "eim:x509_registry": "X509reg",
            },
            "kerb": {
                "kerb:validate_addresses": "checkaddrs",
                "kerb:default_ticket_life": "deftktlife",
                "kerb:encryption_algorithms": "encrypt",
                "kerb:realm_name": "kerbname",
                "kerb:max_ticket_life": "maxtktlf",
                "kerb:min_ticket_life": "mintklife",
                "kerb:password": "password",
            },
            "icsf": {
                "icsf:symmetric_export_certificates": "symexportcert",
                "icsf:exportable_public_keys": "symexportable",
                "icsf:symmetric_export_public_keys": "symexportkey",
                "icsf:symmetric_cpacf_rewrap": "symcpacfwrap",
                "icsf:symmetric_cpacf_rewrap_return": "symcpacfret",
                "icsf:asymmetric_key_usage": "asymusage",
            },
            "ictx": {
                "ictx:use_identity_map": "domap",
                "ictx:require_identity_mapping": "mapreq",
                "ictx:identity_map_timeout": "maptimeo",
                "ictx:cache_application_provided_identity_map": "usemap",
            },
            "idtparms": {
                "idtparms:token": "sigtoken",
                "idtparms:sequence_number": "sigseqnum",
                "idtparms:category": "sigcat",
                "idtparms:signature_algorithm": "sigalg",
                "idtparms:identity_token_timeout": "idttimeout",
                "idtparms:use_for_any_application": "anyappl",
            },
            "jes": {"jes:key_label": "racf:keylabel"},
            "mfpolicy": {
                "mfpolicy:factors": "racf:factors",
                "mfpolicy:token_timeout": "racf:timeout",
                "mfpolicy:reuse_token": "racf:reuse",
            },
            "proxy": {
                "proxy:bind_distinguished_name": "binddn",
                "proxy:bind_password": "bindpw",
                "proxy:ldap_host": "ldaphost",
            },
            "session": {
                "session:security_checking_level": "racf:convsec",
                "session:session_key_interval": "racf:interval",
                "session:locked": "racf:lock",
                "session:session_key": "racf:sesskey",
            },
            "sigver": {
                "sigver:fail_program_load_condition": "failload",
                "sigver:log_signature_verification_events": "sigaudit",
                "sigver:signature_required": "sigrequired",
            },
            "ssignon": {
                "ssignon:encrypt_legacy_pass_ticket_key": "racf:keycrypt",
                "ssignon:enhanced_pass_ticket_label": "ptkeylab",
                "ssignon:enhanced_pass_ticket_type": "pttype",
                "ssignon:enhanced_pass_ticket_timeout": "pttimeo",
                "ssignon:enhanced_pass_ticket_replay": "ptreplay",
                "ssignon:legacy_pass_ticket_label": "racf:keylabel",
                "ssignon:mask_legacy_pass_ticket_key": "racf:keymask",
            },
            "stdata": {
                "stdata:group": "racf:group",
                "stdata:privileged": "racf:privlege",
                "stdata:trace": "racf:trace",
                "stdata:trusted": "racf:trusted",
                "stdata:user": "racf:user",
            },
            "svfmr": {
                "svfmr:parameter_list_name": "racf:parmname",
                "svfmr:script_name": "racf:script",
            },
            "tme": {
                "tme:children": "racf:children",
                "tme:groups": "racf:groups",
                "tme:parent": "racf:parent",
                "tme:resource": "racf:resource",
                "tme:roles": "racf:roles",
            },
        }

valid_segment_traits["s_admin"] = {
            "base": {
                "base:active_classes": "racf:classact",
                "base:add_creator": "racf:addcreat",
                "base:automatic_data_set_protection": "racf:adsp",
                "base:application_logon_auditing": "racf:applaudt",
                "base:audit_classes": "racf:audit",
                "base:uncataloged_data_set_access": "racf:catdsns",
                "base:log_racf_command_violations": "racf:cmdviol",
                "base:security_label_compatibility_mode": "racf:compmode",
                "base:enhanced_generic_naming": "racf:egn",
                "base:erase_data_sets_on_delete": "racf:erase",
                "base:erase_data_sets_on_delete_all": "racf:eraseall",
                "base:erase_data_sets_on_delete_security_level": "racf:erasesec",
                "base:generic_command_classes": "racf:gencmd",
                "base:generic_profile_checking_classes": "racf:generic",
                "base:generic_profile_sharing_classes": "racf:genlist",
                "base:generic_owner": "racf:genowner",
                "base:global_access_classes": "racf:global",
                "base:list_of_groups_access_checking": "racf:grplist",
                "base:password_history": "racf:history",
                "base:revoke_inactive_userids_interval": "racf:inactive",
                "base:record_user_verification_statistics": "racf:initstat",
                "base:max_password_change_interval": "racf:interval",
                "base:jes_batch": "racf:jesbatch",
                "base:jes_early_verification": "racf:jesearly",
                "base:jes_network_user": "racf:jesnje",
                "base:jes_undefined_user": "racf:jesundef",
                "base:jes_execution_batch_monitoring": "racf:jesxbm",
                "base:kerberos_encryption_level": "racf:kerblvl",
                "base:list": "racf:list",
                "base:audit_log_always_classes": "racf:logalwys",
                "base:audit_log_default_classes": "racf:logdeflt",
                "base:audit_log_failure_classes": "racf:logfail",
                "base:audit_log_never_classes": "racf:lognever",
                "base:audit_log_success_classes": "racf:logsucc",
                "base:min_password_change_interval": "racf:minchang",
                "base:mixed_case_password_support": "racf:mixdcase",
                "base:multi_level_security_address_space": "racf:mlactive",
                "base:multi_level_security_file_system": "racf:mlfs",
                "base:multi_level_security_interprocess": "racf:mlipc",
                "base:multi_level_security_file_names": "racf:mlnames",
                "base:multi_level_security_logon": "racf:mlquiet",
                "base:multi_level_security_declassification": "racf:mls",
                "base:multi_level_security_label_alteration": "racf:mlstable",
                "base:profile_modelling": "racf:model",
                "base:profile_modelling_generation_data_group": "racf:modgdg",
                "base:profile_modelling_group": "racf:modgroup",
                "base:profile_modelling_user": "racf:moduser",
                "base:log_operator_actions": "racf:operaudt",
                "base:passphrase_change_interval": "racf:phrint",
                "base:data_set_single_level_name_prefix_protection": "racf:prefix",
                "base:primary_language": "racf:primlang",
                "base:protect_all_data_sets": "racf:protall",
                "base:password_encryption_algorithm": "racf:pwdalg",
                "base:special_character_password_support": "racf:pwdspec",
                "base:raclist": "racf:raclist",
                "base:log_real_data_set_name": "racf:realdsn",
                "base:refresh": "racf:refresh",
                "base:tape_data_set_security_retention_period": "racf:retpd",
                "base:max_incorrect_password_attempts": "racf:revoke",
                "base:password_rules": "racf:rules",
                "base:password_rule_1": "racf:rule1",
                "base:password_rule_2": "racf:rule2",
                "base:password_rule_3": "racf:rule3",
                "base:password_rule_4": "racf:rule4",
                "base:password_rule_5": "racf:rule5",
                "base:password_rule_6": "racf:rule6",
                "base:password_rule_7": "racf:rule7",
                "base:password_rule_8": "racf:rule8",
                "base:rvary_switch_password": "racf:rvarswpw",
                "base:rvary_status_password": "racf:rvarstpw",
                "base:log_commands_issued_by_special_users": "racf:saudit",
                "base:security_label_control": "racf:seclabct",
                "base:secondary_language": "racf:seclang",
                "base:max_session_key_interval": "racf:sessint",
                "base:security_label_auditing": "racf:slabaudt",
                "base:security_label_system": "racf:slbysys",
                "base:security_level_auditing": "racf:slevaudt",
                "base:statistics_classes": "racf:classtat",
                "base:tape_data_set_protection": "racf:tapedsn",
                "base:terminal_universal_access": "racf:terminal",
                "base:password_expiration_warning": "racf:warning",
                "base:program_control": "racf:whenprog",
            }
        }

class func_group:
    name = ''
    myDict = {}

    def __init__(self,name):
        self.name = name
        with open(self.name+'.json') as fp:
            self.myDict = json.load(fp)
    
    def get_segment(self,field):
        cln_field = field.replace(' ','').strip().lower()
        for seg in self.myDict.keys():
            if cln_field in self.myDict[seg].keys():
                return seg
        return -1
    
    def get_fieldmap(self,field):
        cln_field = field.replace(' ','').strip().lower()
        return_list = {"racf_name": cln_field}
        for seg in self.myDict.keys():
            if cln_field in self.myDict[seg].keys():
                flags = self.myDict[seg][cln_field].keys()
                #print(flags)
                return_list["operators"] = []
                return_list["data_type"] = "string"
                if "'Y'" in flags:
                    return_list["operators"].append("set")
                    if "bool" in self.myDict[seg][cln_field]["'Y'"].keys() and self.myDict[seg][cln_field]["'Y'"]["bool"]:
                        return_list["data_type"] = "bool"
                if "'N'" in flags:
                    return_list["operators"].append("del")     
                if "'A'" in flags:
                    return_list["operators"].append("add")
                if "'D'" in flags:
                    return_list["operators"].append("remove")
                return return_list
        return -1
    
    def test_field(self,field):
        cln_field = field.replace(' ','').strip().lower()
        seg = self.get_segment(field)
        fld_map = self.get_fieldmap(field)
        print("Field: %s Segment: %s Tag: %s" % (cln_field,seg,fld_map))
    
    def test_field_list(self,list):
        for field in list:
            self.test_field(field)
    
    def build_seg_map(self):
        seg_map = {}
        for seg in self.myDict.keys():
            for entry in self.myDict[seg]:
                if seg not in seg_map.keys():
                    seg_map[seg] = {}
                seg_map[seg][f"{seg}:{entry}"] = self.get_fieldmap(entry)
        return seg_map

def map_admin_type(admin_key: str):
    if admin_key == "u":
        return "user"
    if admin_key == "g":
        return "group"
    if admin_key == "d":
        return "data_set"
    if admin_key == "p":
        return "resource"
    if admin_key == "perm":
        return "permission"
    if admin_key == "gc":
        return "group_connection"
    if admin_key == "s":
        return "racf_options"
    
def generate_header_file(admin_type: str ):
    true_admin_type = map_admin_type(admin_type.split("_")[0]).upper()
    admin = func_group(admin_type)
    map = admin.build_seg_map()

    print(true_admin_type, map.keys(), valid_segment_traits[admin_type].keys() )

    for segment in valid_segment_traits[admin_type]:
        for trait in valid_segment_traits[admin_type][segment]:
            racf_name = valid_segment_traits[admin_type][segment][trait]
            if ':' in racf_name:
                racf_name = racf_name.split(':')[1]
            print(f"racf_name: {racf_name}, sear_name: {trait}")
            if f"{segment}:{racf_name}" in map[segment].keys():
                map[segment][f"{segment}:{racf_name}"]["sear_name"] = trait
    
    #print(map)

    header = f"#ifndef __SEAR_KEY_MAP_{true_admin_type}_H_\n#define __SEAR_KEY_MAP_{true_admin_type}_H_\n\n#include <stdbool.h>\n\n#include \"key_map_structs.hpp\"\n\n"

    for segment in map:
        if segment == "base":
            header += f"const trait_key_mapping_t {true_admin_type}_{segment.upper()}_SEGMENT_MAP[]{{\n"
        else:
            header += f"const trait_key_mapping_t {true_admin_type}_{segment.upper()}_KEY_MAP[]{{\n"
        for trait in map[segment]:
            if "sear_name" in map[segment][trait]:
                sear_name = map[segment][trait]["sear_name"]
            else:
                sear_name = "GIVEMEASEARNAME"
            racf_name = map[segment][trait]["racf_name"]
            trait_type = map[segment][trait]["data_type"].upper()
            if trait_type == "BOOL":
                trait_type = "BOOLEAN"
            set_allowed = "true" if "set" in map[segment][trait]["operators"] else "false"
            del_allowed = "true" if "del" in map[segment][trait]["operators"] else "false"
            add_allowed = "true" if "add" in map[segment][trait]["operators"] else "false"
            rem_allowed = "true" if "remove" in map[segment][trait]["operators"] else "false"
            header += f"    {{\n    \"{sear_name}\", \"{racf_name}\",\n    TRAIT_TYPE_{trait_type}, "+"{"+f"{set_allowed}, {add_allowed}, {rem_allowed}, {del_allowed}"+"},\n    },\n"
        header += "};\n\n\n"
    
    header += f"const segment_key_mapping_t {true_admin_type}_SEGMENT_KEY_MAP[] = {{\n"
    for segment in map:
        if segment == "base":
            header += f"    {{\"{segment}\", field_count({true_admin_type}_{segment.upper()}_SEGMENT_MAP), {true_admin_type}_{segment.upper()}_SEGMENT_MAP"+"},\n"
        else:
            header += f"    {{\"{segment}\", field_count({true_admin_type}_{segment.upper()}_KEY_MAP), {true_admin_type}_{segment.upper()}_KEY_MAP"+"},\n"
    header += "};\n\n#endif"  

    with open(f"key_map_{true_admin_type.lower()}.hpp", 'w') as fp:
          fp.write(header)        
    #print(header)

#u_admin = func_group('u_admin')
#p_admin = func_group('p_admin')
#d_admin = func_group('d_admin')
#perm_admin = func_group('perm_admin')
#setr_admin = func_group('s_admin')
#g_admin = func_group('g_admin')
#gc_admin = func_group('gc_admin')

#u_map = u_admin.build_seg_map()

admin_types = [ "u_admin", "p_admin", "d_admin", "gc_admin", "perm_admin", "s_admin", "g_admin"]
for type in admin_types:
    generate_header_file(type)
#print(u_map)
#print(p_admin.build_seg_map())
#print(d_admin.build_seg_map())
#print(perm_admin.build_seg_map())
#print(setr_admin.build_seg_map())
#print(g_admin.build_seg_map())
#print(gc_admin.build_seg_map())
