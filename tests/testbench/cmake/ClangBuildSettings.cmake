#
# Copyright (c) 2018 Wee Loong Kuan
#
# This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
# top-level directory of this distribution.
#

target_compile_options(bml_testbench PUBLIC
    -ffreestanding -nostdinc++ -fno-rtti -fno-exceptions -Wall -Wextra)

target_link_libraries(bml_testbench PUBLIC gcc -nostdlib)
