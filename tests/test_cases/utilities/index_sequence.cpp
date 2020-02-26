//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
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
