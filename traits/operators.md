---
layout: default
parent: Traits
nav_order: z
---

# Operators

The following operators can be used to tell RACF how a trait should be processed by add and alter oprations.
{: .fs-6 .fw-300 }

&nbsp;

Operators are specified using the format `<operator>:<segment>:<trait>`, where the `<operator>` token is the **Operator**, the `<segment>` token is the **RACF Segment**, and the `<trait>` token is the **Trait**.

&nbsp;

{: .note }
> _When **NO** **Operator** is **Explicitly** specified, `"set"` will be the assumed **Operator** when the corresponding **Trait** value is **NOT** `null`, and `"delete"` when the when the corresponding **Trait** value is `null`.  The only exception is for `boolean` **Traits**, which requires the `"delete"` **Operator** to be specified **Explicitly** when providing a `null` value. It is recommended to omit **Operators** when possible to keep the specification of **Traits** in `"add"` and `"alter"` **Operations** concise._

&nbsp;

{: .note }
> _Every **Operator** is not supported for every **Trait**. Check the corresponding [Trait Table](../../traits/) to see what **Operators** are supported for a given **Trait**._

&nbsp;

| **Operator** | **Description** |
| `"set"` | **Set** A **Trait** to a value. |
| `"add"` | **Add** one or more items to a `string` `array` **Trait**. |
| `"remove"` | **Remove** one or more items from a `string` `array` **Trait**. |
| `"delete"`| **Delete** the existing value for a **Trait** if there is one. |

## 💻 Examples

&nbsp;

The following **RACFu Trait JSON** describes modifications to the following **User Traits**:
* **Set** the **OMVS UID** to `24`.
* **Add** `FACILITY` and `XFACILIT` to the **Class Authorizations** list.
* **Remove** `TERMINAL` from the **Class Authorizations** list.
* **Delete** the existing value for **TSO User Data** if there is one.

###### JSON
```json
{
  "set:omvs:uid": 24,
  "add:base:class_authorization": ["FACILITY", "XFACILIT"],
  "remove:base:class_authorization": "TERMINAL",
  "delete:tso:user_data": null
}
```

The following **RACFu Trait JSON** describes modifications to the following **User Traits** **Without** the use of **Operators**:
* **Set** the **OMVS UID** to `24`.
* **Delete** the existing value for **TSO User Data** if there is one.

###### JSON
```json
{
  "omvs:uid": 24,
  "tso:user_data": null
}
```
