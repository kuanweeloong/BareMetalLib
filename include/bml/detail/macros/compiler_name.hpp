//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
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
