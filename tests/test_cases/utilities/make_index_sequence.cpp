//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/utilities/make_index_sequence.hpp>

auto test_main() noexcept -> int
{
    // Check that the result is an index_sequence with values starting from 0 and ending at N-1.
    {
        static_assert(bml::is_same_v<bml::make_index_sequence<0>, bml::index_sequence<>>);
        static_assert(bml::is_same_v<bml::make_index_sequence<3>, bml::index_sequence<0, 1, 2>>);
        static_assert(bml::is_same_v<bml::make_index_sequence<5>,
            bml::index_sequence<0, 1, 2, 3, 4>>);
    }
    
    return 0;
}
