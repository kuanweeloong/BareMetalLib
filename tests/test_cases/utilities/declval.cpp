//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/utilities/declval.hpp>
#include <bml/type_traits/is_same.hpp>

auto test_main() noexcept -> int
{
    // Check that declval yields a reference to the input type when the input is referenceable.
    {
        static_assert(bml::is_same_v<decltype(bml::declval<int>()), int&&>);
        static_assert(bml::is_same_v<decltype(bml::declval<int&>()), int&>);
        static_assert(bml::is_same_v<decltype(bml::declval<int&&>()), int&&>);
        
        static_assert(bml::is_same_v<decltype(bml::declval<int const>()), int const&&>);
        static_assert(bml::is_same_v<decltype(bml::declval<int volatile&>()), int volatile&>);
        static_assert(bml::is_same_v<decltype(bml::declval<int const volatile&&>()),
            int const volatile&&>);
        
        static_assert(bml::is_same_v<decltype(bml::declval<bmltb::class_type>()),
            bmltb::class_type&&>);
        static_assert(bml::is_same_v<decltype(bml::declval<bmltb::class_type&>()),
            bmltb::class_type&>);
        static_assert(bml::is_same_v<decltype(bml::declval<bmltb::class_type&&>()),
            bmltb::class_type&&>);
    }
    
    // Check that declval yields void when the input is (possibly cv-qualified) void.
    {
        static_assert(bml::is_same_v<decltype(bml::declval<void>()), void>);
        static_assert(bml::is_same_v<decltype(bml::declval<void const>()), void>);
        static_assert(bml::is_same_v<decltype(bml::declval<void volatile>()), void>);
        static_assert(bml::is_same_v<decltype(bml::declval<void const volatile>()), void>);
    }

    return 0;
}
