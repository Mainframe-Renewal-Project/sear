---
layout: default
parent: Traits
nav_order: 7
---

# RACF Options Traits

The following tables describes the racf options segments and traits that are supported for alter operations and returned by extract operations.
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
| `"base:add_creator_to_access_list"` | `addcreat` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:automatic_data_set_protection"` | `adsp` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:application_logon_auditing"` | `applaudt` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:audit_classes"` | `audit` | `string` | `"add"`<br>`"remove"` | `"alter"`<br>`"extract"` |
| `"base:uncataloged_data_set_access"` | `catdsns` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:active_classes"` | `classact` | `string` | `"add"`<br>`"remove"` | `"alter"`<br>`"extract"` |
| `"base:statistics_classes"` | `classtat` | `string` | `"add"`<br>`"remove"` | `"alter"`<br>`"extract"` |
| `"base:log_racf_command_violations"` | `cmdviol` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:security_label_compatibility_mode"` | `compmode` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:enhanced_generic_naming"` | `egn` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:erase_data_sets_on_delete"` | `erase` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:erase_data_sets_on_delete_all"` | `eraseall` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:erase_data_sets_on_delete_security_level"` | `erasesec` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:generic_command_classes"` | `gencmd` | `string` | `"add"`<br>`"remove"` | `"alter"`<br>`"extract"` |
| `"base:generic_profile_checking_classes"` | `generic` | `string` | `"add"`<br>`"remove"` | `"alter"`<br>`"extract"` |
| `"base:generic_profile_sharing_classes"` | `genlist` | `string` | `"add"`<br>`"remove"` | `"alter"`<br>`"extract"` |
| `"base:generic_owner"` | `genowner` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:global_access_classes"` | `global` | `string` | `"add"`<br>`"remove"` | `"alter"`<br>`"extract"` |
| `"base:list_of_groups_access_checking"` | `grplist` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:password_history"` | `history` | `uint` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:revoke_inactive_userids_interval"` | `inactive` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:record_user_verification_statistics"` | `initstat` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:max_password_change_interval"` | `interval` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:jes_batch"` | `jesbatch` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:jes_early_verification"` | `jesearly` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:jes_network_user"` | `jesnje` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:jes_undefined_user"` | `jesundef` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:jes_execution_batch_monitoring"` | `jesxbm` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:kerberos_encryption_level"` | `kerblvl` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:audit_log_always_classes"` | `logalwys` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:audit_log_default_classes"` | `logdeflt` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:audit_log_failure_classes"` | `logfail` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:audit_log_never_classes"` | `lognever` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:audit_log_success_classes"` | `logsucc` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:min_password_change_interval"` | `minchang` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:mixed_case_password_support"` | `mixdcase` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:multi_level_security_address_space"` | `mlactive` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:multi_level_security_file_system"` | `mlfs` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:multi_level_security_interprocess"` | `mlipc` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:multi_level_security_file_names"` | `mlnames` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:multi_level_security_logon"` | `mlquiet` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:multi_level_security_declassification"` | `mls` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:multi_level_security_label_alteration"` | `mlstable` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:profile_modelling"` | `model` | `boolean` | `"delete"` | `"alter"`<br>`"extract"` |
| `"base:profile_modelling_generation_data_group"` | `modgdg` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:profile_modelling_group"` | `modgroup` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:profile_modelling_user"` | `moduser` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:log_operator_actions"` | `operaudt` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:passphrase_change_interval"` | `phrint` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:data_set_single_level_name_prefix_protection"` | `prefix` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:primary_language"` | `primlang` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:protect_all_data_sets"` | `protall` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:password_encryption_algorithm"` | `pwdalg` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:special_character_password_support"` | `pwdspec` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:raclist"` | `raclist` | `string` | `"add"`<br>`"remove"` | `"alter"`<br>`"extract"` |
| `"base:log_real_data_set_name"` | `realdsn` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:refresh"` | `refresh` | `boolean` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:tape_data_set_security_retention_period"` | `retpd` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:max_incorrect_password_attempts"` | `revoke` | `uint` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:password_rules"` | `rules` | `boolean` | `"delete"` | `"alter"`<br>`"extract"` |
| `"base:rvary_status_password_format"` | `rvarstfm` | `string` | N/A | `"extract"` |
| `"base:rvary_status_password"` | `rvarstpw` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:rvary_status_password_format"` | `rvarswfn` | `string` | N/A | `"extract"` |
| `"base:rvary_status_password"` | `rvarswpw` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:log_commands_issuesd_by_special_users"` | `saudit` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:security_label_control"` | `seclabct` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:secondary_language"` | `seclang` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:max_session_key_interval"` | `sessint` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:security_label_auditing"` | `slabaudt` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:security_label_system"` | `slbysys` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:security_level_auditing"` | `slevaudt` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:tape_data_set_protection"` | `tapedsn` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:terminal_universal_access"` | `terminal` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:password_expiration_warning"` | `warning` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:program_control"` | `whenprog` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
