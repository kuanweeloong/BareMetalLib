//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/bool_constant.hpp>

auto test_main() noexcept -> int
{
    // Check that bool_constant contains a bool.
    {
        static_assert(bmltb::is_same<bml::bool_constant<true>::value_type, bool>::value);
        static_assert(bmltb::is_same<bml::bool_constant<false>::value_type, bool>::value);
    }

    // Check that bool_constant contains a true value when its template argument is true.
    {
        using true_constant = bml::bool_constant<true>;

        static_assert(true_constant::value);
        static_assert(true_constant());
    }

    // Check that bool_constant contains a false value when its template argument is false.
    {
        using false_constant = bml::bool_constant<false>;

        static_assert(!false_constant::value);
        static_assert(!false_constant());
    }

    return 0;
}
