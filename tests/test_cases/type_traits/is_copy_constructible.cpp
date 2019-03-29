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
#include <bml/type_traits/is_copy_constructible.hpp>

template <typename T>
auto check_copy_constructible() noexcept -> void
{
    static_assert(bml::is_copy_constructible<T>::value);
    static_assert(bml::is_copy_constructible_v<T>);
}

template <typename T>
auto check_not_copy_constructible() noexcept -> void
{
    static_assert(!bml::is_copy_constructible<T>::value);
    static_assert(!bml::is_copy_constructible_v<T>);
}

struct explicit_copy
{
    explicit_copy(explicit_copy const&);
};

struct explicit_move
{
    explicit_move(explicit_move&&);
};

struct bad_copy
{
    bad_copy(bad_copy&);
    auto operator=(bad_copy&) -> void;
};

class private_copy
{
    private_copy(private_copy const&);
};

struct no_copy
{
    no_copy(no_copy const&) = delete;
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

auto test_main() noexcept -> int
{
    // Check that the result is true when the input type is copy constructible.
    {
        check_copy_constructible<int>();
        check_copy_constructible<int const>();
        check_copy_constructible<int*>();
        check_copy_constructible<int const*>();
        check_copy_constructible<int&>();
        check_copy_constructible<int const&>();
        check_copy_constructible<double>();
        
        check_copy_constructible<explicit_copy>();
        check_copy_constructible<bmltb::class_type>();
        check_copy_constructible<bmltb::enum_class>();
        check_copy_constructible<bmltb::union_type>();
        check_copy_constructible<bmltb::incomplete_class*>();
        
        check_copy_constructible<int bmltb::class_type::*>();
        check_copy_constructible<int bmltb::incomplete_class::*>();
        check_copy_constructible<int abstract::*>();
        check_copy_constructible<int abstract_dtor::*>();
        
        check_copy_constructible<auto (*)() -> void>();
        check_copy_constructible<auto (*)() noexcept -> void>();
        check_copy_constructible<auto (&)() -> void>();
        check_copy_constructible<auto (&)() noexcept -> void>();
        
        check_copy_constructible<auto (bmltb::class_type::*)() -> void>();
        check_copy_constructible<auto (bmltb::class_type::*)() const && -> void>();
        check_copy_constructible<auto (bmltb::class_type::*&)() const volatile & -> void>();
    }
    
    // Check that the result is false when the input type is not copy constructible.
    {
        check_not_copy_constructible<void>();
        check_not_copy_constructible<void const>();
        check_not_copy_constructible<void volatile>();
        check_not_copy_constructible<void const volatile>();
        
        check_not_copy_constructible<char[]>();
        check_not_copy_constructible<char const[]>();
        check_not_copy_constructible<char[][3]>();
        check_not_copy_constructible<char const volatile[][3]>();
        
        check_not_copy_constructible<explicit_move>();
        check_not_copy_constructible<bad_copy>();
        check_not_copy_constructible<private_copy>();
        check_not_copy_constructible<no_copy>();
        check_not_copy_constructible<nested_no_copy>();
        check_not_copy_constructible<abstract>();
        check_not_copy_constructible<abstract_dtor>();
        
        check_not_copy_constructible<auto () -> void>();
        check_not_copy_constructible<auto () noexcept -> void>();
        check_not_copy_constructible<auto () const volatile & noexcept -> void>();
        check_not_copy_constructible<auto () const && noexcept -> void>();
    }
    
    return 0;
}
