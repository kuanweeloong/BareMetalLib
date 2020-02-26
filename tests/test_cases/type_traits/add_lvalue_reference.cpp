//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/add_lvalue_reference.hpp>
#include <bml/type_traits/is_same.hpp>

template <typename T, typename U>
auto check_result() noexcept -> void
{
    static_assert(bml::is_same_v<typename bml::add_lvalue_reference<T>::type, U>);
    static_assert(bml::is_same_v<bml::add_lvalue_reference_ty<T>, U>);
}

auto test_main() noexcept -> int
{
    // Check that the result names a lvalue reference to the input type when the input type is
    // referenceable.
    {
        check_result<int, int&>();
        check_result<int const, int const&>();
        check_result<int[3], int(&)[3]>();
        check_result<int volatile[3], int volatile(&)[3]>();
        check_result<int*, int*&>();
        check_result<int const volatile*, int const volatile*&>();
        
        check_result<int&, int&>();
        check_result<int const volatile&, int const volatile&>();
        check_result<int&&, int&>();
        
        check_result<bmltb::class_type, bmltb::class_type&>();
        check_result<bmltb::enum_class, bmltb::enum_class&>();
        check_result<bmltb::union_type, bmltb::union_type&>();
        check_result<bmltb::incomplete_class, bmltb::incomplete_class&>();
        check_result<int bmltb::class_type::*, int bmltb::class_type::*&>();
        
        check_result<auto () -> void, auto (&)() -> void>();
        check_result<auto (int) noexcept -> void, auto (&)(int) noexcept -> void>();
        
        check_result<auto (bmltb::class_type::*)() -> void,
            auto (bmltb::class_type::*&)() -> void>();
        check_result<auto (bmltb::class_type::*)() & -> void,
            auto (bmltb::class_type::*&)() & -> void>();
        check_result<auto (bmltb::class_type::*)() && noexcept -> void,
            auto (bmltb::class_type::*&)() && noexcept -> void>();
        check_result<auto (bmltb::class_type::*)() const & -> void,
            auto (bmltb::class_type::*&)() const & -> void>();
        check_result<auto (bmltb::class_type::*)() volatile && noexcept -> void,
            auto (bmltb::class_type::*&)() volatile && noexcept -> void>();
    }
    
    // Check that the result names the same type as the input type when the input type is
    // not referenceable.
    {
        check_result<void, void>();
        check_result<void const, void const>();
        check_result<void volatile, void volatile>();
        check_result<void const volatile, void const volatile>();
        
        check_result<auto () & -> void, auto () & -> void>();
        check_result<auto () & noexcept -> void, auto () & noexcept -> void>();
        check_result<auto () const & -> void, auto () const & -> void>();
        check_result<auto () && -> void, auto () && -> void>();
        check_result<auto () const && noexcept -> void, auto () const && noexcept -> void>();
    }
    
    return 0;
}
