//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/conditional.hpp>
#include <bml/type_traits/is_same.hpp>

auto test_main() noexcept -> int
{
    // Check that the result is the first type when the condition is true.
    {
        static_assert(bml::is_same_v<bml::conditional<true, char, int>::type, char>);
        static_assert(bml::is_same_v<bml::conditional_ty<true, char, int>, char>);
    }

    // Check that the result is the second type when the condition is false.
    {
        static_assert(bml::is_same_v<bml::conditional<false, char, int>::type, int>);
        static_assert(bml::is_same_v<bml::conditional_ty<false, char, int>, int>);
    }

    return 0;
}
