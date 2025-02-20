---
layout: default
parent: Traits
nav_order: 5
---

# Data Set Traits

The following tables describes the data set segments and traits that are supported for add and alter operations, and returned by extract operations.
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
| `"base:alter_volume"` | `altvol` | `string` | N/A | `"extract"` |
| `"base:audit_alter"` | `audaltr` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:audit_control"` | `audcntl` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:audit_none"` | `audnone` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:audit_read"` | `audread` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:audit_update"` | `audupdt` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:security_category"` | `category` | `string` | `"set"`<br>`"add"`<br>`"remove"` | `"alter"` |
| `"base:security_categories"` | `numctgy` | `repeat` | N/A | `"extract"` |
| `"base:create_date"` | `creatdat` | `string` | N/A | `"extract"` |
| `"base:installation_data"` | `data` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:data_set_type"` | `dstype` | `string` | N/A | `"extract"` |
| `"base:erase_data_sets_on_delete"` | `erase` | `boolean` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:model_profile_class"` | `fclass` | `string` | `"set"` | `"add"` |
| `"base:model_profile_generic"` | `fgeneric` | `string` | `"set"` | `"add"` |
| `"base:tape_data_set_file_sequence_number"` | `fileseq` | `uint` | `"set"` | `"add"` |
| `"base:model_profile"` | `from` | `string` | `"set"` | `"add"` |
| `"base:model_profile_volume"` | `fvolume` | `string` | `"set"` | `"add"` |
| `"base:global_audit_alter"` | `gaudaltr` | `string` | `"set"`<br>`"delete"` | `"alter"` |
| `"base:global_audit_control"` | `gaudcntl` | `string` | `"set"`<br>`"delete"` | `"alter"` |
| `"base:global_audit_none"` | `gaudnone` | `boolean` | `"set"`<br>`"delete"` | `"alter"` |
| `"base:global_audit_read"` | `gaudread` | `string` | `"set"`<br>`"delete"` | `"alter"` |
| `"base:global_audit_update"` | `gaudupdt` | `string` | `"set"`<br>`"delete"` | `"alter"` |
| `"base:high_level_qualifier_is_group"` | `groupds` | `boolean` | N/A | `"extract"` |
| `"base:creation_group_name"` | `groupnm` | `string` | N/A | `"extract"` |
| `"base:last_change_date"` | `lchgdat` | `string` | N/A | `"extract"` |
| `"base:level"` | `level` | `uint` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:last_reference_date"` | `lrefdat` | `string` | N/A | `"extract"` |
| `"base:data_set_model_profile"` | `model` | `string` | `"set"` | `"add"` |
| `"base:notify_userid"` | `notify` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:owner"` | `owner` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:auditing"` | `raudit` | `repeat` | N/A | `"extract"` |
| `"base:tape_data_set_security_retention_period"` | `retpd` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:global_auditing"` | `rgaudit` | `string` | N/A | `"extract"` |
| `"base:security_label"` | `seclabel` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:security_level"` | `seclevel` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:racf_indicated_dataset"` | `set` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:create_only_tape_vtoc_entry"` | `setonly` | `string` | `"set"` | `"add"` |
| `"base:use_tape_data_set_profile"` | `tape` | `boolean` | N/A | `"extract"` |
| `"base:universal_access"` | `uacc` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:data_set_allocation_unit"` | `unit` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |
| `"base:volume"` | `volume` | `string` | `"set"`<br>`"add"`<br>`"delete"` | `"add"`<br>`"alter"`<br>`"extract"` |
| `"base:resident_volume"` | `volser` | `string` | N/A | `"extract"` |
| `"base:resident_volumes"` | `volcnt` | `repeat` | N/A | `"extract"` |
| `"base:warn_on_insufficient_access"` | `warning` | `string` | `"set"`<br>`"delete"` | `"add"`<br>`"alter"` |

## `dfp`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"dfp:owner"` | `resowner` | `string` | N/A | `"extract"` |
| `"dfp:ckds_data_key"` | `datakey` | `string` | N/A | `"extract"` |

## `tme`

| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |
| `"tme:roles"` | `roles` | `string` | N/A | `"extract"` |
