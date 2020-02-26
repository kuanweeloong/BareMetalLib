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
#include <bml/utilities/integer_sequence.hpp>

auto test_main() noexcept -> int
{
    // Check that the value_type member type alias names the input type.
    {
        static_assert(bml::is_same_v<int, typename bml::integer_sequence<int>::value_type>);
        static_assert(bml::is_same_v<int,
            typename bml::integer_sequence<int, -1, 2, 10, 3, 5>::value_type>);
        
        static_assert(bml::is_same_v<unsigned long,
            typename bml::integer_sequence<unsigned long>::value_type>);
        static_assert(bml::is_same_v<unsigned long,
            typename bml::integer_sequence<unsigned long, 1, 2, 10, 3, 5>::value_type>);
    }
    
    // Check that size() returns the length of the sequence.
    {
        static_assert(bml::integer_sequence<int>::size() == 0);
        static_assert(bml::integer_sequence<int, -1, 2, 10, 3, 5>::size() == 5);
        
        static_assert(bml::integer_sequence<unsigned long>::size() == 0);
        static_assert(bml::integer_sequence<unsigned long, 10, 3, 5>::size() == 3);
    }

    return 0;
}
