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
#include <bml/detail/macros/stringize.hpp>

#define A_B a b
#define A a
#define B b

auto test_main() noexcept -> int
{
    // Check that the contents of stringize's output matches the input.
    {
        constexpr auto& test_string = BML_STRINGIZE(A_B);
        static_assert(test_string[0] == 'a');
        static_assert(test_string[1] == ' ');
        static_assert(test_string[2] == 'b');
        static_assert(test_string[3] == '\0');
    }
    
    // Check that stringize converts multiple arguments to a single string.
    {
        constexpr auto& test_string = BML_STRINGIZE(A, B);
        static_assert(test_string[0] == 'a');
        static_assert(test_string[1] == ',');
        static_assert(test_string[2] == ' ');
        static_assert(test_string[3] == 'b');
        static_assert(test_string[4] == '\0');
    }
    
    return 0;
}
