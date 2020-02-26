//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
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
