---
layout: default
parent: Traits
nav_order: 4
---

# Resource Traits

The following tables describes the resource segments and traits that are supported for add and alter operations, and returned by extract operations.
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
| `"base:access_list"` | `aclcnt` | `repeat` | N/A | `"extract"` |
| `"base:access_count"` | `aclacnt` | `uint` | N/A | `"extract"` |
| `"base:access_type"` | `aclacs` | `string` | N/A | `"extract"` |
| `"base:access_id"` | `aclid` | `string` | N/A | `"extract"` |
| `"base:alter_access_count"` | `acsaltr` | `uint` | N/A | `"extract"` |
| `"base:control_access_count"` | `acscntl` | `uint` | N/A | `"extract"` |
| `"base:read_access_count"` | `acsread` | `uint` | N/A | `"extract"` |
| `"base:update_access_count"` | `acsupdt` | `uint` | N/A | `"extract"` |
| `"base:application_data"` | `appldata` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:audit_alter"` | `audaltr` | `string` | `"set"` | `"add"`<br>`"alter"` |
| `"base:audit_control"` | `audcntl` | `string` | `"set"` | `"add"`<br>`"alter"` |
| `"base:audit_none"` | `audnone` | `string` | `"set"` | `"add"`<br>`"alter"` |
| `"base:audit_read"` | `audread` | `string` | `"set"` | `"add"`<br>`"alter"` |
| `"base:audit_update"` | `audupdt` | `string` | `"set"` | `"add"`<br>`"alter"` |
| `"base:security_category"` | `category` | `string` | `"set"`<br>`"add"`<br>`"remove"` | `"add"`<br>`"alter"` |
| `"base:security_categories"` | `numctgy` | `repeat` | N/A | `"extract"` |
| `"base:create_date"` | `creatdat` | `string` | N/A | `"extract"` |
| `"base:installation_data"` | `data` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:model_profile_class"` | `fclass` | `string` | `"set"` | `"add"` |
| `"base:model_profile_generic"` | `fgeneric` | `boolean` | `"set"` | `"add"` |
| `"base:model_profile"` | `fprofile` | `string` | `"set"` | `"add"` |
| `"base:model_profile_volume"` | `fvolume` | `string` | `"set"` | `"add"` |
| `"base:global_audit_alter"` | `gaudaltr` | `string` | `"set"` | `"alter"` |
| `"base:global_audit_control"` | `gaudcntl` | `string` | `"set"` | `"alter"` |
| `"base:global_audit_none"` | `gaudnone` | `string` | `"set"` | `"alter"` |
| `"base:global_audit_read"` | `gaudread` | `string` | `"set"` | `"alter"` |
| `"base:global_audit_update"` | `gaudupdt` | `string` | `"set"` | `"alter"` |
| `"base:is_generic"` | `generic` | `boolean` | N/A | `"extract"` |
| `"base:last_change_date"` | `lchgdat` | `string` | N/A | `"extract"` |
| `"base:level"` | `level` | `string` | `"set"` | `"add"`<br>`"alter"` |
| `"base:last_reference_date"` | `lrefdat` | `string` | N/A | `"extract"` |
| `"base:member_class_name"` | `member` | `string` | `"set"`<br>`"add"`<br>`"remove"` | `"add"`<br>`"alter"` |
| `"base:member_class_names"` | `member` | `repeat` | N/A | `"extract"` |
| `"base:notify_userid"` | `notify` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:owner"` | `owner` | `string` | `"set"` | `"add"`<br>`"alter"` |
| `"base:auditing"` | `raudit` | `repeat` | N/A | `"extract"` |
| `"base:global_auditing"` | `rgaudit` | `string` | N/A | `"extract"` |
| `"base:security_label"` | `seclabel` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:security_level"` | `seclevel` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:single_data_set_tape_volume"` | `singldsn` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:time_zone"` | `timezone` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:tape_vtoc"` | `tvtoc` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:universal_access"` | `uacc` | `string` | `"set"` | `"add"`<br>`"alter"` |
| `"base:volume"` | `volume` | `string` | `"add"`<br>`"remove"` | `"alter"` |
| `"base:volumes"` | `volcnt` | `repeat` | N/A | `"extract"` |
| `"base:warn_on_insufficient_access"` | `warning` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:terminal_access_allowed_day"` | `whendays` | `string` | `"set"` | `"add"`<br>`"alter"` |
| `"base:terminal_access_allowed_days"` | `whendyct` | `repeat` | N/A | `"extract"` |
| `"base:terminal_access_allowed_time"` | `whentime` | `string` | `"set"` | `"add"`<br>`"alter"` |

## `cdtinfo`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"cdtinfo:case_allowed"` | `cdtcase` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:default_racroute_return_code"` | `cdtdftrc` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:valid_first_character"` | `cdtfirst` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:valid_first_characters"` | `cdtfirn` | `repeat` | N/A | `"extract"` |
| `"cdtinfo:generic_profile_checking"` | `cdtgen` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:generic_profile_sharing"` | `cdtgenl` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:grouping_class_name"` | `cdtgroup` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:key_qualifiers"` | `cdtkeyql` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:manditory_access_control_processing"` | `cdtmac` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:max_length"` | `cdtmaxln` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:max_length_entityx"` | `cdtmaxlx` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:member_class_name"` | `cdtmembr` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:operations"` | `cdtoper` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:valid_other_character"` | `cdtother` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:valid_other_characters"` | `cdtothn` | `repeat` | N/A | `"extract"` |
| `"cdtinfo:posit_number"` | `cdtposit` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:profiles_allowed"` | `cdtprfal` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:raclist_allowed"` | `cdtracl` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:send_enf_signal_on_profile_creation"` | `cdtsigl` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:security_label_required"` | `cdtslreq` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cdtinfo:default_universal_access"` | `cdtuacc` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `cfdef`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"cfdef:custom_field_data_type"` | `cfdtype` | `string` | `"set"` | `"add"`<br>`"extract"` |
| `"cfdef:valid_first_characters"` | `cffirst` | `string` | `"set"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cfdef:help_text"` | `cfhelp` | `string` | `"set"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cfdef:list_heading_text"` | `cflist` | `string` | `"set"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cfdef:mixed_case_allowed"` | `cfmixed` | `string` | `"set"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cfdef:min_numeric_value"` | `cfmnval` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cfdef:max_field_length"` | `cfmxlen` | `uint` | `"set"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cfdef:max_numeric_value"` | `cfmxval` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cfdef:valid_other_characters"` | `cfother` | `string` | `"set"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"cfdef:validation_rexx_exec"` | `cfvalrx` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `dlfdata`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"dlfdata:job_name"` | `jobname` | `string` | `"set"`<br>`"add"`<br>`"remove"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"dlfdata:job_names"` | `jobnmcnt` | `repeat` | N/A | `"extract"` |
| `"dlfdata:retain_object_after_use"` | `retain` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `eim`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"eim:domain_distinguished_name"` | `domaindn` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"eim:kerberos_registry"` | `kerbreg` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"eim:local_registry"` | `localreg` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"eim:options"` | `options` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `kerb`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"kerb:validate_addresses"` | `chkaddrs` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"kerb:default_ticket_life"` | `deftktlf` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"kerb:encryption_algorithm"` | `encrypt` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"kerb:encryption_algorithms"` | `encryptn` | `repeat` | N/A | `"extract"` |
| `"kerb:realm_name"` | `kerbname` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"kerb:key_version"` | `keyvers` | `string` | N/A | `"extract"` |
| `"kerb:max_ticket_life"` | `maxtktlf` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"kerb:min_ticket_life"` | `mintktlf` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"kerb:password"` | `password` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |

## `icsf`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"icsf:certificate_label"` | `crtlbls` | `string` | `"set"`<br>`"add"`<br>`"remove"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"icsf:certificate_labels"` | `crtlblct` | `repeat` | N/A | `"extract"` |
| `"icsf:exportable_public_keys"` | `export` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"icsf:symmetric_export_public_key"` | `keylbls` | `string` | `"set"`<br>`"add"`<br>`"remove"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"icsf:symmetric_export_public_keys"` | `keylblct` | `repeat` | N/A | `"extract"` |
| `"icsf:symmetric_cpacf_rewrap"` | `scpwrap` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"icsf:symmetric_cpacf_rewrap_return"` | `scpret` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"icsf:asymetric_key_usage"` | `usage` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"icsf:key_usage_options"` | `usagect` | `repeat` | N/A | `"extract"` |

## `ictx`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"ictx:use_identity_map"` | `domap` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"ictx:require_identity_mapping"` | `mapreq` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"ictx:identity_map_timeout"` | `maptimeo` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"ictx:cache_application_provided_identity_map"` | `usemap` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `idtparms`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"idtparms:signature_algorithm"` | `sigalg` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"idtparms:identity_token_timeout"` | `idttimeo` | `uint` | `"set"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"idtparms:use_for_any_application"` | `anyappl` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `jes`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"jes:icsf_key_label"` | `keylabel` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `mfpolicy`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"mfpolicy:factor"` | `factors` | `string` | `"set"`<br>`"add"`<br>`"remove"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"mfpolicy:factors"` | `factorsn` | `repeat` | N/A | `"extract"` |
| `"mfpolicy:token_timeout"` | `timeout` | `uint` | N/A | `"extract"` |
| `"mfpolicy:reuse_token"` | `reuse` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `proxy`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"proxy:bind_distinguished_name"` | `binddn` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"proxy:bind_password"` | `bindpw` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"proxy:ldap_host"` | `ldaphost` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `session`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"session:security_checking_level"` | `convsec` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"session:session_key_interval"` | `interval` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"session:locked"` | `lock` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"session:session_key"` | `sesskey` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `sigver`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"sigver:fail_program_load_condition"` | `failload` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"sigver:log_signature_verification_events"` | `sigaudit` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"sigver:signature_required"` | `sigreqd` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `ssignon`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"ssignon:encrypt_legacy_pass_ticket_key"` | `keycrypt` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"ssignon:enhanced_pass_ticket_label"` | `ptkeylab` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"ssignon:enhanced_pass_ticket_type"` | `pttype` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"ssignon:enhanced_pass_ticket_timeout"` | `pttimeo` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"ssignon:enhanced_pass_ticket_replay"` | `ptreplay` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"ssignon:legacy_pass_ticket_label"` | `keylabel` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"ssignon:mask_legacy_pass_ticket_key"` | `keymask` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |

## `stdata`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"stdata:group"` | `group` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"stdata:privileged"` | `privlege` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"stdata:trace"` | `trace` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"stdata:trusted"` | `trusted` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"stdata:userid"` | `user` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `svfmr`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"svfmr:parameter_list_name"` | `parmname` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"svfmr:script_name"` | `script` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |

## `tme`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"tme:child"` | `children` | `string` | `"set"`<br>`"add"`<br>`"remove"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tme:children"` | `childn` | `repeat` | N/A | `"extract"` |
| `"tme:group"` | `groups` | `string` | `"set"`<br>`"add"`<br>`"remove"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tme:groups"` | `groupn` | `repeat` | N/A | `"extract"` |
| `"tme:parent"` | `parent` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tme:resource"` | `resource` | `string` | `"set"`<br>`"add"`<br>`"remove"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tme:resources"` | `resn` | `repeat` | N/A | `"extract"` |
| `"tme:role"` | `roles` | `string` | `"set"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"tme:roles"` | `rolen` | `repeat` | N/A | `"extract"` |
