//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_detected.hpp>
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
    // Check that is_detected is true when detection succeeds.
    {
        static_assert(bml::is_detected<foo_type, has_foo>::value);
        static_assert(bml::is_detected_v<foo_type, has_foo>);
    }
    
    // Check that is_detected is false when detection fails.
    {
        static_assert(!bml::is_detected<foo_type, no_foo>::value);
        static_assert(!bml::is_detected_v<foo_type, no_foo>);
    }

    return 0;
}
