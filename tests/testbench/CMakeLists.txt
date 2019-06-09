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

# Create the testbench target.
#
# Note: This is never installed, so we don't need the BUILD_INTERFACE + INSTALL_INTERFACE idiom.
add_library(bml_testbench STATIC "")
target_compile_features(bml_testbench INTERFACE cxx_std_17)
target_include_directories(bml_testbench PUBLIC include)

# Pull in platform-specific code.
target_sources(bml_testbench PRIVATE
    "src/platform/${CMAKE_CXX_COMPILER_ID}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}.cpp")

# Configure the current compiler to disable - as much as possible - C++ features listed as eschewed
# in README.md.
include("cmake/${CMAKE_CXX_COMPILER_ID}BuildSettings.cmake")

# Bring in tests.
add_subdirectory(tests)
