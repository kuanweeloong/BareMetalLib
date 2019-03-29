//
// Copyright (c) 2019 Wee Loong Kuan
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
#include <bml/utilities/swap_ranges.hpp>

struct user_swap
{
    constexpr user_swap() = default;
    
    user_swap(user_swap&&) = delete;
    auto operator=(user_swap&&) -> user_swap& = delete;
};

constexpr auto swap(user_swap&, user_swap&) noexcept -> void {}

auto test_main() noexcept -> int
{
    // Check that when the first two arguments span N items, exactly N items are swapped between the
    // first range and the second range, starting from the items referenced by first1 and last1.
    {
        // Swap entirety of both ranges.
        static_assert([]() constexpr
        {
            int a[] = { 1, 2, 3 };
            int b[] = { 4, 5, 6 };
            
            bml::swap_ranges(a, a + 3, b);
            
            return a[0] == 4 && a[1] == 5 && a[2] == 6
                && b[0] == 1 && b[1] == 2 && b[2] == 3;
        }());
        
        // Swap a portion of both ranges, starting from the beginning of both ranges.
        static_assert([]() constexpr
        {
            int a[] = { 1, 2, 3, 4, 5  };
            int b[] = { 6, 7, 8, 9, 10 };
            
            bml::swap_ranges(a, a + 3, b);
            
            return a[0] == 6 && a[1] == 7 && a[2] == 8 && a[3] == 4 && a[4] == 5
                && b[0] == 1 && b[1] == 2 && b[2] == 3 && b[3] == 9 && b[4] == 10;
        }());
        
        // Swap a portion of both ranges, starting from the middle of the first range and the
        // beginning of the second range.
        static_assert([]() constexpr
        {
            int a[] = { 1, 2, 3, 4, 5  };
            int b[] = { 6, 7, 8, 9, 10 };
            
            bml::swap_ranges(a + 1, a + 3, b);
            
            return a[0] == 1 && a[1] == 6 && a[2] == 7 && a[3] == 4 && a[4] == 5
                && b[0] == 2 && b[1] == 3 && b[2] == 8 && b[3] == 9 && b[4] == 10;
        }());
        
        // Swap a portion of both ranges, starting from the middle of both ranges.
        static_assert([]() constexpr
        {
            int a[] = { 1, 2, 3, 4, 5  };
            int b[] = { 6, 7, 8, 9, 10 };
            
            bml::swap_ranges(a + 1, a + 3, b + 2);
            
            return a[0] == 1 && a[1] == 8 && a[2] == 9 && a[3] == 4 && a[4] == 5
                && b[0] == 6 && b[1] == 7 && b[2] == 2 && b[3] == 3 && b[4] == 10;
        }());
    }
    
    // Check that user-defined swap functions are considered.
    {
        static_assert([]() constexpr
        {
            user_swap a[] = { {}, {}, {} };
            user_swap b[] = { {}, {}, {} };
            
            bml::swap_ranges(a, a + 2, b);
            
            return true;
        }());
    }
    
    return 0;
}
