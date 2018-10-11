//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>

auto check_assert_ret(bool condition) noexcept -> int
{
    bmltb_assert(condition);

    return 123;
}

auto test_main() noexcept -> int
{
    // Check that bmltb_assert does not affect the caller's return value if the assertion succeeds.
    {
        if (check_assert_ret(true) != 123)
        {
            return 1;
        }
    }

    // Check that bmltb_assert aborts the caller on assertion failure by making it return 1.
    {
        if (check_assert_ret(false) != 1)
        {
            return 1;
        }
    }

    // Check that BMLTB_LINE_NUM contains the stringified line number.
    {
        // There's probably a better way to do this...
        auto& line = BMLTB_LINE_NUM;
        static_assert(line[0] == '3' && line[1] == '8' && line[2] == '\0');

        auto& line2 = BMLTB_LINE_NUM;
        static_assert(line2[0] == '4' && line2[1] == '1' && line2[2] == '\0');
    }
    
    // Check that is_same is true when its inputs name the same type.
    {
        static_assert(bmltb::is_same<int, int>::value);
        static_assert(bmltb::is_same<double const, double const>::value);
        static_assert(bmltb::is_same<char[], char[]>::value);
        static_assert(bmltb::is_same<bmltb::union_type, bmltb::union_type>::value);
    }

    // Check that is_same is false when its inputs name different types.
    {
        static_assert(!bmltb::is_same<int, int*>::value);
        static_assert(!bmltb::is_same<char[], bmltb::incomplete_class[]>::value);
        static_assert(!bmltb::is_same<bmltb::union_type, bmltb::class_type>::value);
    }
    
    return 0;
}
