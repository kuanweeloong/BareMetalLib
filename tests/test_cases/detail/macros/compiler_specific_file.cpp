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

#include <bml_testbench.hpp>
#include <bml/detail/macros/compiler_specific_file.hpp>
#include BML_COMPILER_SPECIFIC_FILE(compiler, compiler_specific.hpp)

auto test_main() noexcept -> int
{
    // Check that compiler_specific.hpp was successfully included.
    {
        static_assert(BMLTB_COMPILER_SPECIFIC_FILE_INCLUDED);
    }
    
    return 0;
}
