---
layout: default
parent: Traits
nav_order: y
---

# Data Types

The following table provides some notes about how the standard JSON data types are used with traits.
{: .fs-6 .fw-300 }

&nbsp;

| **Data Type** | **Notes** |
| `string` |  |
| `number` | This can only ever be a **Positive Unsigned Integer** for all supported **Traits**. |
| `array` | For `"add"` and `"alter"` **Operations**, this will be a `string` `array`. For `"extract"` **Operations**, this will be an `object` `array` containing one or more *"Nested Traits"*. |
| `boolean` | This can only ever be used with a value of `true` or `false` when using the `"set"` **Operator** **Implicitly** or **Explicitly**, and `null` **Only** when using the `"delete"` **Operator** **Explicitly**. |
| `null` | For `"add"` and `"alter"` **Operations**, `null` is used to **Unset** a **Trait** for which the `"delete"` **Operator** is **Allowed**. For `"extract"` **Operations**, some **Traits** may be returned with a `null` value if they are able to be **Unset** and do not currently have a value. The only exception is for `boolean` **Traits**, which requires the `"delete"` **Operator** to be specified **Explicitly** when providing a `null` value. |

## 💻 Examples

&nbsp;

The following shows an example of a `string` **Trait**.

###### JSON
```json
"base:name": "SQUIDWARD"
```

The following shows an example of a `number` **Trait**.

###### JSON
```json
"omvs:uid": 24
```

The following shows an example of a `string` `array` **Trait** as it would be specified for an `"Add"` or `"alter"` **Operation**.

###### JSON
```json
"add:base:class_authorization": ["FACILITY", "XFACILIT"]
```

The following shows an example of an `object` `array` **Trait** as it would be returned as a result of an `"extract"` **Operation**.

###### JSON
```json
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
]
```

The following shows an example of a `boolean` **Trait**.

###### JSON
```json
"base:special": true
```

The following shows an example of a **Trait** that is being unset on an `"add"` or `"alter"` request by setting the value to `null`.

###### JSON
```json
"base:installation_data": null
```

The following shows an example of a **Trait** that was returned as a result of an `"extract"` **Operation** that is **Unset** and therefore set to `null`.

###### JSON
```json
"base:group_connection_last_connect_date": null
```
