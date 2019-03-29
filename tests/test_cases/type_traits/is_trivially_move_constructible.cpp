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
#include <bml/type_traits/is_trivially_move_constructible.hpp>

template <typename T>
auto check_trivially_move_constructible() noexcept -> void
{
    static_assert(bml::is_trivially_move_constructible<T>::value);
    static_assert(bml::is_trivially_move_constructible_v<T>);
}

template <typename T>
auto check_not_trivially_move_constructible() noexcept -> void
{
    static_assert(!bml::is_trivially_move_constructible<T>::value);
    static_assert(!bml::is_trivially_move_constructible_v<T>);
}

struct empty {};

union empty_union {};

struct explicit_copy
{
    explicit_copy(explicit_copy const&);
};

struct explicit_move
{
    explicit_move(explicit_move&&);
};

class private_copy
{
    private_copy(private_copy const&);
};

class private_move
{
    private_move(private_move&&);
};

struct no_copy
{
    no_copy(no_copy const&) = delete;
};

struct nested_no_copy
{
    no_copy n;
};

struct no_move
{
    no_move(no_move&&) = delete;
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

struct defaulted_move
{
    defaulted_move(defaulted_move&&) = default;
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input type is trivially move constructible.
    {
        check_trivially_move_constructible<int>();
        check_trivially_move_constructible<int const>();
        check_trivially_move_constructible<int*>();
        check_trivially_move_constructible<int const*>();
        check_trivially_move_constructible<int&>();
        check_trivially_move_constructible<int const&>();
        check_trivially_move_constructible<double>();
        
        check_trivially_move_constructible<empty>();
        check_trivially_move_constructible<empty_union>();
        check_trivially_move_constructible<defaulted_move>();
        check_trivially_move_constructible<bmltb::enum_class>();
        check_trivially_move_constructible<bmltb::incomplete_class*>();
        
        check_trivially_move_constructible<int bmltb::class_type::*>();
        check_trivially_move_constructible<int bmltb::incomplete_class::*>();
        check_trivially_move_constructible<int abstract::*>();
        check_trivially_move_constructible<int abstract_dtor::*>();
        
        check_trivially_move_constructible<auto (*)() -> void>();
        check_trivially_move_constructible<auto (*)() noexcept -> void>();
        check_trivially_move_constructible<auto (&)() -> void>();
        check_trivially_move_constructible<auto (&)() noexcept -> void>();
        
        check_trivially_move_constructible<auto (bmltb::class_type::*)() -> void>();
        check_trivially_move_constructible<auto (bmltb::class_type::*)() const && -> void>();
        check_trivially_move_constructible<
            auto (bmltb::class_type::*&)() const volatile & -> void>();
    }
    
    // Check that the result is false when the input type is not trivially move constructible.
    {
        check_not_trivially_move_constructible<explicit_copy>();
        check_not_trivially_move_constructible<explicit_move>();
    }
    
    // Check that the result is false when the input type is not move constructible.
    {
        check_not_trivially_move_constructible<void>();
        check_not_trivially_move_constructible<void const>();
        check_not_trivially_move_constructible<void volatile>();
        check_not_trivially_move_constructible<void const volatile>();
        
        check_not_trivially_move_constructible<char[]>();
        check_not_trivially_move_constructible<char const[]>();
        check_not_trivially_move_constructible<char[][3]>();
        check_not_trivially_move_constructible<char const volatile[][3]>();
        
        check_not_trivially_move_constructible<private_copy>();
        check_not_trivially_move_constructible<private_move>();
        check_not_trivially_move_constructible<no_copy>();
        check_not_trivially_move_constructible<nested_no_copy>();
        check_not_trivially_move_constructible<no_move>();
        check_not_trivially_move_constructible<nested_no_move>();
        check_not_trivially_move_constructible<abstract>();
        check_not_trivially_move_constructible<abstract_dtor>();
        
        check_not_trivially_move_constructible<auto () -> void>();
        check_not_trivially_move_constructible<auto () noexcept -> void>();
        check_not_trivially_move_constructible<auto () const volatile & noexcept -> void>();
        check_not_trivially_move_constructible<auto () const && noexcept -> void>();
    }
    
    return 0;
}
