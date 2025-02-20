---
layout: default
parent: Traits
nav_order: 6
---

# Permission Traits

The following tables describes the permission segments and traits that are supported for alter operations and returned by extract operations.
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
| `"base:access"` | `access` | `string` | `"set"` | `"alter"` |
| `"base:model_profile_class"` | `fclass` | `string` | `"set"` | `"alter"` |
| `"base:model_profile"` | `fprofile` | `string` | `"set"` | `"alter"` |
| `"base:model_profile_generic"` | `fgeneric` | `boolean` | `"set"` | `"alter"` |
| `"base:model_profile_volume"` | `fvolume` | `string` | `"set"` | `"alter"` |
| `"base:reset"` | `reset` | `string` | `"set"` | `"alter"` |
| `"base:when_partner_lu_name"` | `whenappc` | `string` | `"set"` | `"alter"` |
| `"base:when_console"` | `whencons` | `string` | `"set"` | `"alter"` |
| `"base:when_jes"` | `whenjes` | `string` | `"set"` | `"alter"` |
| `"base:when_program"` | `whenprog` | `string` | `"set"` | `"alter"` |
| `"base:when_servauth"` | `whenserv` | `string` | `"set"` | `"alter"` |
| `"base:when_sms"` | `whensms` | `string` | `"set"` | `"alter"` |
| `"base:when_service"` | `whensrv` | `string` | `"set"` | `"alter"` |
| `"base:when_system"` | `whensys` | `string` | `"set"` | `"alter"` |
| `"base:when_terminal"` | `whenterm` | `string` | `"set"` | `"alter"` |
