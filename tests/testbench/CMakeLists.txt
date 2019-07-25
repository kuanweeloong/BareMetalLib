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
#
# BML_TESTBENCH_ARCH identifies the OS architecture, and is used instead of CMAKE_SYSTEM_PROCESSOR
# beacuse of cases such as:
#   - Building on an x86 OS running on an x86_64 processor.
#   - CMAKE_SYSTEM_PROCESSOR or the architecture itself being a bit finicky with names (e.g. x86
#     having different revisions such as i386, i486 etc).
# If BML_TESTBENCH_ARCH is not explicitly defined, it defaults to CMAKE_SYSTEM_PROCESSOR.
set(BML_TESTBENCH_ARCH "${CMAKE_SYSTEM_PROCESSOR}" CACHE STRING
    "Architecture for which the BML testbench should target. Defaults to CMAKE_SYSTEM_PROCESSOR.")
mark_as_advanced(BML_TESTBENCH_ARCH)

target_sources(bml_testbench PRIVATE
    "src/platform/${CMAKE_CXX_COMPILER_ID}-${CMAKE_SYSTEM_NAME}-${BML_TESTBENCH_ARCH}.cpp")

# Configure the current compiler to disable - as much as possible - C++ features listed as eschewed
# in README.md.
include("cmake/${CMAKE_CXX_COMPILER_ID}BuildSettings.cmake")

# Bring in tests.
add_subdirectory(tests)
