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

# BML's CMake scripts are based on the approaches outlined in Daniel Pfeifer's "Effective CMake"
# (https://www.youtube.com/watch?v=bsXLMQ6WgIk) and Pablo Arias' "It's Time To Do CMake Right"
# (https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/).

cmake_minimum_required(VERSION 3.10)
project(BareMetalLib VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Create the main BML target.
add_library(bml INTERFACE)
target_compile_features(bml INTERFACE cxx_std_17)
target_include_directories(bml INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

# Configure installers to copy BML's headers.
install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

# Perform incantations to transform BML into a config-file package.
install(TARGETS bml EXPORT bml_targets)
install(EXPORT bml_targets NAMESPACE BareMetalLib::
    FILE BareMetalLibTargets.cmake
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/BareMetalLib")

configure_package_config_file(cmake/BareMetalLibConfig.cmake.in BareMetalLibConfig.cmake
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/BareMetalLib")
write_basic_package_version_file(BareMetalLibConfigVersion.cmake
    VERSION ${BareMetalLib_VERSION} COMPATIBILITY ExactVersion)
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/BareMetalLibConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/BareMetalLibConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/BareMetalLib")

# Allow linking via BareMetalLib::bml when BML is a subproject.
add_library(BareMetalLib::bml ALIAS bml)

# Bring in tests if they're enabled.
option(BML_BUILD_TESTS "Build BareMetalLib tests.")
mark_as_advanced(BML_BUILD_TESTS)

if(BML_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
