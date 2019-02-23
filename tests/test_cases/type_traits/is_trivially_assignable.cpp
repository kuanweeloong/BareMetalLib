//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_trivially_assignable.hpp>

template <typename... Ts>
auto check_trivially_assignable() noexcept -> void
{
    static_assert(bml::is_trivially_assignable<Ts...>::value);
    static_assert(bml::is_trivially_assignable_v<Ts...>);
}

template <typename... Ts>
auto check_not_trivially_assignable() noexcept -> void
{
    static_assert(!bml::is_trivially_assignable<Ts...>::value);
    static_assert(!bml::is_trivially_assignable_v<Ts...>);
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

struct default_assign
{
    auto operator=(default_assign const&) -> default_assign& = default;
    auto operator=(default_assign&&) -> default_assign& = default;
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the 2nd type is trivially assignable to the 1st type.
    {
        check_trivially_assignable<int&, int>();
        check_trivially_assignable<int&, int&>();
        check_trivially_assignable<int&, int const>();
        check_trivially_assignable<int&, int const&>();
        check_trivially_assignable<int&, double>();
        
        check_trivially_assignable<int volatile&, int>();
        check_trivially_assignable<int volatile&, int&>();
        check_trivially_assignable<int volatile&, int const volatile>();
        check_trivially_assignable<int volatile&, int const volatile&>();
        
        check_trivially_assignable<default_assign, default_assign const&>();
        check_trivially_assignable<default_assign, default_assign&&>();
        
        check_trivially_assignable<make_member<bmltb::incomplete_class>*&,
            make_member<bmltb::incomplete_class>*>();
    }
    
    // Check that the result is false when the 2nd type is not trivially assignable to the 1st type.
    {
        check_not_trivially_assignable<int, int&>();
        check_not_trivially_assignable<int, int>();
        
        check_not_trivially_assignable<to, from>();
        check_not_trivially_assignable<to&, from>();
        check_not_trivially_assignable<to&, from&>();
        
        check_not_trivially_assignable<to_cv, from>();
        check_not_trivially_assignable<to_cv&, from>();
        check_not_trivially_assignable<to_cv&, from&>();
        check_not_trivially_assignable<to_cv const, from>();
        check_not_trivially_assignable<to_cv const&, from>();
        check_not_trivially_assignable<to_cv const&, from&>();
        check_not_trivially_assignable<to_cv volatile, from>();
        check_not_trivially_assignable<to_cv volatile&, from>();
        check_not_trivially_assignable<to_cv volatile&, from&>();
        check_not_trivially_assignable<to_cv const volatile, from>();
        check_not_trivially_assignable<to_cv const volatile&, from>();
        check_not_trivially_assignable<to_cv const volatile&, from&>();
        
        check_not_trivially_assignable<to_lref&, from>();
        check_not_trivially_assignable<to_lref const volatile&, from>();
        check_not_trivially_assignable<to_lref const volatile&, from&>();
        
        check_not_trivially_assignable<to_overloaded_comma, int>();
    }
    
    // Check that the result is false when the 2nd type is not assignable to the 1st type.
    {
        check_not_trivially_assignable<void, void>();
        check_not_trivially_assignable<void, void const>();
        check_not_trivially_assignable<void volatile, void const>();
        check_not_trivially_assignable<void const, void volatile>();
        check_not_trivially_assignable<void const volatile, void const volatile>();
        
        check_not_trivially_assignable<int, int>();
        check_not_trivially_assignable<int, int&>();
        check_not_trivially_assignable<int const&, int>();
        check_not_trivially_assignable<int const volatile&, int>();
        
        check_not_trivially_assignable<from, to>();
        check_not_trivially_assignable<from&, to&>();
        check_not_trivially_assignable<from const volatile, to>();
        check_not_trivially_assignable<from const volatile&, to&>();
        
        check_not_trivially_assignable<to const, from>();
        check_not_trivially_assignable<to const&, from>();
        check_not_trivially_assignable<to const&, from&>();
        check_not_trivially_assignable<to volatile, from>();
        check_not_trivially_assignable<to volatile&, from>();
        check_not_trivially_assignable<to volatile&, from&>();
        check_not_trivially_assignable<to const volatile, from>();
        check_not_trivially_assignable<to const volatile&, from>();
        check_not_trivially_assignable<to const volatile&, from&>();
        
        check_not_trivially_assignable<to_lref, from>();
        check_not_trivially_assignable<to_lref const, from>();
        check_not_trivially_assignable<to_lref const volatile, from>();
        
        check_not_trivially_assignable<auto () -> int, int>();
    }
    
    return 0;
}
