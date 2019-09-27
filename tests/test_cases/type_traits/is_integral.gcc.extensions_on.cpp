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
    // META: Check that this test is only compiled with GNU extensions enabled.
    {
        #if defined(__STRICT_ANSI__)
            static_assert(false);
        #endif 
    }

    // Check that the result is true for __int128_t and __uint128_t when they're available, since
    // GNU extensions are enabled.
    {
        #if defined(__SIZEOF_INT128__)
            check_integral<__int128_t>();
            check_integral<__uint128_t>();
        #endif
    }

    return 0;
}
