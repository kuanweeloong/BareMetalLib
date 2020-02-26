//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_integral.hpp>

template <typename T>
auto check_integral() noexcept -> void
{
    static_assert(bml::is_integral<T>::value);
    static_assert(bml::is_integral_v<T>);
    
    static_assert(bml::is_integral<T const>::value);
    static_assert(bml::is_integral_v<T const>);
    
    static_assert(bml::is_integral<T volatile>::value);
    static_assert(bml::is_integral_v<T volatile>);
    
    static_assert(bml::is_integral<T const volatile>::value);
    static_assert(bml::is_integral_v<T const volatile>);
}

template <typename T>
auto check_not_integral() noexcept -> void
{
    static_assert(!bml::is_integral<T>::value);
    static_assert(!bml::is_integral_v<T>);
    
    static_assert(!bml::is_integral<T const>::value);
    static_assert(!bml::is_integral_v<T const>);
    
    static_assert(!bml::is_integral<T volatile>::value);
    static_assert(!bml::is_integral_v<T volatile>);
    
    static_assert(!bml::is_integral<T const volatile>::value);
    static_assert(!bml::is_integral_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true for __int128_t and __uint128_t when they're available.
    {
        #if defined(__SIZEOF_INT128__)
            check_integral<__int128_t>();
            check_integral<__uint128_t>();
        #endif
    }

    return 0;
}
