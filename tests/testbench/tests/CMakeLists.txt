#
# Copyright (c) 2018 Wee Loong Kuan
#
# This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
# top-level directory of this distribution.
#

add_executable(bml_testbench.tests.core core.cpp)
target_link_libraries(bml_testbench.tests.core bml_testbench)
add_test(NAME bml_testbench.tests.core COMMAND bml_testbench.tests.core)

add_executable(bml_testbench.tests.string_display string_display.cpp)
target_link_libraries(bml_testbench.tests.string_display bml_testbench)
add_test(NAME bml_testbench.tests.string_display COMMAND bml_testbench.tests.string_display)
set_tests_properties(bml_testbench.tests.string_display PROPERTIES
    PASS_REGULAR_EXPRESSION "^String from display_ascii.\nString from puts.\n$")

add_executable(bml_testbench.tests.failure_exit_code failure_exit_code.cpp)
target_link_libraries(bml_testbench.tests.failure_exit_code bml_testbench)
add_test(NAME bml_testbench.tests.failure_exit_code COMMAND bml_testbench.tests.failure_exit_code)
set_tests_properties(bml_testbench.tests.failure_exit_code PROPERTIES WILL_FAIL TRUE)
