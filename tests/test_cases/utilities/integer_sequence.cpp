//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
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
