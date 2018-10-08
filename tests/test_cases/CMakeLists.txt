#
# Copyright (c) 2018 Wee Loong Kuan
#
# This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
# top-level directory of this distribution.
#

#
# Adds a normal test case.
#
# Arguments:
# test_name - Test name passed to add_test. This must be a valid target name as a new target with
#             this name will be created.
# source_file - Source file containing test code.
#
function(bml_add_test test_name source_file)
    add_executable(${test_name} "${source_file}")
    target_link_libraries(${test_name} bml bml_testbench)
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

#
# Adds a compile failure test case.
#
# Arguments:
# test_name - Test name passed to add_test. This must be a valid target name as a new target with
#             this name will be created.
# source_file - Source file containing test code.
# 3rd argument (optional) - Regular expression for PASS_REGULAR_EXPRESSION. If this is not provided,
#                           the test will pass as long as compilation fails.
#
function(bml_add_compile_failure_test test_name source_file)
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
