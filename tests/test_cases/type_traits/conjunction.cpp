//
// Copyright (c) 2019 Wee Loong Kuan
//
// BareMetalLib is based on libc++ (https://libcxx.llvm.org/).
// 
// This file is licensed under under the Apache License v2.0 with LLVM Exceptions. For more details,
// see the LICENSE.md file in the top-level directory of this distribution, or copy at 
// https://llvm.org/LICENSE.txt.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/true_type.hpp>
#include <bml/type_traits/false_type.hpp>
#include <bml/type_traits/is_base_of.hpp>
#include <bml/type_traits/conjunction.hpp>

template <typename ExpectedBase, typename... Bs>
auto check_true() noexcept -> void
{
    static_assert(bml::conjunction<Bs...>::value);
    static_assert(bml::conjunction_v<Bs...>);
    
    using Result = bml::conjunction<Bs...>;
    static_assert(bml::is_base_of_v<ExpectedBase, Result>);
}

template <typename ExpectedBase, typename... Bs>
auto check_false() noexcept -> void
{
    static_assert(!bml::conjunction<Bs...>::value);
    static_assert(!bml::conjunction_v<Bs...>);
    
    using Result = bml::conjunction<Bs...>;
    static_assert(bml::is_base_of_v<ExpectedBase, Result>);
}

struct empty {};

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
    // Check that the result is true and is a base of true_type when there are no arguments.
    {
        check_true<bml::true_type>();
    }
    
    // Check that the result is true and is a base of the last argument when all of the arguments
    // are "true-y" (i.e. has a static "value" member that yields true when cast to a bool).
    {
        // 1 arg
        check_true<bml::true_type, bml::true_type>();
        check_true<truey, truey>();
        
        // 2 args
        check_true<bml::true_type, bml::true_type, bml::true_type>();
        check_true<truey, truey, truey>();
        check_true<truey, bml::true_type, truey>();
        check_true<bml::true_type, truey, bml::true_type>();
        
        // 3 args
        check_true<bml::true_type, bml::true_type, bml::true_type, bml::true_type>();
        check_true<truey, truey, truey, truey>();
        check_true<bml::true_type, truey, truey, bml::true_type>();
        check_true<truey, bml::true_type, bml::true_type, truey>();
        
        // 4 args
        check_true<truey, bml::true_type, bml::true_type, bml::true_type, truey>();
        check_true<bml::true_type, truey, truey, truey, bml::true_type>();
    }
    
    // Check that the result is false and is a base of the 1st "false-y" argument when at least one
    // of the arguments is "false-y" (i.e. has a static "value" member that yields false when cast
    // to a bool).
    {
        // 1 arg
        check_false<bml::false_type, bml::false_type>();
        check_false<falsey, falsey>();
        
        // 2 args
        check_false<bml::false_type, bml::false_type, bml::false_type>();
        check_false<bml::false_type, bml::false_type, falsey>();
        check_false<falsey, falsey, bml::false_type>();
        
        check_false<bml::false_type, bml::true_type, bml::false_type>();
        check_false<bml::false_type, bml::false_type, bml::true_type>();
        check_false<falsey, bml::true_type, falsey>();
        check_false<falsey, falsey, bml::true_type>();
        
        // 3 args
        check_false<bml::false_type, bml::false_type, bml::false_type, bml::false_type>();
        check_false<falsey, falsey, falsey, falsey>();
        check_false<bml::false_type, bml::false_type, falsey, falsey>();
        check_false<falsey, falsey, bml::false_type, bml::false_type>();
        
        check_false<bml::false_type, bml::false_type, bml::true_type, bml::true_type>();
        check_false<bml::false_type, bml::false_type, bml::true_type, falsey>();
        check_false<falsey, falsey, truey, truey>();
        check_false<falsey, bml::true_type, falsey, bml::false_type>();
        check_false<falsey, falsey, truey, bml::false_type>();
        
        // 4 args
        check_false<bml::false_type, bml::false_type, falsey, falsey, falsey>();
        check_false<bml::false_type, bml::true_type, truey, bml::false_type, falsey>();
        check_false<falsey, bml::true_type, falsey, truey, falsey>();
    }
    
    // Check that evaluation is short-circuited when conjunction encounters a false-y argument.
    {
        check_false<bml::false_type, bml::false_type, empty>();
        check_false<falsey, bml::true_type, falsey, empty>();
        check_false<bml::false_type, bml::true_type, bml::false_type, empty>();
        check_false<falsey, bml::true_type, falsey, empty, bml::false_type>();
    }
    
    return 0;
}
