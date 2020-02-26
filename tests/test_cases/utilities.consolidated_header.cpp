//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/utilities.hpp>

constexpr auto global_i = 42;

constexpr auto func() noexcept -> int { return 1; }

auto test_main() noexcept -> int
{
    // Check that addressof is available.
    {
        static_assert(bml::addressof(global_i) == &global_i);
    }
    
    // Check that declval is available.
    {
        static_assert(sizeof(bml::declval<int>()) > 0);
    }
    
    // Check that forward is available.
    {
        static_assert([](auto&& i)
        {
            return bml::forward<decltype(i)>(i) == 42;
        }(42));
    }
    
    // Check that index_sequence is available.
    {
        static_assert(sizeof(bml::index_sequence<1, 5, 2>) > 0);
    }
    
    // Check that integer_sequence is available.
    {
        static_assert(sizeof(bml::integer_sequence<int, 1, 5, 2>) > 0);
    }
    
    // Check that invoke is available.
    {
        static_assert(bml::invoke(func) == 1);
    }
    
    // Check that launder is available.
    {
        static_assert(*bml::launder(&global_i) == 42);
    }
    
    // Check that make_index_sequence is available.
    {
        static_assert(sizeof(bml::make_index_sequence<5>) > 0);
    }
    
    // Check that make_integer_sequence is available.
    {
        static_assert(sizeof(bml::make_integer_sequence<int, 5>) > 0);
    }
    
    // Check that max is available.
    {
        static_assert(bml::max(2, 6, 1) == 6);
    }
    
    // Check that min is available.
    {
        static_assert(bml::min(2, 6, 1) == 1);
    }
    
    // Check that move is available.
    {
        auto i = 42;
        static_cast<void>(bml::move(i));
    }
    
    // Check that placement new is available.
    {
        alignas(alignof(int)) char storage[sizeof(int)];
        static_cast<void>(::new (&storage) int(42));
    }
    
    // Check that reference_wrapper is available.
    {
        static_assert(sizeof(bml::reference_wrapper<int>) > 0);
    }
    
    // Check that swap is available.
    {
        static_assert([]()
        {
            auto i = 42;
            auto j = 24;
            
            bml::swap(i, j);
            
            return true;
        }());
    }
    
    // Check that swap_ranges is available.
    {
        static_assert([]()
        {
            int a[] = { 1, 2, 3, 4, 5  };
            int b[] = { 6, 7, 8, 9, 10 };
            
            bml::swap_ranges(a, a + 3, b);
            
            return true;
        }());
    }
    
    return 0;
}
