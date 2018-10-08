//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include <stddef.h>

namespace bmltb
{
    //
    // Displays an ASCII string on the screen. If ASCII display is not supported by the platform,
    // this has no side effects.
    // 
    // Note: This is implemented in platform-specific code.
    // 
    // Arguments:
    // buf - Buffer containing the string to display.
    // size - Size of the string, in bytes.
    //
    auto display_ascii(char const* buf, ::size_t size) noexcept -> void;
    
    //
    // Displays a null-terminated ASCII string and a trailing newline on the screen (like the real
    // puts). The terminating null is not displayed.
    //
    // Arguments:
    // str - The string to display.
    //
    template <::size_t N>
    auto puts(char const (& str)[N]) noexcept -> void
    {
        display_ascii(str, N - 1);
        display_ascii("\n", 1);
    }
    
    //
    // Helper macro to convert the current line number to a string.
    //
    #define BMLTB_LINE_NUM_1(n) #n
    #define BMLTB_LINE_NUM_0(n) BMLTB_LINE_NUM_1(n)
    #define BMLTB_LINE_NUM BMLTB_LINE_NUM_0(__LINE__)
    
    //
    // Macro to assert some condition at runtime. If the assert fails, display the failed condition
    // and abort the caller by making it return 1.
    //
    // Arguments:
    // condition - Condition to assert.
    //
    #define bmltb_assert(condition...)                                           \
        if (!(condition))                                                        \
        {                                                                        \
            bmltb::puts("Assert failed (line " BMLTB_LINE_NUM "): " #condition); \
            return 1;                                                            \
        }
}
