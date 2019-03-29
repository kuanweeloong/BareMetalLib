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

// Note that checks are done by CMake via the PASS_REGULAR_EXPRESSION test property.

auto test_main() noexcept -> int
{
    // Check that display_ascii displays the input ASCII string as-is.
    {
        constexpr auto const& message = "String from display_ascii.\n";
        
        // Don't display the null terminator!
        bmltb::display_ascii(message, sizeof(message) - 1);
    }
    
    // Check that puts appends a newline after the input string.
    {
        bmltb::puts("String from puts.");
    }
    
    return 0;
}
