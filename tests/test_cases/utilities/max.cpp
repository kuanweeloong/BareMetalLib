//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/utilities/max.hpp>

template <typename... Ts>
constexpr auto max_sizeof() noexcept
{
    return bml::max(sizeof(Ts)...);
}

template <typename... Ts>
constexpr auto max(Ts const&...) noexcept { return 100; }

auto test_main() noexcept -> int
{
    // Check that the value of max's result is equal to the value of the input argument when only
    // one argument is provided. 
    {
        auto x = 10;
        
        bmltb_assert(bml::max(x) == 10);
        bmltb_assert(bml::max(10) == 10);
        bmltb_assert(bml::max(-10) == -10);
        
        // Check constexpr context too.
        constexpr auto cx = 10;
        
        static_assert(bml::max(cx) == 10);
        static_assert(bml::max(10) == 10);
        static_assert(bml::max(-10) == -10);
    }
    
    // Check that max returns a reference to the input argument when only one argument is provided. 
    {
        auto x = 10;
        
        bmltb_assert(&bml::max(x) == &x);
    }
    
    // Check that the value of max's result is equal to the largest value of all arguments when more
    // than one argument is provided. 
    {
        auto x = -10;
        auto y = 20;
        auto z = 30;
        
        // 2 arguments
        bmltb_assert(bml::max(x, y) == 20);
        bmltb_assert(bml::max(y, x) == 20);
        
        bmltb_assert(bml::max(x, 100) == 100);
        bmltb_assert(bml::max(100, x) == 100);
        bmltb_assert(bml::max(-50, x) == -10);
        bmltb_assert(bml::max(x, -50) == -10);
        bmltb_assert(bml::max(-1, x) == -1);
        bmltb_assert(bml::max(x, -1) == -1);
        
        bmltb_assert(bml::max(100, y) == 100);
        bmltb_assert(bml::max(y, 100) == 100);
        
        bmltb_assert(bml::max(100, 200) == 200);
        bmltb_assert(bml::max(200, 100) == 200);
        
        bmltb_assert(bml::max(x, x) == -10);
        bmltb_assert(bml::max(y, y) == 20);
        bmltb_assert(bml::max(200, 200) == 200);
        
        // 3+ arguments
        bmltb_assert(bml::max(x, y, z) == 30);
        bmltb_assert(bml::max(y, x, z) == 30);
        bmltb_assert(bml::max(z, y, 100) == 100);
        bmltb_assert(bml::max(1, y, 100) == 100);
        bmltb_assert(bml::max(z, x, -100) == 30);
        
        bmltb_assert(bml::max(x, x, x) == -10);
        bmltb_assert(bml::max(x, x, y) == 20);
        bmltb_assert(bml::max(x, z, z) == 30);
        bmltb_assert(bml::max(x, x, -1) == -1);
        bmltb_assert(bml::max(x, 100, z) == 100);
        
        bmltb_assert(bml::max(x, y, z, 100) == 100);
        bmltb_assert(bml::max(y, 100, x, z) == 100);
        bmltb_assert(bml::max(z, y, 100, 200) == 200);
        bmltb_assert(bml::max(1, y, 200, 100) == 200);
        
        bmltb_assert(bml::max(-500, y, 100, x, z, 500) == 500);
        
        // Check constexpr context too.
        constexpr auto cx = -10;
        constexpr auto cy = 20;
        constexpr auto cz = 30;
        
        // 2 arguments
        static_assert(bml::max(cx, cy) == 20);
        static_assert(bml::max(cy, cx) == 20);
        
        static_assert(bml::max(cx, 100) == 100);
        static_assert(bml::max(100, cx) == 100);
        static_assert(bml::max(-50, cx) == -10);
        static_assert(bml::max(cx, -50) == -10);
        static_assert(bml::max(-1, cx) == -1);
        static_assert(bml::max(cx, -1) == -1);
        
        static_assert(bml::max(100, cy) == 100);
        static_assert(bml::max(cy, 100) == 100);
        
        static_assert(bml::max(100, 200) == 200);
        static_assert(bml::max(200, 100) == 200);
        
        static_assert(bml::max(cx, cx) == -10);
        static_assert(bml::max(cy, cy) == 20);
        static_assert(bml::max(200, 200) == 200);
        
        // 3+ arguments
        static_assert(bml::max(cx, cy, cz) == 30);
        static_assert(bml::max(cy, cx, cz) == 30);
        static_assert(bml::max(cz, cy, 100) == 100);
        static_assert(bml::max(1, cy, 100) == 100);
        static_assert(bml::max(cz, cx, -1) == 30);
        
        static_assert(bml::max(cx, cx, cx) == -10);
        static_assert(bml::max(cx, cx, cy) == 20);
        static_assert(bml::max(cx, cz, cz) == 30);
        static_assert(bml::max(cx, cx, -1) == -1);
        static_assert(bml::max(cx, 100, cz) == 100);
        
        static_assert(bml::max(cx, cy, cz, 100) == 100);
        static_assert(bml::max(cy, 100, cx, cz) == 100);
        static_assert(bml::max(cz, cy, 100, 200) == 200);
        static_assert(bml::max(1, cy, 200, 100) == 200);
        
        static_assert(bml::max(-500, cy, 100, cx, cz, 500) == 500);
    }
    
    // Check that max returns a reference to the largest of all the arguments when more than one
    // argument is provided.
    {
        auto w = -10;
        auto x = 10;
        auto y = 20;
        auto z = 30;
        
        // 2 arguments
        bmltb_assert(&bml::max(x, y) == &y);
        bmltb_assert(&bml::max(y, x) == &y);
        
        // 3+ arguments
        bmltb_assert(&bml::max(w, x, y) == &y);
        bmltb_assert(&bml::max(x, y, z) == &z);
        bmltb_assert(&bml::max(y, w, z) == &z);
        bmltb_assert(&bml::max(x, w, z) == &z);
        bmltb_assert(&bml::max(y, x, w) == &y);
        
        bmltb_assert(&bml::max(y, y, y) == &y);
        bmltb_assert(&bml::max(w, w, w) == &w);
        bmltb_assert(&bml::max(y, y, z) == &z);
        
        bmltb_assert(&bml::max(w, x, y, z) == &z);
        bmltb_assert(&bml::max(y, w, x, z) == &z);
        bmltb_assert(&bml::max(y, y, x, z) == &z);
        bmltb_assert(&bml::max(w, w, w, w) == &w);
        
        bmltb_assert(&bml::max(w, w, w, w, y, y, y, x) == &y);
    }
    
    // Check that max can be invoked with parameter packs that have at least 1 parameter.
    {
        static_assert(max_sizeof<char>() == 1);
        static_assert(max_sizeof<char[3], char[2], char[4]>() == 4);
    }
    
    // Check that the multiple-argument overload of max does not participate in overload resolution
    // when arguments are of different types.
    {
        using bml::max;
        using ::max;
        
        // Deduction failure. 
        static_assert(max(1, 0.5f) == 100);
        
        // SFINAE.
        static_assert(max(1, 1, 0.5f, 8u) == 100);
    }
    
    return 0;
}
