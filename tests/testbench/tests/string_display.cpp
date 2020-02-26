//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
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
