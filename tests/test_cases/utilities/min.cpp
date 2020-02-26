//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/utilities/min.hpp>

template <typename... Ts>
constexpr auto min_sizeof() noexcept
{
    return bml::min(sizeof(Ts)...);
}

template <typename... Ts>
constexpr auto min(Ts const&...) noexcept { return 100; }

auto test_main() noexcept -> int
{
    // Check that the value of min's result is equal to the value of the input argument when only
    // one argument is provided. 
    {
        auto x = 10;
        
        bmltb_assert(bml::min(x) == 10);
        bmltb_assert(bml::min(10) == 10);
        bmltb_assert(bml::min(-10) == -10);
        
        // Check constexpr context too.
        constexpr auto cx = 10;
        
        static_assert(bml::min(cx) == 10);
        static_assert(bml::min(10) == 10);
        static_assert(bml::min(-10) == -10);
    }
    
    // Check that min returns a reference to the input argument when only one argument is provided. 
    {
        auto x = 10;
        
        bmltb_assert(&bml::min(x) == &x);
    }
    
    // Check that the value of min's result is equal to the smallest value of all arguments when
    // more than one argument is provided. 
    {
        auto x = 10;
        auto y = -20;
        auto z = -30;
        
        // 2 arguments
        bmltb_assert(bml::min(x, y) == -20);
        bmltb_assert(bml::min(y, x) == -20);
        
        bmltb_assert(bml::min(x, -100) == -100);
        bmltb_assert(bml::min(-100, x) == -100);
        bmltb_assert(bml::min(50, x) == 10);
        bmltb_assert(bml::min(x, 50) == 10);
        bmltb_assert(bml::min(-10, x) == -10);
        bmltb_assert(bml::min(x, -10) == -10);
        
        bmltb_assert(bml::min(-100, y) == -100);
        bmltb_assert(bml::min(y, -100) == -100);
        
        bmltb_assert(bml::min(100, 200) == 100);
        bmltb_assert(bml::min(200, 100) == 100);
        
        bmltb_assert(bml::min(x, x) == 10);
        bmltb_assert(bml::min(y, y) == -20);
        bmltb_assert(bml::min(200, 200) == 200);
        
        // 3+ arguments
        bmltb_assert(bml::min(x, y, z) == -30);
        bmltb_assert(bml::min(y, x, z) == -30);
        bmltb_assert(bml::min(z, y, -100) == -100);
        bmltb_assert(bml::min(1, y, -100) == -100);
        bmltb_assert(bml::min(z, x, 100) == -30);
        
        bmltb_assert(bml::min(x, x, x) == 10);
        bmltb_assert(bml::min(x, x, y) == -20);
        bmltb_assert(bml::min(x, z, z) == -30);
        bmltb_assert(bml::min(x, x, -1) == -1);
        bmltb_assert(bml::min(x, -100, z) == -100);
        
        bmltb_assert(bml::min(x, y, z, -100) == -100);
        bmltb_assert(bml::min(y, -100, x, z) == -100);
        bmltb_assert(bml::min(z, y, -100, -200) == -200);
        bmltb_assert(bml::min(-1, y, -200, -100) == -200);
        
        bmltb_assert(bml::min(-500, y, 100, x, z, -500) == -500);
        
        // Check constexpr context too.
        constexpr auto cx = 10;
        constexpr auto cy = -20;
        constexpr auto cz = -30;
        
        // 2 arguments
        static_assert(bml::min(cx, cy) == -20);
        static_assert(bml::min(cy, cx) == -20);
        
        static_assert(bml::min(cx, -100) == -100);
        static_assert(bml::min(-100, cx) == -100);
        static_assert(bml::min(50, cx) == 10);
        static_assert(bml::min(cx, 50) == 10);
        static_assert(bml::min(-10, cx) == -10);
        static_assert(bml::min(cx, -10) == -10);
        
        static_assert(bml::min(-100, cy) == -100);
        static_assert(bml::min(cy, -100) == -100);
        
        static_assert(bml::min(100, 200) == 100);
        static_assert(bml::min(200, 100) == 100);
        
        static_assert(bml::min(cx, cx) == 10);
        static_assert(bml::min(cy, cy) == -20);
        static_assert(bml::min(200, 200) == 200);
        
        // 3+ arguments
        static_assert(bml::min(cx, cy, cz) == -30);
        static_assert(bml::min(cy, cx, cz) == -30);
        static_assert(bml::min(cz, cy, -100) == -100);
        static_assert(bml::min(1, cy, -100) == -100);
        static_assert(bml::min(cz, cx, 100) == -30);
        
        static_assert(bml::min(cx, cx, cx) == 10);
        static_assert(bml::min(cx, cx, cy) == -20);
        static_assert(bml::min(cx, cz, cz) == -30);
        static_assert(bml::min(cx, cx, -1) == -1);
        static_assert(bml::min(cx, -100, cz) == -100);
        
        static_assert(bml::min(cx, cy, cz, -100) == -100);
        static_assert(bml::min(cy, -100, cx, cz) == -100);
        static_assert(bml::min(cz, cy, -100, -200) == -200);
        static_assert(bml::min(-1, cy, -200, -100) == -200);
        
        static_assert(bml::min(-500, cy, 100, cx, cz, -500) == -500);
    }
    
    // Check that min returns a reference to the smallest of all the arguments when more than one
    // argument is provided.
    {
        auto w = 10;
        auto x = -10;
        auto y = -20;
        auto z = -30;
        
        // 2 arguments
        bmltb_assert(&bml::min(x, y) == &y);
        bmltb_assert(&bml::min(y, x) == &y);
        
        // 3+ arguments
        bmltb_assert(&bml::min(w, x, y) == &y);
        bmltb_assert(&bml::min(x, y, z) == &z);
        bmltb_assert(&bml::min(y, w, z) == &z);
        bmltb_assert(&bml::min(x, w, z) == &z);
        bmltb_assert(&bml::min(y, x, w) == &y);
        
        bmltb_assert(&bml::min(y, y, y) == &y);
        bmltb_assert(&bml::min(w, w, w) == &w);
        bmltb_assert(&bml::min(y, y, z) == &z);
        
        bmltb_assert(&bml::min(w, x, y, z) == &z);
        bmltb_assert(&bml::min(y, w, x, z) == &z);
        bmltb_assert(&bml::min(y, y, x, z) == &z);
        bmltb_assert(&bml::min(w, w, w, w) == &w);
        
        bmltb_assert(&bml::min(w, w, w, w, y, y, y, x) == &y);
    }
    
    // Check that min can be invoked with parameter packs that have at least 1 parameter.
    {
        static_assert(min_sizeof<char>() == 1);
        static_assert(min_sizeof<char[3], char[2], char[4]>() == 2);
    }
    
    // Check that the multiple-argument overload of min does not participate in overload resolution
    // when arguments are of different types.
    {
        using bml::min;
        using ::min;
        
        // Deduction failure. 
        static_assert(min(1, 0.5f) == 100);
        
        // SFINAE.
        static_assert(min(1, 1, 0.5f, 8u) == 100);
    }
    
    return 0;
}
