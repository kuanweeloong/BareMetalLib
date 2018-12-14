//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
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
        auto const& test_string = BML_STRINGIZE(A_B);
        static_assert(test_string[0] == 'a');
        static_assert(test_string[1] == ' ');
        static_assert(test_string[2] == 'b');
        static_assert(test_string[3] == '\0');
    }
    
    // Check that stringize converts multiple arguments to a single string.
    {
        auto const& test_string = BML_STRINGIZE(A, B);
        static_assert(test_string[0] == 'a');
        static_assert(test_string[1] == ',');
        static_assert(test_string[2] == ' ');
        static_assert(test_string[3] == 'b');
        static_assert(test_string[4] == '\0');
    }
    
    return 0;
}
