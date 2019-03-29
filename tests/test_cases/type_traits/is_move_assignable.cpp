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
#include <bml/type_traits/is_move_assignable.hpp>

template <typename T>
auto check_move_assignable() noexcept -> void
{
    static_assert(bml::is_move_assignable<T>::value);
    static_assert(bml::is_move_assignable_v<T>);
}

template <typename T>
auto check_not_move_assignable() noexcept -> void
{
    static_assert(!bml::is_move_assignable<T>::value);
    static_assert(!bml::is_move_assignable_v<T>);
}

struct explicit_copy
{
    auto operator=(explicit_copy const&) -> explicit_copy&;
};

struct explicit_move
{
    auto operator=(explicit_move&&) -> explicit_move&;
};

struct copy_ctor
{
    copy_ctor(copy_ctor const&);
};

struct move_ctor
{
    move_ctor(move_ctor&&);
};

class private_move
{
    auto operator=(private_move&&) -> private_move&;
};

struct no_move
{
    auto operator=(no_move&&) -> no_move& = delete;
};

struct nested_no_move
{
    no_move n;
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

auto test_main() noexcept -> int
{
    // Check that the result is true when the input type is move assignable.
    {
        check_move_assignable<int>();
        check_move_assignable<int&>();
        check_move_assignable<int*>();
        check_move_assignable<int const*>();
        check_move_assignable<double>();
        
        check_move_assignable<explicit_copy>();
        check_move_assignable<explicit_move>();
        check_move_assignable<copy_ctor>();
        check_move_assignable<abstract>();
        check_move_assignable<abstract_dtor>();
        check_move_assignable<bmltb::class_type>();
        check_move_assignable<bmltb::enum_class>();
        check_move_assignable<bmltb::union_type>();
        check_move_assignable<bmltb::incomplete_class*>();
        
        check_move_assignable<int bmltb::class_type::*>();
        check_move_assignable<int bmltb::incomplete_class::*>();
        check_move_assignable<int abstract::*>();
        check_move_assignable<int abstract_dtor::*>();
        
        check_move_assignable<auto (*)() -> void>();
        check_move_assignable<auto (*)() noexcept -> void>();
        
        check_move_assignable<auto (bmltb::class_type::*)() -> void>();
        check_move_assignable<auto (bmltb::class_type::*)() const && -> void>();
        check_move_assignable<auto (bmltb::class_type::*&)() const volatile & -> void>();
    }
    
    // Check that the result is false when the input type is not move assignable.
    {
        check_not_move_assignable<void>();
        check_not_move_assignable<void const>();
        check_not_move_assignable<void volatile>();
        check_not_move_assignable<void const volatile>();
        
        check_not_move_assignable<int const>();
        check_not_move_assignable<int const&>();
        
        check_not_move_assignable<char[]>();
        check_not_move_assignable<char const[]>();
        check_not_move_assignable<char[][3]>();
        check_not_move_assignable<char const volatile[][3]>();
        
        check_not_move_assignable<move_ctor>();
        check_not_move_assignable<private_move>();
        check_not_move_assignable<no_move>();
        check_not_move_assignable<nested_no_move>();
        check_not_move_assignable<const_mem>();
        check_not_move_assignable<ref_mem>();
        
        check_not_move_assignable<auto (&)() -> void>();
        check_not_move_assignable<auto (&)() noexcept -> void>();
        
        check_not_move_assignable<auto () -> void>();
        check_not_move_assignable<auto () noexcept -> void>();
        check_not_move_assignable<auto () const volatile & noexcept -> void>();
        check_not_move_assignable<auto () const && noexcept -> void>();
    }
    
    return 0;
}
