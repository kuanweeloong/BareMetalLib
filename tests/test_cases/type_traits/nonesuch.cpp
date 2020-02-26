//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/nonesuch.hpp>
#include <bml/type_traits/is_default_constructible.hpp>
#include <bml/type_traits/is_copy_constructible.hpp>
#include <bml/type_traits/is_move_constructible.hpp>
#include <bml/type_traits/is_copy_assignable.hpp>
#include <bml/type_traits/is_move_assignable.hpp>

auto test_main() noexcept -> int
{
    // Check that nonesuch is not default constructible.
    {
        static_assert(!bml::is_default_constructible_v<bml::nonesuch>);
    }
    
    // Check that nonesuch is not copyable.
    {
        static_assert(!bml::is_copy_constructible_v<bml::nonesuch>);
        static_assert(!bml::is_copy_assignable_v<bml::nonesuch>);
    }
    
    // Check that nonesuch is not movable.
    {
        static_assert(!bml::is_move_constructible_v<bml::nonesuch>);
        static_assert(!bml::is_move_assignable_v<bml::nonesuch>);
    }
    
    return 0;
}
