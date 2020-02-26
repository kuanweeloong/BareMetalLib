//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/utilities/make_integer_sequence.hpp>

auto test_main() noexcept -> int
{
    // Check that the result is an integer_sequence of type T, with values starting from 0 and
    // ending at N-1.
    {
        static_assert(bml::is_same_v<bml::make_integer_sequence<int, 0>,
            bml::integer_sequence<int>>);
        static_assert(bml::is_same_v<bml::make_integer_sequence<int, 3>,
            bml::integer_sequence<int, 0, 1, 2>>);
        static_assert(bml::is_same_v<bml::make_integer_sequence<int, 5>,
            bml::integer_sequence<int, 0, 1, 2, 3, 4>>);
        
        static_assert(bml::is_same_v<bml::make_integer_sequence<unsigned long, 0>,
            bml::integer_sequence<unsigned long>>);
        static_assert(bml::is_same_v<bml::make_integer_sequence<unsigned long, 3>,
            bml::integer_sequence<unsigned long, 0, 1, 2>>);
        static_assert(bml::is_same_v<bml::make_integer_sequence<unsigned long, 5>,
            bml::integer_sequence<unsigned long, 0, 1, 2, 3, 4>>);
    }
    
    return 0;
}
