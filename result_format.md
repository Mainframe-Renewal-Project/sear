---
layout: default
---

# Result Format

RACFu provides the following standardized JSON schema for security results returned by RACF.
{: .fs-6 .fw-300 }

## 📤 Result Fields *(JSON Keys)*

&nbsp;

* `"commands"`<br>
  An `object` `array` describing one or more **RACF Commands** that were executed and the corresponding **Messages** produced after processing **Add**, **Alter**, and **Delete** requests if there were any.

  * `"command"`<br>
    A **String** value containing a **RACF Command** that was executed.

  * `"messages"`<br>
    A `string` `array` containing the **Messages** produced during the processing of a **RACF Command** for which there may be **Zero**, **One**, or **Many**. These messages may be **Informational messages** or **Error messages**.

  ###### JSON
  ```json
  [
    {
      "command": "RACF COMMAND 1",
      "messages": [
        "RACF MESSAGE 1",
        "RACF MESSAGE 2"
      ]
    },
    {
      "command": "RACF COMMAND 2",
      "messages": []
    }
  ]
  ```

&nbsp;

* `"profile"`<br>
  An `object` describing **Profile Data** extracted as a result of an `"extract"` **Operation**. This structure contains all of the **Profile Data** that corresponds to the profile specified using the `"profile_name"` **Parameter** *(and the `"class_name"` **Parameter** for **Admin Types** that require it)* of the corresponding request. The only exception is the `"racf-options"` **Admin Type**, where `"profile_name"` is **NOT** allowed in **RACF Options Administration** requests due to **RACF Options** being a **Singleton** for which there is **NO** concept of multiple discrete *"profiles"* that can be created, deleted, and managed.

  * `"<segment>"`<br>
    An `object` describing a **RACF Segment**. At least one **Segment** will be returned, and each **Segment** returned will contain one or more **Traits**.

  * `"<segment>:<trait>"`<br>
    A **Key-Value Pair** that describes a **Trait**/**Attribute** within a **Segment**. The `<segment>` token describes the **Segment** that the **Trait** belongs to, and the `<trait>` token is the name of the **Trait**. See [Traits](../traits/) for more details about what **Traits** can be returned for each **Admin Type** and what **Data Types** are used for each one.

  ###### JSON
  ```json
  {
    "<segment>": {
      "<segment>:<trait>": "VALUE",
      "<segment>:<trait>": 24
    },
    "<segment>": {
      "<segment>:<trait>": true,
      "<segment>:<trait>": [
        {
          "<segment>:<trait>": null,
          "<segment>:<trait>": false
        },
        {
          "<segment>:<trait>": "VALUE",
          "<segment>:<trait>": true
        }
      ]
    }
  }
  ```

&nbsp;
  
* `"errors"`<br>
  A `string` `array` containing the **Error Messages** produced when processing a **Security Request** if there were any.

  &nbsp;

  {: .note }
  > * _**Error Messages** produced during the processing of **Add**, **Alter**, and **Delete** requests may also manifest within the `"commands"` field. These **Error Messages** will describe problems encountered by **RACF** while processing the corresponding **RACF Commands**._

  &nbsp;

* `"return_codes"`<br>
  An `object` describing all of the **Return Codes** and **Reason Codes** for the **Security Administration Request** that was **Attempted**/**Performed**. The following table describes the **Subfields** that can be found in `"return_codes"`.

  &nbsp;

  {: .note }
  > _Detailed explanations for the **SAF Return Codes**, **RACF Return Codes**, and **RACF Reason Codes** returned by **Add**, **Alter**, and **Delete** **Operations** can be found [here](https://www.ibm.com/docs/en/zos/latest?topic=operations-return-reason-codes)._

  &nbsp;

  {: .note }
  > _Detailed explanations for the **SAF Return Codes**, **RACF Return Codes**, and **RACF Reason Codes** returned by **Extract** **Operations** can be found [here](https://www.ibm.com/docs/en/zos/latest?topic=rairaa-return-reason-codes)._

  &nbsp;

  | **Subfield** | **Description** |
  | `"saf_return_code"` | A `number` describing the **SAF Return Code**. `"saf_return_code"` will be set to `null` when `"racfu_return_code"` is `8`. |
  | `"racf_return_code"` | A `number` describing the **RACF Return Code**. `"racf_return_code"` will be set to `null` when `"racfu_return_code"` is `8`. |
  | `"racf_reason_code"` | A `number` describing the **RACF Reason Code**. `"racf_reason_code"` will be set to `null` when `"racfu_return_code"` is `8`. |
  | `"racfu_return_code"` | A `number` describing the **RACFu Return Code**. `"racfu_return_code"` will be set to `0` when there are no errors, `4` when an error occured within the call to the corresponding **RACF Callable Service**, and `8` when **RACFu** encounters an error that prevented the request from being **Proccessed** by the corresponding **RACF Callable Service** or prevented the result from the corresponding **RACF Callable Service** from being **Post-Processed**. |

## 💻 Result Examples

&nbsp;

{: .note }
> _These examples are **NOT** comprehensive and are primarily meant to show users the general structure of the **RACFu Result JSON** in a handful of common scenarios._

&nbsp;

The following **RACFu Result JSON** contains the result of an `"add"` **Operation** that created a new **z/OS Userid** called `SQUIDWRD` with the following **Traits**:
* A **Name** of `"Squidward"`.
* An **OMVS UID** of `24`.
* An **OMVS Home Directory** of `"/u/squidwrd"`.

###### JSON
```json
{
  "commands": [
    {
      "command": "ADDUSER SQUIDWRD ",
      "messages": [
        "ICH01024I User SQUIDWRD is defined as PROTECTED."
      ]
    },
    {
      "command": "ALTUSER SQUIDWRD     NAME        ('Squidward') OMVS     (HOME        ('/u/squidwrd') UID         (24))",
      "messages": []
    }
  ],
  "return_codes": {
    "racf_reason_code": 0,
    "racf_return_code": 0,
    "racfu_return_code": 0,
    "saf_return_code": 0
  }
}
```

The following **RACFu Result JSON** contains the result of an `"add"` **Operation** that was unable to create a new **z/OS Userid** called `SQUIDWRD` since a **z/OS Userid** already exists on the system with that name.

###### JSON
```json
{
  "errors": [
    "racfu: unable to add 'SQUIDWRD' because a 'user' profile already exists with that name"
   ],
  "return_codes": {
    "racf_reason_code": 0,
    "racf_return_code": 0,
    "racfu_return_code": 4,
    "saf_return_code": 0
  }
}
```

The following **RACFu Result JSON** contains the result of a request that was never processed by RACF due to **Errors** in the corresponding **RACFu Request JSON**.

###### JSON
```json
{
  "errors": [
    "racfu: 'junk_operation' is not a valid value for 'operation'",
    "racfu: 'junk_admin' is not a valid value for 'admin_type'"
  ],
  "return_codes": {
    "racf_reason_code": null,
    "racf_return_code": null,
    "racfu_return_code": 8,
    "saf_return_code": null
  }
}
```

The following **RACFu Result JSON** contains the result of an `"extract"` **Operation** that contains the **Profile Data** for a **z/OS Userid** called `SQUIDWRD`. 

###### JSON
```json
{
  "profile": {
    "base": {
      "base:audit_logging": false,
      "base:audit_responsibility": false,
      "base:auditor": false,
      "base:automatic_data_set_protection": false,
      "base:create_date": "09/13/24",
      "base:default_group": "SYS1",
      "base:group_connections": [
        {
          "base:group_connection_auditor": false,
          "base:group_connection_automatic_data_set_protection": false,
          "base:group_connection_create_date": "09/13/24",
          "base:group_connection_data_set_access": false,
          "base:group_connection_group": "SYS1",
          "base:group_connection_last_connect_date": null,
          "base:group_connection_last_connect_time": null,
          "base:group_connection_operations": false,
          "base:group_connection_owner": "LEONARD",
          "base:group_connection_resume_date": null,
          "base:group_connection_revoke_date": null,
          "base:group_connection_revoked": false,
          "base:group_connection_special": false,
          "base:group_connection_universal_access": "NONE",
          "base:group_connection_used_count": 0
        }
      ],
      "base:group_data_set_access": false,
      "base:has_passphrase": false,
      "base:has_password": false,
      "base:logon_allowed_days": [
        {
          "base:logon_allowed_day": "SUNDAY"
        },
        {
          "base:logon_allowed_day": "MONDAY"
        },
        {
          "base:logon_allowed_day": "TUESDAY"
        },
        {
          "base:logon_allowed_day": "WEDNESDAY"
        },
        {
          "base:logon_allowed_day": "THURSDAY"
        },
        {
          "base:logon_allowed_day": "FRIDAY"
        },
        {
          "base:logon_allowed_day": "SATURDAY"
        }
      ],
      "base:logon_allowed_time": "ANYTIME",
      "base:mfa_password_fallback": false,
      "base:name": "SQUIDWARD",
      "base:operations": false,
      "base:owner": "LEONARD",
      "base:passphrase_change_interval": 0,
      "base:passphrase_enveloped": false,
      "base:password_change_interval": 186,
      "base:password_enveloped": false,
      "base:protected": true,
      "base:restrict_global_access_checking": false,
      "base:revoked": false,
      "base:special": false
    },
    "omvs": {
      "omvs:home_directory": "/u/squidwrd",
      "omvs:uid": 24
    }
  },
  "return_codes": {
    "racf_reason_code": 0,
    "racf_return_code": 0,
    "racfu_return_code": 0,
    "saf_return_code": 0
  }
}
```

The following **RACFu Result JSON** contains the result of an `"extract"` **Operation** that failed because the **z/OS Userid** `SQUIDWRD` does **NOT** exist. 

###### JSON
```json
{
  "errors": [
    "racfu: unable to extract 'user' profile 'SQUIDWRD'"
  ],
  "return_codes": {
    "racf_reason_code": 4,
    "racf_return_code": 4,
    "racfu_return_code": 4,
    "saf_return_code": 4
  }
}
```
