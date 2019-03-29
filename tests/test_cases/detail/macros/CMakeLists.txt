#
# Copyright (c) 2018 Wee Loong Kuan
#
# BareMetalLib is based on libc++ (https://libcxx.llvm.org/).
# 
# This file is licensed under under the Apache License v2.0 with LLVM Exceptions. For more details,
# see the LICENSE.md file in the top-level directory of this distribution, or copy at 
# https://llvm.org/LICENSE.txt.
#
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#

bml_add_test("detail.macros.stringize" stringize.cpp)
bml_add_test("detail.macros.compiler_specific_file" compiler_specific_file.cpp)
