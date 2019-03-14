//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/true_type.hpp>
#include <bml/type_traits/false_type.hpp>
#include <bml/type_traits/negation.hpp>

template <typename B>
auto check_true() noexcept -> void
{
    static_assert(bml::negation<B>::value);
    static_assert(bml::negation_v<B>);
}

template <typename B>
auto check_false() noexcept -> void
{
    static_assert(!bml::negation<B>::value);
    static_assert(!bml::negation_v<B>);
}

struct truey
{
    static constexpr auto value = 100;
};

struct falsey
{
    static constexpr auto value = 0;
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is "false-y" (i.e. has a static "value" member
    // that yields false when cast to a bool).
    {
        check_true<bml::false_type>();
        check_true<falsey>();
        check_true<bml::negation<bml::true_type>>();
    }
    
    // Check that the result is false when the input is "true-y" (i.e. has a static "value" member
    // that yields true when cast to a bool).
    {
        check_false<bml::true_type>();
        check_false<truey>();
        check_false<bml::negation<bml::false_type>>();
    }
    
    return 0;
}
