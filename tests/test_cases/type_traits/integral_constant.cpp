//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/integral_constant.hpp>

auto test_main() noexcept -> int
{
    using five = bml::integral_constant<int, 5>;

    // Check that value_type member alias is equal to the template argument type.
    {
        static_assert(bmltb::is_same<five::value_type, int>::value);
    }

    // Check that type member alias is equal to the actual type.
    {
        static_assert(bmltb::is_same<five::type, five>::value);
    }

    // Check that value member is equal to template argument value.
    {
        static_assert(five::value == 5);
        static_assert(five()== 5);
        bmltb_assert(five() == 5);
        static_assert(five()() == 5);
    }
    
    return 0;
}
