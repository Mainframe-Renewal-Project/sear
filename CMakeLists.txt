#----------------------------------------------------------------------#
# SEAR API build script                                                #
#                                                                      #
# This script can build:                                               #
# - SEAR                                                               #
#   - as an archive library (libsear.a)                                #
#     cmake --preset <your preset>                                     #
#     cmake --build --preset <your preset> --target sear               #
#                                                                      #
#   - as a shared library (libsear.so + libsear.x)                     #
#     cmake --preset <your preset> -DBUILD_SHARED_LIBS=on              #
#     cmake --build --preset <your preset> --target sear               #
#                                                                      #
# - pysear                                                             #
#   - as a python wheel with sear incorporated                         #
#     python -m build .                                                #
#                                                                      #
# - test_runner                                                        #
#   - as a stand alone executable (that requires libsear.so)           #
#     cmake --preset linux-test -DBUILD_SHARED_LIBS=on                 #
#     cmake --build --preset linux-test --target sear                  #
#     cmake --build --preset linux-test --target test_runner           #
#                                                                      #
# - debug                                                              #
#   - as a stand alone executable                                      #
#     cmake --preset zos -DBUILD_SHARED_LIBS=on                        #
#     cmake --build --preset zos --target sear                         #
#     cmake --build --preset zos --target debug                        #
#                                                                      #
# - lint                                                               #
#   - executes clang-format for most .cpp and .hpp files,              #
#     this is executed in a Github workflow                            #
#                                                                      #
# - check                                                              #
#   - execute cppcheck on the sear code,                               #
#     this is executed in a Github workflow                            #
#                                                                      #
# - fuzz                                                               #
#   - compile sear code with fuzz and run fuzz security checks         #
#     this is exectuted in a Github workflow                           #
#----------------------------------------------------------------------#

cmake_minimum_required(VERSION 3.24)

project(sear C CXX ASM)
set(CXX_STANDARD 14)

# This option is used when building the Python wheel
option(SEAR_ENABLE_PYTHON "Enables building the Python language module." OFF)

# This option is used on Linux to build SEAR with mocked unit tests
option(SEAR_UNIT_TEST "Builds tests" OFF)

find_package(OpenSSL REQUIRED)

# If the SEAR_UNIT_TEST variable is ON, don't go look for ZOSLIB library,
# add the tests/zoslib folder to sear include directories and skip the
# assembly of irrseq00.s.
if (SEAR_UNIT_TEST)
    set(ZOSLIB "")
    set(ZOSLIB_INCLUDE "tests/zoslib")
    set(IRRSEQ00 "")
else()
    find_library(ZOSLIB libzoslib.a REQUIRED)
    set(ZOSLIB_INCLUDE "")
    set(IRRSEQ00 "sear/irrseq00/irrseq00.s")
endif()

# The library for SEAR
add_library(
    sear

    sear/irrsdl00/irrsdl00.cpp
    sear/irrsdl00/keyring_extractor.cpp
    sear/irrsdl00/keyring_modifier.cpp
    sear/irrsdl00/keyring_post_processor.cpp

    # Assemblying irrseq00.s is dependent on the platform,
    # it only works on Z
    "${IRRSEQ00}"
    sear/irrseq00/profile_extractor.cpp
    sear/irrseq00/profile_post_processor.cpp

    sear/irrsmo00/irrsmo00_error.cpp
    sear/irrsmo00/irrsmo00.cpp
    sear/irrsmo00/xml_generator.cpp
    sear/irrsmo00/xml_parser.cpp

    sear/key_map/key_map.cpp
    sear/validation/trait_validation.cpp
    sear/logger.cpp
    sear/sear_error.cpp
    sear/sear.cpp
    sear/security_admin.cpp
    sear/security_request.cpp

    externals/json-schema-validator/json-patch.cpp
    externals/json-schema-validator/json-schema-draft7.json.cpp
    externals/json-schema-validator/json-uri.cpp
    externals/json-schema-validator/json-validator.cpp
    externals/json-schema-validator/smtp-address-validator.cpp
    externals/json-schema-validator/string-format-check.cpp
)
# SEAR's include directories
target_include_directories(
    sear PUBLIC
    sear
    sear/irrsdl00
    sear/irrseq00
    sear/irrsmo00
    sear/key_map
    sear/validation
    externals/json
    externals/json-schema-validator
    # tests/zoslib include directory only needed on Linux build
    "${ZOSLIB_INCLUDE}"
    # add generated header to include path
    "${CMAKE_CURRENT_BINARY_DIR}/sear"
)
# Extra defines for compiling SEAR
target_compile_definitions(sear PUBLIC _POSIX_C_SOURCE=200112L)

# Embed json schema into sear_schema.hpp
file(READ schema.json SEAR_SCHEMA)
configure_file(sear/sear_schema.hpp.in sear/sear_schema.hpp)

# Ugly hack to get shared library to work on Z
set(STRT "")

if (BUILD_SHARED_LIBS AND NOT SEAR_UNIT_TEST)
    set(STRT "-Wl,-e,CELQSTRT")
endif()

# Create the sear target
target_link_libraries(sear PRIVATE "${STRT}" OpenSSL::SSL "${ZOSLIB}")

# If we're building the Python wheel
if (SEAR_ENABLE_PYTHON)
    find_package(Python3 REQUIRED COMPONENTS Development Development.SABIModule)

    Python3_add_library(pysear MODULE USE_SABI 3.12 sear/python/_sear.c)
    target_link_libraries(pysear PRIVATE sear Python3::Python)

    if (DEFINED SEAR_PYTHON_EXTENSION_PATH)
        message(STATUS "Installing Python module to: ${SEAR_PYTHON_EXTENSION_PATH}")
        cmake_path(GET SEAR_PYTHON_EXTENSION_PATH FILENAME MODULE_FILENAME)
        cmake_path(GET SEAR_PYTHON_EXTENSION_PATH PARENT_PATH MODULE_DIR)
        install(PROGRAMS "$<TARGET_FILE:pysear>" DESTINATION "${MODULE_DIR}" RENAME "${MODULE_FILENAME}")
    endif()
endif()

# The test_runner executable
add_executable(
    test_runner
    tests/test_runner.cpp
    tests/unit_test_utilities.cpp
    tests/irrsdl00/test_irrsdl00.cpp
    tests/irrseq00/test_irrseq00.cpp
    tests/irrsmo00/test_irrsmo00.cpp
    tests/mock/irrsdl64.cpp
    tests/mock/irrseq00.cpp
    tests/mock/irrsmo64.cpp
    tests/unity/unity.c
    tests/validation/test_parameter_validation.cpp
    tests/zoslib/zoslib.cpp
)
# test_runner's include directories
target_include_directories(
    test_runner PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    sear
    sear/irrsdl00
    sear/irrseq00
    sear/irrsmo00
    sear/key_map
    sear/validation
    externals/json
    externals/json-schema-validator
    tests/irrsdl00
    tests/zoslib
)
# Extra defines for compiling test_runner
target_compile_definitions(test_runner PUBLIC UNIT_TEST UNITY_OUTPUT_COLOR)
# Create the test_runner target
target_link_libraries(test_runner PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/libsear.so")

# The debug executable
add_executable(
    debug
    debug/debug.c
)
# Create the debug target
target_link_libraries(debug PRIVATE)

# Custom target 'link', executes clang-format for most .cpp and .hpp files
add_custom_target(lint ALL
    COMMAND find ${CMAKE_CURRENT_SOURCE_DIR}/sear/ -type f -name "*.cpp" -exec clang-format-19 --verbose --Werror --dry-run -i {} "\;"
    COMMAND find ${CMAKE_CURRENT_SOURCE_DIR}/sear/ -type f -name "*.hpp" -exec clang-format-19 --verbose --Werror --dry-run -i {} "\;"
    COMMAND find ${CMAKE_CURRENT_SOURCE_DIR}/tests/ -type f -name "*.cpp" -exec clang-format-19 --verbose --Werror --dry-run -i {} "\;"
    COMMAND find ${CMAKE_CURRENT_SOURCE_DIR}/tests/ -type f -name "*.hpp" -exec clang-format-19 --verbose --Werror --dry-run -i {} "\;"
)

# Custom target 'check', executes 'cppcheck' on the sear code
add_custom_target(check ALL
    COMMAND "cppcheck"
                "--suppress='missingIncludeSystem'"
                "--suppress='useStlAlgorithm'"
                "--inline-suppr"
                "--language=c++"
                "--std=c++${CXX_STANDARD}"
                "--enable=all"
                "--force"
                "--check-level=exhaustive"
                "--inconclusive"
                "--error-exitcode=1"
                "-D __ptr32="
                "-D _POSIX_C_SOURCE=200112L"
                "-I${CMAKE_CURRENT_SOURCE_DIR}/sear"
                "-I${CMAKE_CURRENT_SOURCE_DIR}/sear/irrsdl00"
                "-I${CMAKE_CURRENT_SOURCE_DIR}/sear/irrseq00"
                "-I${CMAKE_CURRENT_SOURCE_DIR}/sear/irrsmo00"
                "-I${CMAKE_CURRENT_SOURCE_DIR}/sear/key_map"
                "-I${CMAKE_CURRENT_SOURCE_DIR}/sear/validation"
                "-I${CMAKE_CURRENT_SOURCE_DIR}/tests/zoslib"
                "-I${CMAKE_CURRENT_BINARY_DIR}/sear"
                "${CMAKE_CURRENT_SOURCE_DIR}/sear"
)

# The fuzz executable
add_executable(
    fuzz

    tests/fuzz.cpp
    tests/mock/irrsdl64.cpp
    tests/mock/irrseq00.cpp
    tests/mock/irrsmo64.cpp
    tests/zoslib/zoslib.cpp

    sear/irrsdl00/irrsdl00.cpp
    sear/irrsdl00/keyring_extractor.cpp
    sear/irrsdl00/keyring_modifier.cpp
    sear/irrsdl00/keyring_post_processor.cpp

    sear/irrseq00/profile_extractor.cpp
    sear/irrseq00/profile_post_processor.cpp

    sear/irrsmo00/irrsmo00_error.cpp
    sear/irrsmo00/irrsmo00.cpp
    sear/irrsmo00/xml_generator.cpp
    sear/irrsmo00/xml_parser.cpp

    sear/key_map/key_map.cpp
    sear/validation/trait_validation.cpp
    sear/logger.cpp
    sear/sear_error.cpp
    sear/sear.cpp
    sear/security_admin.cpp
    sear/security_request.cpp

    externals/json-schema-validator/json-patch.cpp
    externals/json-schema-validator/json-schema-draft7.json.cpp
    externals/json-schema-validator/json-uri.cpp
    externals/json-schema-validator/json-validator.cpp
    externals/json-schema-validator/smtp-address-validator.cpp
    externals/json-schema-validator/string-format-check.cpp
)
# fuzz's include directories
target_include_directories(
    fuzz PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    sear
    sear/irrsdl00
    sear/irrseq00
    sear/irrsmo00
    sear/key_map
    sear/validation
    externals/json
    externals/json-schema-validator
    tests/irrsdl00
    tests/zoslib
    "${CMAKE_CURRENT_BINARY_DIR}/sear"
)
# Add sanitize flags to fuzz compilation
target_compile_options(fuzz PUBLIC -fsanitize=fuzzer -fsanitize=undefined -fsanitize=address)
# Add sanitize flags to fuzz linking
target_link_options(fuzz PUBLIC -fsanitize=fuzzer -fsanitize=undefined -fsanitize=address)
# Create the fuzz target
target_link_libraries(fuzz PRIVATE OpenSSL::SSL "${ZOSLIB}")
