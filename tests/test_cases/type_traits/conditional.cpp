//
// Copyright (c) 2018 Wee Loong Kuan
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
