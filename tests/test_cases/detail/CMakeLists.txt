#
# Copyright (c) 2019 Wee Loong Kuan
#
# This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
# top-level directory of this distribution.
#

bml_add_test("detail.size_to_ptrdiff" size_to_ptrdiff.cpp)
bml_add_compile_failure_test("detail.size_to_ptrdiff.fail.overflow"
    size_to_ptrdiff.fail.overflow.cpp
    "Input is larger than PTRDIFF_MAX.")

add_subdirectory(macros)
