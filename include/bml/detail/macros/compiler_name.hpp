//
// Copyright (c) 2018 Wee Loong Kuan
//
// BareMetalLib is based on libc++ (https://libcxx.llvm.org/).
// 
// This file is licensed under under the Apache License v2.0 with LLVM Exceptions. For more details,
// see the LICENSE.md file in the top-level directory of this distribution, or copy at 
// https://llvm.org/LICENSE.txt.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once

//
// Macro containing the compiler name.
//
// This macro is defined here instead of via the build system as BML aims to be usable without
// requiring modifications to a project's existing build scripts. However, the build system can
// choose to override this by explicitly defining BML_COMPILER_NAME.
//
#if !defined(BML_COMPILER_NAME)
    #if defined(__clang__)
        #define BML_COMPILER_NAME clang
    #elif defined(__GNUC__)
        #define BML_COMPILER_NAME gcc
    #else
        #define BML_COMPILER_NAME unknown_compiler
    #endif
#endif
