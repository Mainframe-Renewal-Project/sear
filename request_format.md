---
layout: default
---

# Request Format

RACFu provides the following standardized JSON schema for issuing security requests to RACF.
{: .fs-6 .fw-300 }

## 📥 Parameters *(JSON Keys)*

&nbsp;

* `"operation"`<br>
  A `string` value describing the **Security Management Function** to perform. The following table describes all of the valid values for `"operation"`.

  &nbsp;

  {: .note }
  > _Only the `"alter"` and `"extract"` **Operations** are allowed for the `"racf-options"` **Admin Type**._

  &nbsp;

  {: .note }
  > _Only the `"alter"`, `"extract"`, and `"delete"` **Operations** are allowed for the `"permission"` **Admin Type**._

  &nbsp;

  | **Operation** | **Description** |
  | `"add"` | **Add/Create** a new security profile. |
  | `"alter"` | **Alter** an existing security profile. |
  | `"extract"` | **Extract** a security profile's data. |
  | `"delete"` | **Delete** a security profile. |

* `"admin_type"`<br>
  A `string` value describing the type of **Security Administration Request** to issue. The following table describes all of the valid values for `"admin_type"`.

  &nbsp;

  {: .note }
  > _The `"permission"` **Admin Type** is **NOT** allowed for `"extract"` **Operations**._

  &nbsp;

  | **Admin Type** | **Description** |
  | `"user"` | Used for **User** administration. |
  | `"group"` | Used for **Group** administration. |
  | `"group-connection"` | Used for **Group Connection** administration. |
  | `"resource"` | Used for **General Resource Profile** administration. |
  | `"data-set"` | Used for **Data Set** administration. |
  | `"racf-options"` | Used for **RACF Options** administration. |
  | `"permission"` | Used for **Permission** administration. |

* `"profile_name"`<br>
  A `string` value identifying a **Security Profile** to **Add**, **Alter**, **Extract**, or **Delete**.

  &nbsp;

  {: .note }
  > _`"profile_name"` is **NOT** allowed to be used with the `"racf-options"` **Admin Type** due to **RACF Options** being a **Singleton** for which there is **NO** concept of multiple discrete "profiles" that can be created, deleted, and managed._

  &nbsp;

  {: .note }
  > _`"class_name"` **MUST** be used to indicate which **Class Name** the specified **Security Profile** is associated with for the `"resource"` and `"permission"` **Admin Types**._

  &nbsp;

* `"traits"`<br>
  An `object` describing the **Traits/Attributes** to **Add/Modify** in `"add"` and `"alter"` **Operations**. See [Traits](../traits/) for more detail about how to specify **Traits** for `"add"` and `"alter"` **Operations**, and what **Traits** are supported for each **Admin Type**.

  &nbsp;

  {: .note }
  > _`"traits"` is **NOT** allowed to be used with `"extract"` and `"delete"` **Operations**._

  &nbsp;

* `"class_name"`<br>
  A `string` value identifying a **Class Name** that the specified **Security Profile** is associated with.

  &nbsp;

  {: .note }
  > _`"class_name"` is **required** for and **only** allowed for the `"resource"` and `"permission"` **Admin Types**._

  &nbsp;

* `"volume"`<br>
  A `string` value identifying a **Volume**.

  &nbsp;

  {: .note }
  > _Only the `"data-set"` and `"permission"` **Admin Types** can be used with `"volume"`, and **only** for `"add"`, `"alter"`, and `"delete"` **Operations**._

  &nbsp;

  {: .note }
  > _Note that for the `"permission"` **Admin Type**, this parameter will only take effect if the `"class_name"` parameter is set to `"DATASET"`._

  &nbsp;

* `"generic"`<br>
  A `string` value identifying a **Security Profile** as **Generic** or **Not Generic**.

  &nbsp;

  {: .note }
  > _Only the `"data-set"` and `"permission"` **Admin Types** can be used with `"generic"`, and **only** for `"add"`, `"alter"`, and `"delete"` **Operations**._

  &nbsp;

  {: .note }
  > _Note that for the `"permission"` **Admin Type**, this parameter will only take effect if the `"class_name"` parameter is set to `"DATASET"`._

  &nbsp;

  {: .note }
  > _`"generic"` may **only** be set to `"yes"` or `"no"`._

  &nbsp;

* `"run_as_userid"`<br>
  A `string` value identifying a **z/OS Userid** to perform the **Security Operation** as.

  &nbsp;

  {: .note }
  > _In order to use `"run_as_userid"`, the caller must have at least `UPDATE` access to the `<userid>.IRRSMO00` **General Resource Profile** in the `SURROGAT` **Class**, where `<userid>` represents the **z/OS Userid** to perform **Security Operations** as. More information about **IRRSMO00 Authorizations** can be found [here](https://www.ibm.com/docs/en/zos/latest?topic=operations-racf-authorization)._

  &nbsp;

  {: .note }
  > _`"run_as_userid"` is **NOT** allowed for `"extract"` **Operations**._

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
  "profile_name": "SQUIDWRD",
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
  "profile_name": "SQUIDWRD",
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
  "profile_name": "SQUIDWRD"
}
```

The following **RACFu Request JSON** extracts the **Profile Data** for a **z/OS Userid** called `SQUIDWRD`. 

###### JSON
```json
{
  "operation": "extract",
  "admin_type": "user",
  "profile_name": "SQUIDWRD"
}
```
