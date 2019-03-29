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
#include <bml/type_traits/enable_if.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/type_traits/is_detected.hpp>
#include <bml/type_traits/false_type.hpp>

template <typename T>
using type_member_alias = typename T::type;

template <typename BoolConstant>
using valid_enable_if_ty = bml::enable_if_ty<BoolConstant::value, int>;

template <typename BoolConstant>
using valid_enable_if_ty_default_type = bml::enable_if_ty<BoolConstant::value>;

auto test_main() noexcept -> int
{
    // Check that the "type" member type alias is the same as the input type when the condition is
    // true.
    {
        static_assert(bml::is_same_v<typename bml::enable_if<true, int>::type, int>);
        static_assert(bml::is_same_v<bml::enable_if_ty<true, int>, int>);
        
        static_assert(bml::is_same_v<typename bml::enable_if<true, char[]>::type, char[]>);
        static_assert(bml::is_same_v<bml::enable_if_ty<true, char[]>, char[]>);
    }
    
    // Check that the "type" member type alias names void when the condition is true, but no input
    // type was specified.
    {
        static_assert(bml::is_same_v<typename bml::enable_if<true>::type, void>);
        static_assert(bml::is_same_v<bml::enable_if_ty<true>, void>);
    }
    
    // Check that there is no "type" member type alias when the condition is false.
    {
        static_assert(!bml::is_detected_v<type_member_alias, bml::enable_if<false, int>>);
        static_assert(!bml::is_detected_v<valid_enable_if_ty, bml::false_type>);
        
        static_assert(!bml::is_detected_v<type_member_alias, bml::enable_if<false>>);
        static_assert(!bml::is_detected_v<valid_enable_if_ty_default_type, bml::false_type>);
    }
    
    return 0;
}
