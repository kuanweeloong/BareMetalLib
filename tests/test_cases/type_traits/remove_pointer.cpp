//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/remove_pointer.hpp>
#include <bml/type_traits/is_same.hpp>

template <typename T, typename U>
auto check_result() noexcept -> void
{
    static_assert(bml::is_same_v<typename bml::remove_pointer<T>::type, U>);
    static_assert(bml::is_same_v<bml::remove_pointer_ty<T>, U>);
}

auto test_main() noexcept -> int
{
    // Check that the result is the same as the input when the input is not a pointer.
    {
        check_result<void, void>();
        check_result<void const, void const>();
        check_result<void volatile, void volatile>();
        check_result<void const volatile, void const volatile>();
        
        check_result<void*&, void*&>();
        check_result<void**&, void**&>();
        check_result<void* const&, void* const&>();
        check_result<void*&&, void*&&>();
        
        check_result<int, int>();
        check_result<int[], int[]>();
        check_result<int(*&)[], int(*&)[]>();
        check_result<int const[3], int const[3]>();
        check_result<int const(&)[3], int const(&)[3]>();
        check_result<int&, int&>();
        check_result<int&&, int&&>();
        check_result<int volatile&&, int volatile&&>();
        
        check_result<bmltb::class_type, bmltb::class_type>();
        check_result<bmltb::enum_class, bmltb::enum_class>();
        check_result<bmltb::union_type const, bmltb::union_type const>();
        check_result<bmltb::incomplete_class, bmltb::incomplete_class>();
        check_result<int bmltb::class_type::*, int bmltb::class_type::*>();
        
        check_result<auto (int) -> void, auto (int) -> void>();
        check_result<auto (&)(int) -> void, auto (&)(int) -> void>();
        check_result<auto (*&&)(int) -> void, auto (*&&)(int) -> void>();
        check_result<auto (int, ...) noexcept -> void, auto (int, ...) noexcept -> void>();
        check_result<auto (&)(int, ...) noexcept -> void, auto (&)(int, ...) noexcept -> void>();
        check_result<auto (*&)(int, ...) noexcept -> void, auto (*&)(int, ...) noexcept -> void>();
        
        check_result<auto (bmltb::class_type::*)() -> void,
            auto (bmltb::class_type::*)() -> void>();
        check_result<auto (bmltb::class_type::*)() volatile && noexcept -> void,
            auto (bmltb::class_type::*)() volatile && noexcept -> void>();
        
        check_result<auto (int) const && -> void, auto (int) const && -> void>();
        check_result<auto () const && noexcept -> void, auto () const && noexcept -> void>();
    }
    
    // Check that the result is the same as the type being pointed to when the input is an
    // unqualified pointer type.
    {
        check_result<void*, void>();
        check_result<void const*, void const>();
        check_result<void volatile*, void volatile>();
        check_result<void const volatile*, void const volatile>();
        check_result<void**, void*>();
        check_result<void* const*, void* const>();
        
        check_result<int*, int>();
        check_result<int const**, int const*>();
        check_result<int(*)[], int[]>();
        check_result<int(**)[], int(*)[]>();
        check_result<int const(*)[3], int const[3]>();
        
        check_result<bmltb::class_type*, bmltb::class_type>();
        check_result<bmltb::enum_class*, bmltb::enum_class>();
        check_result<bmltb::union_type const*, bmltb::union_type const>();
        check_result<bmltb::incomplete_class*, bmltb::incomplete_class>();
        
        check_result<auto (*)(int) -> void, auto (int) -> void>();
        check_result<auto (*)(int, ...) noexcept -> void, auto (int, ...) noexcept -> void>();
    }

    // Check that the result is the same as the type being pointed to when the input is a const or
    // volatile qualified pointer type.
    {
        check_result<void* volatile, void>();
        check_result<void const* const, void const>();
        check_result<void volatile* const volatile, void volatile>();
        check_result<void const volatile* const, void const volatile>();
        check_result<void** const, void*>();
        check_result<void* const* volatile, void* const>();
        
        check_result<int* const, int>();
        check_result<int const** volatile, int const*>();
        check_result<int(* const)[], int[]>();
        check_result<int(** volatile)[], int(*)[]>();
        check_result<int const(* const volatile)[3], int const[3]>();
        
        check_result<bmltb::class_type* volatile, bmltb::class_type>();
        check_result<bmltb::enum_class* const, bmltb::enum_class>();
        check_result<bmltb::union_type const* const, bmltb::union_type const>();
        check_result<bmltb::incomplete_class* volatile, bmltb::incomplete_class>();
        
        check_result<auto (* const)(int) -> void, auto (int) -> void>();
        check_result<auto (* volatile)(int, ...) noexcept -> void, auto (int, ...) noexcept -> void>();
    }
    
    return 0;
}
