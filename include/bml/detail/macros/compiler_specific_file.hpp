//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "compiler_name.hpp"
#include "stringize.hpp"

// Macro for generating paths to compiler-specific files.
// 
// Generated paths point to files in <base_dir>/BML_COMPILER_NAME/, where BML_COMPILER_NAME is a
// macro containing the current compiler's name (see compiler_name.hpp). The main use case for this
// is to #include compiler-specific implementations - for instance, the following line:
//
//     #include BML_COMPILER_SPECIFIC_FILE(detail, implementation.hpp)
// 
// will include "detail/clang/implementation.hpp" when compiling with Clang, and
// "detail/gcc/implementation.hpp" when compiling with GCC.
//
// Arguments:
// base_dir - Path to the directory containing the desired file. This can be a relative path - in
//            such cases, the generated path will be relative to the file that invoked this macro.
//            This will be stringized, so it should not be enclosed in quotes.
// file - Name of the desired file. This will be stringized, so it should not be enclosed in quotes.
//
// Returns:
// Path to the desired file in the compiler-specific directory under base_dir.
#define BML_COMPILER_SPECIFIC_FILE(base_dir, file) \
    BML_STRINGIZE(base_dir/BML_COMPILER_NAME/file)
