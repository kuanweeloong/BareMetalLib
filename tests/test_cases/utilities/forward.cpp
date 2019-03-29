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
#include <bml/utilities/forward.hpp>
#include <bml/type_traits/is_same.hpp>

constexpr auto check_forward_constexpr_func() noexcept -> bool
{
    auto x = 42;
    auto const cx = 420;
    
    return bml::forward<int>(x) == 42
        && bml::forward<int&>(x) == 42
        && bml::forward<const int>(x) == 42
        && bml::forward<const int&>(x) == 42
        && bml::forward<const int>(cx) == 420
        && bml::forward<const int&>(cx) == 420;
}

struct arg {};

auto get_arg() noexcept -> arg { return arg(); };
auto get_arg_c() noexcept -> arg const { return arg(); };
auto get_arg_v() noexcept -> arg volatile { return arg(); };
auto get_arg_cv() noexcept -> arg const volatile { return arg(); };

auto test_main() noexcept -> int
{
    // Check that lvalues are forwarded as lvalues when T is a lvalue reference.
    {
        auto a = arg();
        auto const ca = arg();
        auto volatile va = arg();
        auto const volatile cva = arg();
        
        static_assert(bml::is_same_v<decltype(bml::forward<arg&>(a)), arg&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg const&>(a)), arg const&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg volatile&>(a)), arg volatile&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg const volatile&>(a)),
            arg const volatile&>);
        
        static_assert(bml::is_same_v<decltype(bml::forward<arg const&>(ca)), arg const&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg volatile&>(va)), arg volatile&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg const volatile&>(cva)),
            arg const volatile&>);
    }
    
    // Check that lvalues are forwarded as rvalues when T is not a reference.
    {
        auto a = arg();
        auto const ca = arg();
        auto volatile va = arg();
        auto const volatile cva = arg();
        
        static_assert(bml::is_same_v<decltype(bml::forward<arg>(a)), arg&&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg const>(a)), arg const&&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg volatile>(a)), arg volatile&&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg const volatile>(a)),
            arg const volatile&&>);
        
        static_assert(bml::is_same_v<decltype(bml::forward<arg const>(ca)), arg const&&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg volatile>(va)), arg volatile&&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg const volatile>(cva)),
            arg const volatile&&>);
    }
    
    // Check that rvalues are forwarded as rvalues when T is not a reference.
    {
        static_assert(bml::is_same_v<decltype(bml::forward<arg>(get_arg())), arg&&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg const>(get_arg())), arg const&&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg const>(get_arg())), arg const&&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg const>(get_arg())), arg const&&>);
        
        static_assert(bml::is_same_v<decltype(bml::forward<arg const>(get_arg_c())), arg const&&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg volatile>(get_arg_v())),
            arg volatile&&>);
        static_assert(bml::is_same_v<decltype(bml::forward<arg const volatile >(get_arg_cv())), arg
            const volatile&&>);
    }
    
    // Check that forward is usable in a constexpr context.
    {
       constexpr auto i = bml::forward<int>(42);
       
       static_assert(bml::forward<int>(42) == 42);
       static_assert(bml::forward<int const&>(i) == 42);
       static_assert(check_forward_constexpr_func());
    }

    return 0;
}
