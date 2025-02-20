---
layout: page
nav_exclude: true
---

![pyRACF Logo](/assets/images/logo.png)

&nbsp;

A standardized JSON interface for RACF that enables seemless exploitation by programming languages that have a foreign language interface for C/C++ and native or third-party JSON support.
{: .fs-6 .fw-300 }

&nbsp;

{: .development_status }
> _**RACFu** is currently in **Alpha**, meaning that some core functionality may still be missing, unstable, and or may still need more thorough testing._

&nbsp;

{: .warning }
> * _RACFu encodes the data it passes to RACF in Code Page `IBM-1047`._
> * _If you are entering information with special or national characters, users viewing or altering this information from terminals using differnt or international codepages may see unexpected data._
> * _Please consult a list of invariant characters to use for such information if this applies to you._

## Mission Statement

As automation becomes more and more prevalent, the need to manage the security environment programmaticaly increases. On z/OS that means managing a security product like the IBM **Resource Access Control Facility** _(RACF)_. RACF is the primary facility for managing identity, authority, and access control for z/OS. There are more than 50 callable services with assembler interfaces that are part of the RACF API. The complete set of interfaces can be found [here](https://www.ibm.com/docs/en/zos/latest?topic=racf-zos-security-server-callable-services).

&nbsp;

While there are a number of languages that can be used to manage RACF, _(from low level lnaguages like Assembler to higher level languages like REXX)_, the need to be able to easily exploit RACF management functions using existing indurstry standard programming languages and even programming languages that don't exist yet is paramount. The RACFu project is focused on making RACF management functions available to all programming languages that have native or third-party JSON support and a foreign language interface for C/C++. This will make it easier to pivot to new tools and programming languages as technology, skills, and business needs continue to evolve in the forseeable future.

## Minimum z/OS & Language Versions

All versions of **z/OS** and the **IBM Open Enterprise SDK for Python** that are fully supported by IBM are supported by RACFu.
* [z/OS Product Lifecycle](https://www.ibm.com/support/pages/lifecycle/search/?q=5655-ZOS,%205650-ZOS)
* [IBM Open Enterprise SDK for Python Product Lifecycle](https://www.ibm.com/support/pages/lifecycle/search?q=5655-PYT)

## Dependencies

* **R_SecMgtOper (IRRSMO00)**: Security Management Operations.
* **R_Admin (IRRSEQ00)**: RACF Administration API.
* **RACF Subsystem Address Space**: This is a dependency for both **IRRSMO00** and **IRRSEQ00**. More information can be found [here](https://www.ibm.com/docs/en/zos/latest?topic=considerations-racf-subsystem).

## Authorizations

The following authorizations are required in order exploit all of the functionality that RACFu provides.
* More details about the authorizations required for **IRRSMO00** can be found [here](https://www.ibm.com/docs/en/zos/latest?topic=operations-racf-authorization).
* More details about the authorizations required for **IRRSEQ00** can be found [here](https://www.ibm.com/docs/en/zos/latest?topic=api-racf-authorization).

&nbsp;

| **Access** | **General Resource Profile** | **Class** | **Functionality** |
| `READ` | `IRR.RADMIN.LISTUSER` | `FACILITY` | Extract **User Profiles** |
| `READ` | `IRR.RADMIN.LISTGRP` | `FACILITY` | Extract **Group Profiles** |
| `READ` | `IRR.RADMIN.RLIST` | `FACILITY` | Extract **General Resource Profiles** |
| `READ` | `IRR.RADMIN.LISTDSD` | `FACILITY` | Extract **Data Set Profiles** |
| `READ` | `IRR.RADMIN.SETROPTS.LIST` | `FACILITY` | List **RACF Options** |
| `READ` | `IRR.IRRSMO00.PRECHECK` | `XFACILIT` | **Alter** and **Add** Profiles |
| `UPDATE` | `<userid>.IRRSMO00` | `SURROGAT` | Run **Add**, **Alter**, and **Delete** **Commands** as a **Specific Userid** |

## Install

&nbsp;

{: .note }
> _You may also optionally [Download & Install RACFu From GitHub](https://github.com/ambitus/racfu/releases)._

&nbsp;

```shell
python3 -m pip install racfu
```

## Use

```python
>>> from racfu import racfu
>>> result = racfu({"operation": "extract", "admin_type": "user", "profile_name": "SQUIDWRD"})
>>> result.result
{'profile': {'base': {'base:audit_logging': False, 'base:audit_responsibility': False, 'base:auditor': False, 'base:automatic_data_set_protection': False, 'base:create_date': '09/13/24', 'base:default_group': 'SYS1', 'base:group_connections': [{'base:group_connection_auditor': False, 'base:group_connection_automatic_data_set_protection': False, 'base:group_connection_create_date': '09/13/24', 'base:group_connection_data_set_access': False, 'base:group_connection_group': 'SYS1', 'base:group_connection_last_connect_date': None, 'base:group_connection_last_connect_time': None, 'base:group_connection_operations': False, 'base:group_connection_owner': 'LEONARD', 'base:group_connection_resume_date': None, 'base:group_connection_revoke_date': None, 'base:group_connection_revoked': False, 'base:group_connection_special': False, 'base:group_connection_universal_access': 'NONE', 'base:group_connection_used_count': 0}], 'base:group_data_set_access': False, 'base:has_passphrase': False, 'base:has_password': False, 'base:logon_allowed_days': [{'base:logon_allowed_day': 'SUNDAY'}, {'base:logon_allowed_day': 'MONDAY'}, {'base:logon_allowed_day': 'TUESDAY'}, {'base:logon_allowed_day': 'WEDNESDAY'}, {'base:logon_allowed_day': 'THURSDAY'}, {'base:logon_allowed_day': 'FRIDAY'}, {'base:logon_allowed_day': 'SATURDAY'}], 'base:logon_allowed_time': 'ANYTIME', 'base:mfa_password_fallback': False, 'base:name': 'SQUIDWARD', 'base:operations': False, 'base:owner': 'LEONARD', 'base:passphrase_change_interval': 0, 'base:passphrase_enveloped': False, 'base:password_change_interval': 186, 'base:password_enveloped': False, 'base:protected': True, 'base:restrict_global_access_checking': False, 'base:revoked': False, 'base:special': False}, 'omvs': {'omvs:home_directory': '/u/squidwrd', 'omvs:uid': 24}}, 'return_codes': {'racf_reason_code': 0, 'racf_return_code': 0, 'racfu_return_code': 0, 'saf_return_code': 0}}
```

## Architecture

&nbsp;

{: .warning }
> _Just because a **Programming Language Exploiter** is shown on this architecture diagram does not mean that there is or will be an interface created, maintained, and distributed by the RACFu team for that programming language. The interfaces currently maintained and distributed by the RACFu team can be found [here](./interfaces/)._

&nbsp;

<pre class="mermaid">
  flowchart TD
    c(C/C++ Exploiter)-- JSON (ASCII) ---RACFu
    style c fill:#01559e,color:#fff,stroke:#01559e
    python(Python Exploiter)-- JSON (ASCII) ---RACFu
    style python fill:#ffcb3c,color:#000,stroke:#ffcb3c
    nodejs(Node.JS Exploiter)-- JSON (ASCII) ---RACFu
    style nodejs fill:#417e38,color:#fff,stroke:#417e38
    java(Java Exploiter)-- JSON (ASCII) ---RACFu
    style java fill:#ec2025,color:#fff,stroke:#ec2025
    subgraph C/C+
        RACFu(["RACFu (64-bit XPLINK ASCII)"])
        style RACFu fill:#0096ff,color:#fff,stroke:#0096ff
        RACFu --- Extract(Extract)
        RACFu --- Add(Add)
        RACFu --- Alter(Alter)
        RACFu --- Delete(Delete)
        Add-- XML (EBCDIC) ---IRRSMO00("IRRSMO00 (64-bit OSLINK EBCDIC)")
        Alter-- XML (EBCDIC) ---IRRSMO00
        Delete-- XML (EBCDIC) ---IRRSMO00
        style IRRSMO00 fill:#33a,color:#fff,stroke:#33a
    end
    subgraph HLASM
        Extract-- Binary (EBCDIC) ---IRRSEQ00("IRRSEQ00 (31-bit OSLINK EBCDIC)")
        IRRSMO00-- Binary (EBCDIC) ---IRRSEQ00
        style IRRSEQ00 fill:#33a,color:#fff,stroke:#33a
    end
    IRRSEQ00 --- SAF(SAF)
    SAF --- RACF[(RACF)]

</pre>
