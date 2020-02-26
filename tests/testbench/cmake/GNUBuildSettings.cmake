#
# Copyright (c) 2018 Wee Loong Kuan
#
# Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
# https://llvm.org/LICENSE.txt for license information.
#
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#

target_compile_options(bml_testbench PUBLIC
    -ffreestanding -nostdinc++ -fno-rtti -fno-exceptions -Wall -Wextra)

target_link_libraries(bml_testbench PUBLIC gcc -nostdlib)
