![SEAR Logo](https://raw.githubusercontent.com/Mainframe-Renewal-Project/sear/refs/heads/main/logo.svg)

# Security API for RACF (SEAR)

A standardized JSON interface for RACF that enables seamless exploitation by programming languages that have a foreign language interface for C/C++ and native JSON support.

## Description

As automation becomes more and more prevalent, the need to manage the security environment programmatically increases. On z/OS that means managing a security product like the IBM **Resource Access Control Facility** _(RACF)_. RACF is the primary facility for managing identity, authority, and access control for z/OS. There are more than 50 callable services with assembler interfaces that are part of the RACF API. The complete set of interfaces can be found [here](http://publibz.boulder.ibm.com/epubs/pdf/ich2d112.pdf).

While there are a number of languages that can be used to manage RACF, _(from low level languages like Assembler to higher level languages like REXX)_, the need to be able to easily exploit RACF management functions using existing industry standard programming languages and even programming languages that don't exist yet is paramount. The SEAR project is focused on making RACF management functions available to all programming languages that have native JSON support and a foreign language interface for C/C++. This will make it easier to pivot to new tools and programming languages as technology, skills, and business needs continue to evolve in the foreseeable future.

### Minimum z/OS & Language Versions

All versions of **z/OS** and the **IBM Open Enterprise SDK for Python** that are fully supported by IBM are supported by _SEAR_.

* [z/OS Product Lifecycle](https://www.ibm.com/support/pages/lifecycle/search/?q=5655-ZOS,%205650-ZOS)
* [IBM Open Enterprise SDK for Python Product Lifecycle](https://www.ibm.com/support/pages/lifecycle/search?q=5655-PYT)

### Dependencies

* **R_SecMgtOper (IRRSMO00)**: Security Management Operations.
  * More details about the authorizations required for **IRRSMO00** can be found [in the IBM documentation](https://www.ibm.com/docs/en/zos/latest?topic=operations-racf-authorization).
* **R_Admin (IRRSEQ00)**: RACF Administration API.
  * More details about the authorizations required for **IRRSEQ00** can be found [in the IBM documentation](https://www.ibm.com/docs/en/zos/latest?topic=api-racf-authorization).
* **RACF Subsystem Address Space**: This is a dependency for both **IRRSMO00** and **IRRSEQ00**.
  * More information can be found [in the IBM documentation](https://www.ibm.com/docs/en/zos/latest?topic=considerations-racf-subsystem).
* **z/OS Language Environment Runtime Support**: _SEAR_ is compiled using the **IBM Open XL C/C++ 2.1** compiler, which is still fairly new and requires **z/OS Language Environment** service updates for runtime support.
  * More information can be found in section **5.2.2.2 Operational Requisites** on page **9** in the [Program Directory for IBM Open XL C/C++ 2.1 for z/OS](https://publibfp.dhe.ibm.com/epubs/pdf/i1357012.pdf).

### Installation

> :bulb: _Note: You can also [Download & Install SEAR from GitHub](https://github.com/Mainframe-Renewal-Project/sear/releases)_

```shell
python3 -m pip install pysear
```

### Build from source

Alternatively to installing from Pip, _SEAR_ can be built from source on a z/OS system. _SEAR_ uses a CMake build system, and can be built via a two-step process:

```shell
cmake --preset <preset>
cmake --build --preset <preset> --target <sear,pysear>
```

The first command will configure the build environment and generate build scripts in a directory named `build/<preset>`, then the second command builds the given target.

A complete list of available CMake presets can be found in [CMakePresets.json](CMakePresets.json), but the most useful are:

* `default` - Does not apply any special platform handling, and should work on most platforms.

* `zos` - Applies the `cmake/ibm-clang.cmake` toolchain to the build process. This compiles the project using the IBM-Clang compiler, and works only on z/OS systems.

* `zos-pysear` - Inherits from the `zos` preset. Used internally as part of the Python package build process, and not generally used by hand.

Build artifacts are located within the build directory.

The CMake build process builds static libraries by default. If you instead wish to build shared libraries, append `-DBUILD_SHARED_LIBS=on` to the CMake configure step command (the first of the two) shown above.

## Help

* [GitHub Discussions](https://github.com/Mainframe-Renewal-Project/sear/discussions)
* [System Z Enthusiasts discord](https://discord.gg/sze)

## Maintainers

* Bobby Tjassens Keiser
* Emma Skovgård

## Authors of RACFu

This is a fork of RACFu

* Leonard Carcaramo: <lcarcaramo@ibm.com>
* Elijah Swift: <Elijah.Swift@ibm.com>
* Frank De Gilio: <degilio@us.ibm.com>
* Joe Bostian: <jbostian@ibm.com>
