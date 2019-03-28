//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <stddef.h>
#include <bml_testbench.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/utilities/index_sequence.hpp>

auto test_main() noexcept -> int
{
    // Check that the value_type member type alias names ptrdiff_t.
    {
        static_assert(bml::is_same_v<::ptrdiff_t, typename bml::index_sequence<>::value_type>);
        static_assert(bml::is_same_v<::ptrdiff_t,
            typename bml::index_sequence<1, 2, -10, 3, 5>::value_type>);
    }
    
    return 0;
}
