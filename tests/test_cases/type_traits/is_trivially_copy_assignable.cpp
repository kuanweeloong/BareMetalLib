//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_trivially_copy_assignable.hpp>

template <typename T>
auto check_trivially_copy_assignable() noexcept -> void
{
    static_assert(bml::is_trivially_copy_assignable<T>::value);
    static_assert(bml::is_trivially_copy_assignable_v<T>);
}

template <typename T>
auto check_not_trivially_copy_assignable() noexcept -> void
{
    static_assert(!bml::is_trivially_copy_assignable<T>::value);
    static_assert(!bml::is_trivially_copy_assignable_v<T>);
}

struct empty {};

union empty_union {};

struct explicit_copy
{
    auto operator=(explicit_copy const&) -> explicit_copy&;
};

struct explicit_move
{
    auto operator=(explicit_move&&) -> explicit_move&;
};

struct move_ctor
{
    move_ctor(move_ctor&&);
};

struct bad_copy
{
    auto operator=(bad_copy&) -> void;
};

class private_copy
{
    auto operator=(private_copy const&) -> private_copy&;
};

struct no_copy
{
    auto operator=(no_copy const&) -> no_copy& = delete;
};

struct nested_no_copy
{
    no_copy n;
};

class abstract
{
    virtual auto foo() -> void = 0;
};

class abstract_dtor
{
    virtual ~abstract_dtor() = 0;
};

struct const_mem
{
    int const i;
};

struct ref_mem
{
    int& i;
};

struct defaulted_copy_assign
{
    auto operator=(defaulted_copy_assign const&) -> defaulted_copy_assign& = default;
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input type is trivially copy assignable.
    {
        check_trivially_copy_assignable<int>();
        check_trivially_copy_assignable<int&>();
        check_trivially_copy_assignable<int*>();
        check_trivially_copy_assignable<int const*>();
        check_trivially_copy_assignable<double>();
        
        check_trivially_copy_assignable<empty>();
        check_trivially_copy_assignable<empty_union>();
        check_trivially_copy_assignable<defaulted_copy_assign>();
        check_trivially_copy_assignable<bmltb::enum_class>();
        check_trivially_copy_assignable<bmltb::incomplete_class*>();
        
        check_trivially_copy_assignable<int bmltb::class_type::*>();
        check_trivially_copy_assignable<int bmltb::incomplete_class::*>();
        check_trivially_copy_assignable<int abstract::*>();
        check_trivially_copy_assignable<int abstract_dtor::*>();
        
        check_trivially_copy_assignable<auto (*)() -> void>();
        check_trivially_copy_assignable<auto (*)() noexcept -> void>();
        
        check_trivially_copy_assignable<auto (bmltb::class_type::*)() -> void>();
        check_trivially_copy_assignable<auto (bmltb::class_type::*)() const && -> void>();
        check_trivially_copy_assignable<auto (bmltb::class_type::*&)() const volatile & -> void>();
    }
    
    // Check that the result is false when the input type is not trivially copy assignable.
    {
        check_not_trivially_copy_assignable<explicit_copy>();
        check_not_trivially_copy_assignable<abstract>();
        check_not_trivially_copy_assignable<abstract_dtor>();
    }
    
    // Check that the result is false when the input type is not copy assignable.
    {
        check_not_trivially_copy_assignable<void>();
        check_not_trivially_copy_assignable<void const>();
        check_not_trivially_copy_assignable<void volatile>();
        check_not_trivially_copy_assignable<void const volatile>();
        
        check_not_trivially_copy_assignable<int const>();
        check_not_trivially_copy_assignable<int const&>();
        
        check_not_trivially_copy_assignable<char[]>();
        check_not_trivially_copy_assignable<char const[]>();
        check_not_trivially_copy_assignable<char[][3]>();
        check_not_trivially_copy_assignable<char const volatile[][3]>();
        
        check_not_trivially_copy_assignable<explicit_move>();
        check_not_trivially_copy_assignable<move_ctor>();
        check_not_trivially_copy_assignable<bad_copy>();
        check_not_trivially_copy_assignable<private_copy>();
        check_not_trivially_copy_assignable<no_copy>();
        check_not_trivially_copy_assignable<nested_no_copy>();
        check_not_trivially_copy_assignable<const_mem>();
        check_not_trivially_copy_assignable<ref_mem>();
        check_not_trivially_copy_assignable<empty const>();
        check_not_trivially_copy_assignable<empty_union const>();
        check_not_trivially_copy_assignable<defaulted_copy_assign const>();
        
        check_not_trivially_copy_assignable<auto (&)() -> void>();
        check_not_trivially_copy_assignable<auto (&)() noexcept -> void>();
        
        check_not_trivially_copy_assignable<auto () -> void>();
        check_not_trivially_copy_assignable<auto () noexcept -> void>();
        check_not_trivially_copy_assignable<auto () const volatile & noexcept -> void>();
        check_not_trivially_copy_assignable<auto () const && noexcept -> void>();
    }
    
    return 0;
}
