# Contributing to SEAR

Thank you for taking the time to contribute to SEAR!
The following are a set of guidelines to help you contribute.

## Table Of Contents

* [Before Getting Started](#before-getting-started)

* [Ways to Contribute](#ways-to-contribute)

  * [Coding](#coding)

  * [pre-commit Hooks](#pre-commit-hooks)

  * [Adding New Functionality](#adding-new-functionality)

  * [Testing](#testing)

  * [Fixing Bugs](#fixing-bugs)

  * [Adding or Fixing Documentation](#adding-or-fixing-documentation)

  * [Branch Naming Conventions](#branch-naming-conventions)

* [Style Guidelines](#style-guidelines)

* [Static Code Analysis](#static-code-analysis)

* [Contribution checklist](#contribution-checklist)

* [Found a bug?](#found-a-bug)

## Before Getting Started

> :warning: _All code contributed must be made under an Apache 2 license._
>
> :warning: _All contributions must be accompanied by a [Developer Certification of Origin (DCO) signoff](https://github.com/openmainframeproject/tsc/blob/master/process/contribution_guidelines.md#developer-certificate-of-origin)._

## Ways to Contribute

There are many ways to contribute to the project. You can write code, work on the documentation, provide tests, report bugs or provide suggestions for improvement.

### Coding

If you want to write code, a good way to get started is by looking at the issues section of this repository. Look for the **Good First Issue** tag. Good First Issues are great as a first contribution.

### pre-commit Hooks

To ensure `clang-format`, `cppcheck`, and **unit tests** are always run against your code on **every commit**, set up the **pre-commit hooks**.

* Install [`pre-commit`](https://pre-commit.com/).
* Setup **pre-commit Hooks**:

  ```shell
  pre-commit install
  ```

### Adding New Functionality

If you want to contribute new functionality, open a GitHub pull request against the `dev` branch with your changes. In the PR, make sure to clearly document the new functionality including why it is valuable.

### Testing

The main way to test SEAR is to write **unit tests** in the [`tests`](tests) directory, which contains **mocks** that mock the real **IRRSMO00** and **IRRSEQ00** RACF callable services to enable **request generation** and **response parsing** logic to be validated in a **fast** and **automated** way. The unit test suite can be run by just running `make test` in the root directory of this repository. It is also recommended to do manual testing on a **z/OS system** for **new functionality** and **bug fixes** to test the real calls to **IRRSMO00** and **IRRSEQ00**.

* **Unit Tests**

  > :bulb: _See the [Unity Unit Testing For C](https://www.throwtheswitch.org/unity) documentation for more details on writing test cases._
  > :white_check_mark: _In order to facilitate development and unit testing, the real **API calls** to **IRRSMO00** and **IRRSEQ00** have been mocked in [`tests/mock`](tests/mock). Additionally, implementations of some **z/OS specific C/C++ Runtime Library functions** are provided in [`tests/zoslib`](tests/zoslib) to enable the SEAR unit test suite to more or less be run on any 64-bit POSIX system where the `clang` compiler is installed. This ensures that development and testing can be done when contributors do not have access to a z/OS system, and also enables faster iteration since contributors can just run `make test` on their workstation without needing to copy the files to a z/OS system to run the unit tests._

  * Unit tests should be placed in the **subdirectory** corresponding to the **RACF callable service** you are creating a test for. The main focus of these tests is to validate the **generation of requests** to and **parsing of responses** from the **IRRSMO00** and **IRRSEQ00** callable services, and more generally testing various other code paths in the SEAR code. There are directories called `request_samples` and `response_samples` in the [`tests/irrseq00`](tests/irrseq00) and [`tests/irrsmo00`](tests/irrseq00) test folders to put request and response samples. All **raw request samples** and **raw response samples** for a given callable service should end with the `.bin` file extension. `get_raw_sample()` and `get_json_sample()` are defined in [`tests/unit_test_utilities.hpp`](tests/unit_test_utilities.hpp) to facilitate the loading of request and response samples in test cases. Other categories of test cases and test utilities must follow the same conventions described here.

    > _**Example:** A test case for verifying that SEAR can parse the result of an **extract user request** should be placed in the [`test_irrseq00.cpp`](tests/irrseq00/test_irrseq00.cpp) unit test module within the [`irrseq00`](tests/irrseq00) subdirectory. A **JSON request** sample containing the parameters for a **profile extract request** should be created in the [`irrseq00/request_samples/user`](tests/irrseq00/request_samples/user) directory. A **raw response** sample that contains the **mocked** result of the profile extract request and the corresponding expected **post-processed JSON response** should be created in the [`irrseq00/result_samples/user`](tests/irrseq00/result_samples/user) directory. Request/response samples should be loaded in the unit test case using the `get_raw_sample()` and `get_json_sample()` functions defined in [`tests/unit_test_utilities.hpp`](tests/unit_test_utilities.hpp). [`tests/unit_test_utilities.hpp`](tests/unit_test_utilities.hpp) also provides various other utility functions for facilitating the creation of test cases that should be used when applicable. [`irrseq00.hpp`](tests/mock/irrseq00.hpp) and [`irrsmo64.hpp`](tests/mock/irrsmo64.hpp) provide all of the necessary **global varibales** for mocking the result of requests made to `callRadmin()` and `IRRSMO64()` respectively._

* **Functional Verification Tests**
  > :warning: _Ensure that the `SEAR_FVT_USERID` environment variable is set to a z/OS userid that doesn't exist on the system where the functional verifification tests are being run prior to running `make fvt`._

  * In order to ensure that the real API calls to **IRRSEQ00** and **IRRSMO00** are working, build and install the Python distribution of SEAR from your branch/fork on a z/OS system and run `make fvt`.

### Fixing Bugs

If you fix a bug, open a GitHub pull request against the `dev` branch with the fix. In the PR, make sure to clearly describe the problem and the solution approach.

### Adding or Fixing Documentation

If any updates need to be made to the SEAR documentation, open a GitHub pull request against the `gh-pages-dev` branch with your changes. This may include updates to document new functionality or updates to correct errors or mistakes in the existing documentation.

### Branch Naming Conventions

Code branches should use the following naming conventions:

* `wip/name` _(Work in progress branch that likely won't be finished soon)_
* `feat/name` _(Branch where new functionality or enhancements are being developed)_
* `bug/name` _(Branch where one or more bugs are being fixed)_
* `junk/name` _(Throwaway branch created for experimentation)_

## Style Guidelines

:bulb: _These steps can be done automatically using the [pre-commit Hooks](#pre-commit-hooks)._

The use of the `clang-format` code formatter is required.

The following code style conventions should be followed:

* Variable names should use snake case _(i.e., `my_variable`)_.
* Pointer variables should start with `p_` _(i.e., `p_my_pointer`)_.
* Class variables should end with an `_` to help differentiate between class variables and local function variables _(i.e., `my_class_variable_`)_.
* Class name should use pascal case _(i.e., `MyClass`)_.
* Function names should use camel case _(i.e., `myFunction()`)_.
* When calling a class function within the same class that function is a member of, the following syntax should be used to make it clear that a function within the same class is being called.

  ```cpp
  MyClass::myFunction();
  ```

* Structs should use the following naming convention.

  ```cpp
  typedef struct {
    int member_1;
    char member_2[5];
  } my_struct_t;
  ```

## Static Code Analysis

:bulb: _These steps can be done automatically using the [pre-commit Hooks](#pre-commit-hooks)._

`cppcheck` will be run against all code contributions to ensure that contributions don't inadvertently introduce any vulnerabilities or other significant issues. All contributions must have no `cppcheck` complaints. False positives and minor complaints may be [suppressed](http://cppcheck.net/manual.html#inline-suppressions) when it make sense to do so, but this should only be done very sparingly. All `cppcheck` comlpaints should be evaluated and corrected when it is possible and makes sense to do so. You can run `cppcheck` by running `make check`.

## Contribution checklist

When contributing to SEAR, think about the following:

* Make any necessary updates to `pyproject.toml`.
* Make any necessary updates to `README.md`.
* Make any necessary updates to the GitHub pages documentation in the `gh-pages` branch _(Pull requests should be opened against the `gh-pages-dev` branch)_.
* Add any necessary test cases to `/tests`.
* Ensure that you have **pre-commit Hooks** setup to ensure that `clang-format`, `cppcheck`, and **unit tests** are run against the code for every commit you make.
* Run unit tests by running `make test`.
* Run LLVM LibFuzzer by running `make fuzz`.
* Run functional verification tests by running `make fvt`.
* Run `cppcheck` static code analysis cans by running `make check`.

## Found a bug?

If you find a bug in the code, please open the an issue.
In the issue, clearly state what is the bug, and  any other details that can be helpful.
