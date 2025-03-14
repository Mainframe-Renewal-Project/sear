---
layout: default
---

# Request Format

RACFu provides the following standardized JSON Schema for issuing security requests to RACF.
{: .fs-6 .fw-300 }

&nbsp;

{: .note }
> _RACFu validates requests using a **JSON Schema** that conforms to the [Draft-07](https://json-schema.org/draft-07) standard. The **JSON Schema** that RACFu uses to validate requests can be seen [here](https://github.com/ambitus/racfu/blob/main/schemas/parameters.json). Note that separate **JSON Schemas** are used to validate [Traits](../traits/)._

## Parameters

| **Parameter** | **Description** |
| `"operation"` | A `string` value describing the **Security Management Function** to perform. |
| `"admin_type"` | A `string` value describing the Type of **Security Administration Request** to issue. |
| `"traits"` | An `object` describing **Traits/Attributes** to **Add/Modify** in `"add"` and `"alter"` **Operations**. |
| `"userid"` | A `string` value that identifies a **z/OS Userid**. |
| `"group"` | A `string` value that identifies a **Group**. |
| `"resource"` | A `string` value that identifies a **General Resource Profile**. |
| `"class"` | A `string` value that identifies a **General Resource Class**. |
| `"volume"` | A `string` value that identifies a **DASD Volume Serial**. |
| `"generic"` | A `boolean` value that identifies a **Security Profile** as being **Generic** or not. |
| `"run_as_userid"` | A `string` value identifying a **z/OS Userid** to perform the **Security Operation** as. |

## User Administration Schemas

#### Extract User Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"extract"` | Required |
| `"admin_type"`| `string` | `"user"` | Required |
| `"userid"` | `string` | 1-8 character string | Required |

#### Add/Alter User Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"add"` or `"alter"` | Required |
| `"admin_type"`| `string` | `"user"` | Required |
| `"userid"` | `string` | 1-8 character string | Required |
| `"traits"` | `json` | [Traits JSON](../traits/) | Required |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

#### Delete User Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"delete"` | Required |
| `"admin_type"`| `string` | `"user"` | Required |
| `"userid"` | `string` | 1-8 character string | Required |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

## Group Administration Schemas

#### Extract Group Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"extract"` | Required |
| `"admin_type"`| `string` | `"group"` | Required |
| `"group"` | `string` | 1-8 character string | Required |

#### Add/Alter Group Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"add"` or `"alter"` | Required |
| `"admin_type"`| `string` | `"group"` | Required |
| `"group"` | `string` | 1-8 character string | Required |
| `"traits"` | `json` | [Traits JSON](../traits/) | Required |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

#### Delete Group Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"delete"` | Required |
| `"admin_type"`| `string` | `"group"` | Required |
| `"group"` | `string` | 1-8 character string | Required |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

## Group Connection Administration Schemas

#### Extract Group Connection Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"extract"` | Required |
| `"admin_type"`| `string` | `"group-connection"` | Required |
| `"userid"` | `string` | 1-8 character string | Required |
| `"group"` | `string` | 1-8 character string | Required |

#### Alter Group Connection Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"alter"` | Required |
| `"admin_type"`| `string` | `"group-connection"` | Required |
| `"userid"` | `string` | 1-8 character string | Required |
| `"group"` | `string` | 1-8 character string | Required |
| `"traits"` | `json` | [Traits JSON](../traits/) | Required |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

#### Delete Group Connection Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"delete"` | Required |
| `"admin_type"`| `string` | `"group-connection"` | Required |
| `"userid"` | `string` | 1-8 character string | Required |
| `"group"` | `string` | 1-8 character string | Required |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

## Resource Administration Schemas

#### Extract Resource Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"extract"` | Required |
| `"admin_type"`| `string` | `"resource"` | Required |
| `"resource"` | `string` | 1-246 character string | Required |
| `"class"` | `string` | 1-8 character string | Required |

#### Add/Alter Resource Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"add"` or `"alter"` | Required |
| `"admin_type"`| `string` | `"resource"` | Required |
| `"resource"` | `string` | 1-246 character string | Required |
| `"class"` | `string` | 1-8 character string | Required |
| `"traits"` | `json` | [Traits JSON](../traits/) | Required |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

#### Delete Resource Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"delete"` | Required |
| `"admin_type"`| `string` | `"resource"` | Required |
| `"resource"` | `string` | 1-246 character string | Required |
| `"class"` | `string` | 1-8 character string | Required |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

## Data Set Administration Schemas

#### Extract Data Set Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"extract"` | Required |
| `"admin_type"`| `string` | `"data-set"` | Required |
| `"data_set"` | `string` | 1-44 character string | Required |

#### Add/Alter Data Set Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"add"` or `"alter"` | Required |
| `"admin_type"`| `string` | `"data-set"` | Required |
| `"data_set"` | `string` | 1-44 character string | Required |
| `"volume"` | `string` | 1-6 character string | Optional |
| `"generic"` | `boolean` | `true` or `false`<br>*(`false` is the default)* | Optional |
| `"traits"` | `json` | [Traits JSON](../traits/) | Required |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

#### Delete Data Set Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"delete"` | Required |
| `"admin_type"`| `string` | `"data-set"` | Required |
| `"data_set"` | `string` | 1-44 character string | Required |
| `"volume"` | `string` | 1-6 character string | Optional |
| `"generic"` | `boolean` | `true` or `false`<br>*(`false` is the default)* | Optional |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

## RACF Options Administration Schemas

#### Extract RACF Options Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"extract"` | Required |
| `"admin_type"`| `string` | `"racf-options"` | Required |

#### Alter RACF Options Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"alter"` | Required |
| `"admin_type"`| `string` | `"racf-options"` | Required |
| `"traits"` | `json` | [Traits JSON](../traits/) | Required |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

## Permission Administration Schemas

#### Alter Permission Resource Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"alter"` | Required |
| `"admin_type"`| `string` | `"permission"` | Required |
| `"resource"` | `string` | 1-246 character string | Required |
| `"class"` | `string` | 1-8 character string | Required |
| `"userid"` | `string` | 1-8 character string | Required and only allowed if `"group"` is not specified |
| `"group"` | `string` | 1-8 character string | Required and only allowed if `"userid"` is not specified |
| `"traits"` | `json` | [Traits JSON](../traits/) | Required |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

#### Alter Permission Data Set Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"alter"` | Required |
| `"admin_type"`| `string` | `"permission"` | Required |
| `"data_set"` | `string` | 1-44 character string | Required |
| `"userid"` | `string` | 1-8 character string | Required and only allowed if `"group"` is not specified |
| `"group"` | `string` | 1-8 character string | Required and only allowed if `"userid"` is not specified |
| `"volume"` | `string` | 1-6 character string | Optional |
| `"generic"` | `boolean` | `true` or `false`<br>*(`false` is the default)* | Optional |
| `"traits"` | `json` | [Traits JSON](../traits/) | Required |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

#### Delete Permission Resource Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"delete"` | Required |
| `"admin_type"`| `string` | `"permission"` | Required |
| `"resource"` | `string` | 1-246 character string | Required |
| `"class"` | `string` | 1-8 character string | Required |
| `"userid"` | `string` | 1-8 character string | Required and only allowed if `"group"` is not specified |
| `"group"` | `string` | 1-8 character string | Required and only allowed if `"userid"` is not specified |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

#### Delete Permission Data Set Schema

| **Parameter** | **Data Type** | **Value** | **Required** |
| `"operation"` | `string` | `"delete"` | Required |
| `"admin_type"`| `string` | `"permission"` | Required |
| `"data_set"` | `string` | 1-44 character string | Required |
| `"userid"` | `string` | 1-8 character string | Required and only allowed if `"group"` is not specified |
| `"group"` | `string` | 1-8 character string | Required and only allowed if `"userid"` is not specified |
| `"volume"` | `string` | 1-6 character string | Optional |
| `"generic"` | `boolean` | `true` or `false`<br>*(`false` is the default)* | Optional |
| `"run_as_userid"` | `string` | 1-8 character string | Optional |

## 💻 Request Examples

&nbsp;

{: .note }
> _These examples are **NOT** comprehensive and are primarily meant to show users the general structure of `"add"`, `"alter"`, `"extract"` and `"delete"` requests._

&nbsp;

The following **RACFu Request JSON** creates new new **z/OS Userid** called `SQUIDWRD` with the following **Traits**:
* A **Name** of `"Squidward"`.
* An **OMVS UID** of `24`.
* An **OMVS Home Directory** of `"/u/squidwrd"`.

###### JSON
```json
{
  "operation": "add",
  "admin_type": "user",
  "userid": "SQUIDWRD",
  "traits": {
    "base:name": "Squidward",
    "omvs:uid": 24,
    "omvs:home_directory": "/u/squidwrd"
  }
}
```

The following **RACFu Request JSON** alters an exsting **z/OS Userid** called `SQUIDWRD` by **Changing/Setting** the **Name Trait** to `"Squilliam"`. 

###### JSON
```json
{
  "operation": "alter",
  "admin_type": "user",
  "userid": "SQUIDWRD",
  "traits": {
    "base:name": "Squilliam"
  }
}
```

The following **RACFu Request JSON** deletes an exsting **z/OS Userid** called `SQUIDWRD`. 

###### JSON
```json
{
  "operation": "delete",
  "admin_type": "user",
  "userid": "SQUIDWRD"
}
```

The following **RACFu Request JSON** extracts the **Profile Data** for a **z/OS Userid** called `SQUIDWRD`. 

###### JSON
```json
{
  "operation": "extract",
  "admin_type": "user",
  "userid": "SQUIDWRD"
}
```
