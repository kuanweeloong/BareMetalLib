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
#include <bml/type_traits/remove_reference.hpp>
#include <bml/type_traits/is_same.hpp>

template <typename T, typename U>
auto check_result() noexcept -> void
{
    static_assert(bml::is_same_v<typename bml::remove_reference<T>::type, U>);
    static_assert(bml::is_same_v<bml::remove_reference_ty<T>, U>);
}

auto test_main() noexcept -> int
{
    // Check that the result is the same as the input when the input is not a reference type.
    {
        check_result<void, void>();
        check_result<void const, void const>();
        check_result<void*, void*>();
        check_result<int, int>();
        check_result<int const[], int const[]>();
        check_result<int[3], int[3]>();
        check_result<int* const, int* const>();
        check_result<int volatile*, int volatile*>();
        
        check_result<bmltb::class_type const volatile, bmltb::class_type const volatile>();
        check_result<bmltb::enum_class, bmltb::enum_class>();
        check_result<bmltb::union_type, bmltb::union_type>();
        check_result<bmltb::union_type*, bmltb::union_type*>();
        check_result<bmltb::incomplete_class volatile, bmltb::incomplete_class volatile>();
        check_result<int bmltb::class_type::*, int bmltb::class_type::*>();
        
        check_result<auto (int) -> void, auto (int) -> void>();
        check_result<auto (int, ...) noexcept -> void, auto (int, ...) noexcept -> void>();
        
        check_result<auto (bmltb::class_type::*)() -> void,
            auto (bmltb::class_type::*)() -> void>();
        check_result<auto (bmltb::class_type::*)() volatile && noexcept -> void,
            auto (bmltb::class_type::*)() volatile && noexcept -> void>();
            
        check_result<auto (int) const && -> void, auto (int) const && -> void>();
        check_result<auto () const && noexcept -> void, auto () const && noexcept -> void>();
    }
    
    // Check that the result names the input's referred to type when the input is a lvalue
    // reference.
    {
        check_result<int&, int>();
        check_result<int const(&)[], int const[]>();
        check_result<int(&)[3], int[3]>();
        check_result<int* const&, int* const>();
        check_result<int volatile*&, int volatile*>();
        
        check_result<bmltb::class_type const volatile&, bmltb::class_type const volatile>();
        check_result<bmltb::enum_class&, bmltb::enum_class>();
        check_result<bmltb::union_type&, bmltb::union_type>();
        check_result<bmltb::union_type*&, bmltb::union_type*>();
        check_result<bmltb::incomplete_class volatile&, bmltb::incomplete_class volatile>();
        check_result<int bmltb::class_type::*&, int bmltb::class_type::*>();
        
        check_result<auto (&)(int) -> void, auto (int) -> void>();
        check_result<auto (&)(int, ...) noexcept -> void, auto (int, ...) noexcept -> void>();
        
        check_result<auto (bmltb::class_type::*&)() -> void,
            auto (bmltb::class_type::*)() -> void>();
        check_result<auto (bmltb::class_type::*&)() volatile && noexcept -> void,
            auto (bmltb::class_type::*)() volatile && noexcept -> void>();
    }

    // Check that the result names the input's referred to type when the input is a rvalue
    // reference.
    {
        check_result<int&&, int>();
        check_result<int const(&&)[], int const[]>();
        check_result<int(&&)[3], int[3]>();
        check_result<int* const&&, int* const>();
        check_result<int volatile*&&, int volatile*>();
        
        check_result<bmltb::class_type const volatile&&, bmltb::class_type const volatile>();
        check_result<bmltb::enum_class&&, bmltb::enum_class>();
        check_result<bmltb::union_type&&, bmltb::union_type>();
        check_result<bmltb::union_type*&&, bmltb::union_type*>();
        check_result<bmltb::incomplete_class volatile&&, bmltb::incomplete_class volatile>();
        check_result<int bmltb::class_type::*&&, int bmltb::class_type::*>();
        
        check_result<auto (&&)(int) -> void, auto (int) -> void>();
        check_result<auto (&&)(int, ...) noexcept -> void, auto (int, ...) noexcept -> void>();
        
        check_result<auto (bmltb::class_type::*&&)() -> void,
            auto (bmltb::class_type::*)() -> void>();
        check_result<auto (bmltb::class_type::*&&)() volatile && noexcept -> void,
            auto (bmltb::class_type::*)() volatile && noexcept -> void>();
    }
    
    return 0;
}
