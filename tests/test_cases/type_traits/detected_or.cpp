//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/detected_or.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/type_traits/true_type.hpp>
#include <bml/type_traits/false_type.hpp>

template <typename T>
using foo_type = typename T::foo;

struct has_foo
{
    using foo = int;
};

struct no_foo {};

auto test_main() noexcept -> int
{
    // Check that value_ty aliases to true_type when detection succeeds.
    {
        static_assert(bml::is_same_v<bml::detected_or<char, foo_type, has_foo>::value_ty,
            bml::true_type>);
    }
    
    // Check that value_ty aliases to false_type when detection fails.
    {
        static_assert(bml::is_same_v<bml::detected_or<char, foo_type, no_foo>::value_ty,
            bml::false_type>);
    }
    
    // Check that type (the member type alias) aliases to type named by Op<Args...> when detection
    // succeeds.
    {
        static_assert(bml::is_same_v<bml::detected_or<char, foo_type, has_foo>::type,
            foo_type<has_foo>>);
        static_assert(bml::is_same_v<bml::detected_or_ty<char, foo_type, has_foo>,
            foo_type<has_foo>>);
    }
    
    // Check that type (the member type alias) aliases to Default when detection fails.
    {
        static_assert(bml::is_same_v<bml::detected_or<char, foo_type, no_foo>::type, char>);
        static_assert(bml::is_same_v<bml::detected_or_ty<char, foo_type, no_foo>, char>);
    }

    return 0;
}
