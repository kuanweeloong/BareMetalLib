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
#include <bml/type_traits/is_assignable.hpp>

template <typename... Ts>
auto check_assignable() noexcept -> void
{
    static_assert(bml::is_assignable<Ts...>::value);
    static_assert(bml::is_assignable_v<Ts...>);
}

template <typename... Ts>
auto check_not_assignable() noexcept -> void
{
    static_assert(!bml::is_assignable<Ts...>::value);
    static_assert(!bml::is_assignable_v<Ts...>);
}

struct from {};

struct to
{
    auto operator=(from) noexcept -> void;
};

struct to_cv
{
    auto operator=(from) const volatile noexcept -> void;
};

struct to_lref
{
    auto operator=(from) const volatile & noexcept -> void;
};

struct overloaded_comma
{
    template <typename T> auto operator,(T&&) noexcept -> bmltb::incomplete_class;
};

struct to_overloaded_comma
{
    auto operator=(int) noexcept -> overloaded_comma;
};

template <typename T>
struct make_member { T t; };

auto test_main() noexcept -> int
{
    // Check that the result is true when the 2nd type is assignable to the 1st type.
    {
        check_assignable<int&, int>();
        check_assignable<int&, int&>();
        check_assignable<int&, int const>();
        check_assignable<int&, int const&>();
        check_assignable<int&, double>();
        
        check_assignable<int volatile&, int>();
        check_assignable<int volatile&, int&>();
        check_assignable<int volatile&, int const volatile>();
        check_assignable<int volatile&, int const volatile&>();
        
        check_assignable<to, from>();
        check_assignable<to&, from>();
        check_assignable<to&, from&>();
        
        check_assignable<to_cv, from>();
        check_assignable<to_cv&, from>();
        check_assignable<to_cv&, from&>();
        check_assignable<to_cv const, from>();
        check_assignable<to_cv const&, from>();
        check_assignable<to_cv const&, from&>();
        check_assignable<to_cv volatile, from>();
        check_assignable<to_cv volatile&, from>();
        check_assignable<to_cv volatile&, from&>();
        check_assignable<to_cv const volatile, from>();
        check_assignable<to_cv const volatile&, from>();
        check_assignable<to_cv const volatile&, from&>();
        
        check_assignable<to_lref&, from>();
        check_assignable<to_lref const volatile&, from>();
        check_assignable<to_lref const volatile&, from&>();
        
        check_assignable<to_overloaded_comma, int>();
        check_assignable<make_member<bmltb::incomplete_class>*&,
            make_member<bmltb::incomplete_class>*>();
    }
    
    // Check that the result is false when the 2nd type is not assignable to the 1st type.
    {
        check_not_assignable<void, void>();
        check_not_assignable<void, void const>();
        check_not_assignable<void volatile, void const>();
        check_not_assignable<void const, void volatile>();
        check_not_assignable<void const volatile, void const volatile>();
        
        check_not_assignable<int, int>();
        check_not_assignable<int, int&>();
        check_not_assignable<int const&, int>();
        check_not_assignable<int const volatile&, int>();
        
        check_not_assignable<from, to>();
        check_not_assignable<from&, to&>();
        check_not_assignable<from const volatile, to>();
        check_not_assignable<from const volatile&, to&>();
        
        check_not_assignable<to const, from>();
        check_not_assignable<to const&, from>();
        check_not_assignable<to const&, from&>();
        check_not_assignable<to volatile, from>();
        check_not_assignable<to volatile&, from>();
        check_not_assignable<to volatile&, from&>();
        check_not_assignable<to const volatile, from>();
        check_not_assignable<to const volatile&, from>();
        check_not_assignable<to const volatile&, from&>();
        
        check_not_assignable<to_lref, from>();
        check_not_assignable<to_lref const, from>();
        check_not_assignable<to_lref const volatile, from>();
        
        check_not_assignable<auto () -> int, int>();
    }
    
    return 0;
}
