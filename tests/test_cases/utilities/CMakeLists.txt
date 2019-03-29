#
# Copyright (c) 2019 Wee Loong Kuan
#
# BareMetalLib is based on libc++ (https://libcxx.llvm.org/).
# 
# This file is licensed under under the Apache License v2.0 with LLVM Exceptions. For more details,
# see the LICENSE.md file in the top-level directory of this distribution, or copy at 
# https://llvm.org/LICENSE.txt.
#
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
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
bml_add_test("utilities.move" move.cpp)
bml_add_compile_failure_test("utilities.move.fail.move_unmovable" move.fail.move_unmovable.cpp)
bml_add_test("utilities.min" min.cpp)
bml_add_test("utilities.addressof" addressof.cpp)
bml_add_compile_failure_test("utilities.addressof.fail.rvalue_address"
    addressof.fail.rvalue_address.cpp)
bml_add_test("utilities.new" new.cpp)
bml_add_test("utilities.launder" launder.cpp)
bml_add_compile_failure_test("utilities.launder.fail.launder_function"
    launder.fail.launder_function.cpp "Cannot launder function.")
bml_add_compile_failure_test("utilities.launder.fail.launder_void" launder.fail.launder_void.cpp
    "Cannot launder void.")
bml_add_test("utilities.swap" swap.cpp)
bml_add_test("utilities.swap_ranges" swap_ranges.cpp)
bml_add_test("utilities.integer_sequence" integer_sequence.cpp)
bml_add_compile_failure_test("utilities.integer_sequence.fail.non_integral"
    integer_sequence.fail.non_integral.cpp
    "T is not integral..")
bml_add_test("utilities.make_integer_sequence" make_integer_sequence.cpp)
bml_add_compile_failure_test("utilities.make_integer_sequence.fail.negative_n"
    make_integer_sequence.fail.negative_n.cpp)
bml_add_test("utilities.index_sequence" index_sequence.cpp)
bml_add_test("utilities.make_index_sequence" make_index_sequence.cpp)
