#
# Copyright (c) 2019 Wee Loong Kuan
#
# This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
# top-level directory of this distribution.
#

bml_add_test("utilities.declval" declval.cpp)
bml_add_test("utilities.forward" forward.cpp)
bml_add_compile_failure_test("utilities.forward.fail.rvalue_to_lvalue"
    forward.fail.rvalue_to_lvalue.cpp "Cannot forward rvalue as lvalue.")
bml_add_compile_failure_test("utilities.forward.fail.lvalue_arg_cv_mismatch"
    forward.fail.lvalue_arg_cv_mismatch.cpp)
bml_add_compile_failure_test("utilities.forward.fail.rvalue_arg_cv_mismatch"
    forward.fail.rvalue_arg_cv_mismatch.cpp)
bml_add_compile_failure_test("utilities.forward.fail.missing_t" forward.fail.missing_t.cpp)
bml_add_test("utilities.max" max.cpp)
