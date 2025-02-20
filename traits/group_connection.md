---
layout: default
parent: Traits
nav_order: 3
---

# Group Connection Traits

The following tables describes the group connection segments and traits that are supported for alter operations and returned by extract operations.
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
| `"base:automatic_data_set_protection"` | `adsp` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:auditor"` | `auditor` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:authority"` | `auth` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:connection_create_date"` | `cgauthda` | `string` | N/A | `"extract"` |
| `"base:connection_used_count"` | `cginitct` | `uint` | N/A | `"extract"` |
| `"base:connecion_last_used_date"` | `cgljdate` | `string` | N/A | `"extract"` |
| `"base:connecion_last_used_time"` | `cgljtime` | `string` | N/A | `"extract"` |
| `"base:group_access"` | `grpacc` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:operations"` | `oper` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:owner"` | `owner` | `string` | `"set"` | `"alter"`<br>`"extract"` |
| `"base:resume_date"` | `resume` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:revoke_date"` | `revoke` | `string` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:revoked"` | `revokefl` | `boolean` | N/A | `"extract"` |
| `"base:special"` | `special` | `boolean` | `"set"`<br>`"delete"` | `"alter"`<br>`"extract"` |
| `"base:universal_access"` | `uacc` | `string` | `"set"` | `"alter"`<br>`"extract"` |
