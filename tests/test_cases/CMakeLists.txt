#
# Copyright (c) 2019 Wee Loong Kuan
#
# Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
# https://llvm.org/LICENSE.txt for license information.
#
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#

#
# Adds a normal test case.
#
# Arguments:
# test_name - Test name. This is prefixed with "bml.tests." before being passed to add_executable
#             (to create the test target) and add_test. Note that this means the test name must also
#             be a valid target name.
# source_file - Source file containing test code.
#
function(bml_add_test test_name source_file)
    string(PREPEND test_name bml.tests.)
    add_executable(${test_name} "${source_file}")
    target_link_libraries(${test_name} bml bml_testbench)
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

#
# Adds a compile failure test case.
#
# Arguments:
# test_name - Test name. This is prefixed with "bml.tests." before being passed to add_executable
#             (to create the test target) and add_test. Note that this means the test name must also
#             be a valid target name.
# source_file - Source file containing test code.
# 3rd argument (optional) - Regular expression for PASS_REGULAR_EXPRESSION. If this is not provided,
#                           the test will pass as long as compilation fails.
#
function(bml_add_compile_failure_test test_name source_file)
    string(PREPEND test_name bml.tests.)
    add_executable(${test_name} EXCLUDE_FROM_ALL "${source_file}")
    target_link_libraries(${test_name} bml bml_testbench)
    
    add_test(NAME ${test_name} COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_BINARY_DIR}"
        --target ${test_name})
    
    if(ARGC GREATER 2)
        set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION "${ARGV2}")
    else()
        set_tests_properties(${test_name} PROPERTIES WILL_FAIL TRUE)
    endif()
endfunction()

# Start adding tests.
add_subdirectory(containers)
add_subdirectory(detail)
add_subdirectory(type_traits)
add_subdirectory(utilities)

bml_add_test("basic_types.consolidated_header" basic_types.consolidated_header.cpp)
bml_add_test("containers.consolidated_header" containers.consolidated_header.cpp)
bml_add_test("type_traits.consolidated_header" type_traits.consolidated_header.cpp)
bml_add_test("utilities.consolidated_header" utilities.consolidated_header.cpp)
