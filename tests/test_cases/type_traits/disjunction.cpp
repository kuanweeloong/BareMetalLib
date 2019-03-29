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
#include <bml/type_traits/disjunction.hpp>

template <typename ExpectedBase, typename... Bs>
auto check_true() noexcept -> void
{
    static_assert(bml::disjunction<Bs...>::value);
    static_assert(bml::disjunction_v<Bs...>);
    
    using Result = bml::disjunction<Bs...>;
    static_assert(bml::is_base_of_v<ExpectedBase, Result>);
}

template <typename ExpectedBase, typename... Bs>
auto check_false() noexcept -> void
{
    static_assert(!bml::disjunction<Bs...>::value);
    static_assert(!bml::disjunction_v<Bs...>);
    
    using Result = bml::disjunction<Bs...>;
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
    // Check that the result is false and is a base of false_type when there are no arguments.
    {
        check_false<bml::false_type>();
    }
    
    // Check that the result is false and is a base of the last argument when all of the arguments
    // are "false-y" (i.e. has a static "value" member that yields false when cast to a bool).
    {
        // 1 arg
        check_false<bml::false_type, bml::false_type>();
        check_false<falsey, falsey>();
        
        // 2 args
        check_false<bml::false_type, bml::false_type, bml::false_type>();
        check_false<falsey, falsey, falsey>();
        check_false<falsey, bml::false_type, falsey>();
        check_false<bml::false_type, falsey, bml::false_type>();
        
        // 3 args
        check_false<bml::false_type, bml::false_type, bml::false_type, bml::false_type>();
        check_false<falsey, falsey, falsey, falsey>();
        check_false<bml::false_type, falsey, falsey, bml::false_type>();
        check_false<falsey, bml::false_type, bml::false_type, falsey>();
        
        // 4 args
        check_false<falsey, bml::false_type, bml::false_type, bml::false_type, falsey>();
        check_false<bml::false_type, falsey, falsey, falsey, bml::false_type>();
    }
    
    // Check that the result is true and is a base of the 1st "true-y" argument when at least one of
    // the arguments is "true-y" (i.e. has a static "value" member that yields false when cast to a
    // bool).
    {
        // 1 arg
        check_true<bml::true_type, bml::true_type>();
        check_true<truey, truey>();
        
        // 2 args
        check_true<bml::true_type, bml::true_type, bml::true_type>();
        check_true<bml::true_type, bml::true_type, truey>();
        check_true<truey, truey, bml::true_type>();
        
        check_true<bml::true_type, bml::true_type, bml::false_type>();
        check_true<bml::true_type, bml::false_type, bml::true_type>();
        check_true<truey, bml::false_type, truey>();
        check_true<truey, truey, bml::false_type>();
        
        // 3 args
        check_true<bml::true_type, bml::true_type, bml::true_type, bml::true_type>();
        check_true<truey, truey, truey, truey>();
        check_true<bml::true_type, bml::true_type, truey, truey>();
        check_true<truey, truey, bml::true_type, bml::true_type>();
        
        check_true<bml::true_type, bml::true_type, bml::false_type, bml::false_type>();
        check_true<bml::true_type, bml::true_type, bml::false_type, truey>();
        check_true<truey, truey, falsey, falsey>();
        check_true<truey, bml::false_type, truey, bml::true_type>();
        check_true<truey, truey, falsey, bml::true_type>();
        
        // 4 args
        check_true<bml::true_type, bml::true_type, truey, truey, truey>();
        check_true<bml::true_type, bml::false_type, falsey, bml::true_type, truey>();
        check_true<truey, bml::false_type, truey, falsey, truey>();
    }
    
    // Check that evaluation is short-circuited when disjunction encounters a true-y argument.
    {
        check_true<bml::true_type, bml::true_type, empty>();
        check_true<truey, bml::false_type, truey, empty>();
        check_true<bml::true_type, bml::false_type, bml::true_type, empty>();
        check_true<truey, bml::false_type, truey, empty, bml::true_type>();
    }
    
    return 0;
}
