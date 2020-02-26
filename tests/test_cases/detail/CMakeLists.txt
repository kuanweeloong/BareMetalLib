#
# Copyright (c) 2019 Wee Loong Kuan
#
# Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
# https://llvm.org/LICENSE.txt for license information.
#
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#

bml_add_test("detail.size_to_ptrdiff" size_to_ptrdiff.cpp)
bml_add_compile_failure_test("detail.size_to_ptrdiff.fail.overflow"
    size_to_ptrdiff.fail.overflow.cpp
    "Input is larger than PTRDIFF_MAX.")
bml_add_test("detail.INVOKE" INVOKE.cpp)

add_subdirectory(macros)
