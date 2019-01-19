//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
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
