//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/false_type.hpp>
#include <bml/type_traits/bool_constant.hpp>

auto test_main() noexcept -> int
{
    // Check that false_type is an alias for bool_constant<false>.
    {
        static_assert(bmltb::is_same<bml::false_type, bml::bool_constant<false>>::value);
    }

    // Check that non-truth is preserved after assignment.
    {
        bml::false_type f1;
        bml::false_type f2 = f1;

        bmltb_assert(!f2);
    }

    return 0;
}
