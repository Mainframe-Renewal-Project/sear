---
layout: default
parent: Traits
nav_order: 1
---

# User Traits

The following tables describes the user segments and traits that are supported for add and alter operations, and returned by extract operations.
{: .fs-6 .fw-300 }

&nbsp;

{: .note }
> _More information about **RACF Keys** can be found [here](https://www.ibm.com/docs/en/zos/latest?topic=services-reference-documentation-tables)._

&nbsp;

{: .note }
> _See [Data Types](../data_types) for more information about **Data Types**._

&nbsp;

{: .note }
> _See [Operators](../operators) for more information about **Operator** usage._

## `base`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"base:automatic_data_set_protection"` | `adsp` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:auditor"` | `auditor` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:default_group_authority"` | `auth` | `string` | `"set"` | `"add"`<br>`"alter"` |
| `"base:security_category"` | `category` | `string` | `"add"`<br>`"remove"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:security_categories"` | `numctgy` | `repeat` | N/A | `"extract"` |
| `"base:class_authorization"` | `clauth` | `string` | `"add"`<br>`"remove"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:class_authorizations"` | `clcnt` | `repeat` | N/A | `"extract"` |
| `"base:group_connections"` | `connects` | `repeat` | N/A | `"extract"` |
| `"base:group_connection_automatic_data_set_protection"` | `cadsp` | `boolean` | N/A | `"extract"` |
| `"base:group_connection_auditor"` | `cauditor` | `boolean` | N/A | `"extract"` |
| `"base:group_connection_create_date"` | `cauthda` | `string` | N/A | `"extract"` |
| `"base:group_connection_group"` | `cgroup` | `string` | N/A | `"extract"` |
| `"base:group_connection_data_set_access"` | `cgrpacc` | `string` | N/A | `"extract"` |
| `"base:group_connection_used_count"` | `cinitct` | `uint` | N/A | `"extract"` |
| `"base:group_connection_last_connect_date"` | `cljdate` | `string` | N/A | `"extract"` |
| `"base:group_connection_last_connect_time"` | `cljtime` | `string` | N/A | `"extract"` |
| `"base:group_connection_operations"` | `coper` | `boolean` | N/A | `"extract"` |
| `"base:group_connection_owner"` | `cowner` | `string` | N/A | `"extract"` |
| `"base:group_connection_resume_date"` | `cresume` | `string` | N/A | `"extract"` |
| `"base:group_connection_revoke_date"` | `crevoke` | `string` | N/A | `"extract"` |
| `"base:group_connection_revoked"` | `crevokfl` | `boolean` | N/A | `"extract"` |
| `"base:group_connection_special"` | `cspecial` | `boolean` | N/A | `"extract"` |
| `"base:group_connection_universal_access"` | `cuacc` | `string` | N/A | `"extract"` |
| `"base:create_date"` | `creatdat` | `string` | N/A | `"extract"` |
| `"base:installation_data"` | `data` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:default_group"` | `dfltgrp` | `string` | `"set"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:password_expired"` | `expired` | `boolean` | `"set"`<br>`"delete"` | `"alter"` |
| `"base:mfa_factors"` | `factorn` | `repeat` | N/A | `"extract"` |
| `"base:mfa_active"` | `facactv` | `boolean` | N/A | `"extract"` |
| `"base:group"` | `group` | `string` | `"set"` | `"alter"` |
| `"base:group_data_set_access"` | `grpacc` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:has_passphrase"` | `hasphras` | `boolean` | N/A | `"extract"` |
| `"base:has_password"` | `haspwd` | `boolean` | N/A | `"extract"` |
| `"base:last_access_date"` | `lastdate` | `string` | N/A | `"extract"` |
| `"base:last_acess_time"` | `lasttime` | `string` | N/A | `"extract"` |
| `"base:mfa_password_fallback"` | `mfaflbk` | `boolean` | N/A | `"extract"` |
| `"base:mfa_policy"` | `mfapolnm` | `string` | N/A | `"extract"` |
| `"base:mfa_policies"` | `mfapoln` | `repeat` | N/A | `"extract"` |
| `"base:model_data_set"` | `model` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:name"` | `name` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:require_operator_id_card"` | `oidcard` | `boolean` | `"delete"` | `"add"`<br>`"alter"` |
| `"base:operations"` | `oper` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:owner"` | `owner` | `string` | `"set"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:password_change_date"` | `passdate` | `string` | N/A | `"extract"` |
| `"base:password_change_interval"` | `passint` | `uint` | N/A | `"extract"` |
| `"base:password"` | `password` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:passphrase"` | `phrase` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:passphrase_change_date"` | `phrdate` | `string` | N/A | `"extract"` |
| `"base:passphrase_change_interval"` | `phrint` | `uint` | N/A | `"extract"` |
| `"base:passphrase_enveloped"` | `pphenv` | `boolean` | N/A | `"extract"` |
| `"base:protected"` | `protectd` | `boolean` | N/A | `"extract"` |
| `"base:password_enveloped"` | `pwdenv` | `boolean` | N/A | `"extract"` |
| `"base:restrict_global_access_checking"` | `rest` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:resume_date"` | `resume` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:revoke_date"` | `revoke` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:revoked"` | `revokefl` | `boolean` | N/A | `"extract"` |
| `"base:audit_responsibility"` | `roaudit` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:security_label"` | `seclabel` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:security_level"` | `seclevel` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:special"` | `special` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:universal_access"` | `uacc` | `string` | `"set"` | `"add"`<br>`"alter"` |
| `"base:audit_logging"` | `uaudit` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:logon_allowed_day"` | `whendays` | `string` | `"set"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:logon_allowed_days"` | `whendyct` | `repeat` | N/A | `"extract"` |
| `"base:logon_allowed_time"` | `whentime` | `string` | `"set"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `cics`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"cics:operator_class"` | `opclass` | `string` | `"set"`<br>`"add"`<br>`"remove"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cics:operator_classes"` | `opclassn` | `repeat` | N/A | `"extract"` |
| `"cics:operator_id"` | `opident` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cics:operator_priority"` | `opprty` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cics:resource_security_level_key"` | `rslkey` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cics:resource_security_level_keys"` | `rslkeyn` | `repeat` | N/A | `"extract"` |
| `"cics:timeout"` | `timeout` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cics:transaction_security_level_key"` | `tslkey` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cics:transaction_security_level_keys"` | `tslkeyn` | `repeat` | N/A | `"extract"` |
| `"cics:force_signoff_when_xrf_takeover"` | `xrfsoff` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `dce`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"dce:auto_login"` | `autolog` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"dce:name"` | `dcename` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"dce:home_cell"` | `homecell` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"dce:home_cell_uuid"` | `homeuuid` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"dce:uuid"` | `uuid` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `dfp`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"dfp:data_application"` | `dataappl` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"dfp:data_class"` | `dataclas` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"dfp:management_class"` | `mgmtclas` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"dfp:storage_class"` | `storclas` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `eim`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"eim:ldap_bind_profile"` | `ldapprof` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `kerb`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"kerb:encryption_algorithm"` | `encrypt` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"kerb:encryption_algorithms"` | `encryptn` | `repeat` | N/A | `"extract"` |
| `"kerb:name"` | `kerbname` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"kerb:key_from"` | `keyfrom` | `string` | N/A | `"extract"` |
| `"kerb:key_version"` | `keyvers` | `string` | N/A | `"extract"` |
| `"kerb:max_ticket_life"` | `maxtktlf` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `language`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"language:primary"` | `primary` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"language:secondary"` | `second` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `lnotes`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"lnotes:zos_short_name"` | `sname` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `mfa`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"mfa:factor"` | `factor` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"mfa:active"` | `facactv` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"mfa:tags"` | `factags` | `string` | `"set"`<br>`"remove"`<br>`"delete"` | `"alter"` |
| `"mfa:password_fallback"` | `mfaflbk` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"mfa:mfa_policy"` | `mfapolnm` | `string` | `"add"`<br>`"remove"` | `"alter"`<br>`"extract"` |

## `nds`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"nds:username"` | `uname` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `netview`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"netview:default_mcs_console_name"` | `consname` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"netview:security_control_check"` | `ctl` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"netview:domain"` | `domains` | `string` | `"set"`<br>`"add"`<br>`"remove"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"netview:domains"` | `domainsn` | `repeat` | N/A | `"extract"` |
| `"netview:logon_commands"` | `ic` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"netview:receive_unsolicited_messages"` | `msgrecvr` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"netview:operator_graphic_monitor_facility_administration_allowed"` | `ngmfadmn` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"netview:operator_graphic_monitor_facility_display_authority"` | `ngmfvspn` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"netview:operator_scope_classes"` | `opclass` | `string` | `"set"`<br>`"add"`<br>`"remove"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `omvs`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"omvs:max_address_space_size"` | `assize` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"omvs:auto_uid"` | `autouid` | `boolean` | `"set"` | `"add"`<br>`"alter"` |
| `"omvs:max_cpu_time"` | `cputime` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"omvs:max_files_per_process"` | `fileproc` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"omvs:home_directory"` | `home` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"omvs:max_non_shared_memory"` | `memlimit` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"omvs:max_file_mapping_pages"` | `mmaparea` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"omvs:max_processes"` | `procuser` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"omvs:default_shell"` | `program` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"omvs:shared"` | `shared` | `boolean` | `"set"` | `"add"`<br>`"alter"` |
| `"omvs:max_shared_memory"` | `shmemmax` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"omvs:max_threads"` | `threads` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"omvs:uid"` | `uid` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `operparm`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"operparm:alternate_console_group"` | `altgrp` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:receive_automated_messages"` | `auto` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:command_target_system"` | `cmdsys` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:receive_delete_operator_messages"` | `dom` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:receive_hardcopy_messages"` | `hc` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:receive_internal_console_messages"` | `intids` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:console_searching_key"` | `key` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:message_level"` | `level` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:message_levels"` | `leveln` | `repeat` | N/A | `"extract"` |
| `"operparm:log_command_responses"` | `logcmd` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:message_format"` | `mform` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:migration_id"` | `migid` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:monitor_event"` | `monitor` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:monitor_events"` | `monitorn` | `repeat` | N/A | `"extract"` |
| `"operparm:message_scope"` | `mscope` | `string` | `"set"`<br>`"add"`<br>`"remove"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:message_scopes"` | `mscopen` | `repeat` | N/A | `"extract"` |
| `"operparm:console_authority"` | `operauth` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:console_authorities"` | `operautn` | `repeat` | N/A | `"extract"` |
| `"operparm:receive_routing_code"` | `routcode` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:receive_routing_codes"` | `routcodn` | `repeat` | N/A | `"extract"` |
| `"operparm:message_queue_storage"` | `storage` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:receive_undelivered_messages"` | `ud` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"operparm:receive_unknown_console_id_messages"` | `unknids` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `ovm`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"ovm:file_system_root"` | `fsroot` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"ovm:home_directory"` | `vhome` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"ovm:default_shell"` | `vprogram` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"ovm:uid"` | `vuid` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `proxy`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"proxy:bind_distinguished_name"` | `binddn` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"proxy:bind_password"` | `bindpw` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"proxy:ldap_host"` | `ldaphost` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `tso`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"tso:account_number"` | `acctnum` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tso:logon_command"` | `command` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tso:sysout_destination_id"` | `dest` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tso:hold_class"` | `hldclass` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tso:job_class"` | `jobclass` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tso:max_region_size"` | `maxsize` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tso:message_class"` | `msgclass` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tso:logon_procedure"` | `proc` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tso:security_label"` | `seclabel` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tso:default_region_size"` | `size` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tso:sysout_class"` | `sysoutcl` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tso:data_set_allocation_unit"` | `unit` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tso:user_data"` | `userdata` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `workattr`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"workattr:account_number"` | `waaccnt` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"workattr:sysout_building"` | `wabldg` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"workattr:sysout_department"` | `wadept` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"workattr:sysout_user"` | `waname` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"workattr:sysout_room"` | `waroom` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"workattr:sysout_email"` | `waemail` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
