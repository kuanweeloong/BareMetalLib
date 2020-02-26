//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/remove_cvref.hpp>
#include <bml/type_traits/is_same.hpp>

template <typename T, typename U>
auto check_result() noexcept -> void
{
    static_assert(bml::is_same_v<typename bml::remove_cvref<T>::type, U>);
    static_assert(bml::is_same_v<bml::remove_cvref_ty<T>, U>);
}

auto test_main() noexcept -> int
{
    // Check that the result is the same as the input when the input is an unqualified,
    // non-reference type.
    {
        check_result<void, void>();
        check_result<void*, void*>();
        check_result<int, int>();
        check_result<int[], int[]>();
        check_result<int[3], int[3]>();
        check_result<int*, int*>();
        check_result<int volatile*, int volatile*>();
        
        check_result<bmltb::class_type, bmltb::class_type>();
        check_result<bmltb::enum_class, bmltb::enum_class>();
        check_result<bmltb::union_type, bmltb::union_type>();
        check_result<bmltb::union_type*, bmltb::union_type*>();
        check_result<bmltb::incomplete_class, bmltb::incomplete_class>();
        check_result<int bmltb::class_type::*, int bmltb::class_type::*>();
        
        check_result<auto (int) -> void, auto (int) -> void>();
        check_result<auto (int, ...) noexcept -> void, auto (int, ...) noexcept -> void>();
        check_result<auto (*)(int) -> void, auto (*)(int) -> void>();
        check_result<auto (*)(int, ...) noexcept -> void, auto (*)(int, ...) noexcept -> void>();
        
        check_result<auto (bmltb::class_type::*)() -> void,
            auto (bmltb::class_type::*)() -> void>();
        check_result<auto (bmltb::class_type::*)() volatile && noexcept -> void,
            auto (bmltb::class_type::*)() volatile && noexcept -> void>();
            
        check_result<auto (int) const && -> void, auto (int) const && -> void>();
        check_result<auto () const && noexcept -> void, auto () const && noexcept -> void>();
    }
    
    // Check that the result names the input's referred to type when the input is a reference to an
    // unqualified type.
    {
        check_result<void*&, void*>();
        check_result<int&, int>();
        check_result<int&&, int>();
        check_result<int(&)[], int[]>();
        check_result<int(&)[3], int[3]>();
        check_result<int*&, int*>();
        check_result<int volatile*&&, int volatile*>();
        
        check_result<bmltb::class_type&, bmltb::class_type>();
        check_result<bmltb::enum_class&, bmltb::enum_class>();
        check_result<bmltb::union_type&&, bmltb::union_type>();
        check_result<bmltb::union_type const*&, bmltb::union_type const*>();
        check_result<bmltb::incomplete_class&, bmltb::incomplete_class>();
        check_result<int bmltb::class_type::*&, int bmltb::class_type::*>();
        
        check_result<auto (&)(int) -> void, auto (int) -> void>();
        check_result<auto (*&)(int) -> void, auto (*)(int) -> void>();
        check_result<auto (&&)(int, ...) noexcept -> void, auto (int, ...) noexcept -> void>();
        check_result<auto (*&&)(int, ...) noexcept -> void, auto (*)(int, ...) noexcept -> void>();
        
        check_result<auto (bmltb::class_type::*&)() -> void,
            auto (bmltb::class_type::*)() -> void>();
        check_result<auto (bmltb::class_type::*&&)() volatile && noexcept -> void,
            auto (bmltb::class_type::*)() volatile && noexcept -> void>();
    }

    // Check that the result names the unqualified version of the input when the input is a
    // const or volatile non-reference type.
    {
        check_result<void const volatile, void>();
        check_result<void* const, void*>();
        check_result<int volatile, int>();
        check_result<int const[], int[]>();
        check_result<int const volatile[3], int[3]>();
        check_result<int* const, int*>();
        check_result<int volatile* volatile, int volatile*>();
        
        check_result<bmltb::class_type const, bmltb::class_type>();
        check_result<bmltb::enum_class const volatile, bmltb::enum_class>();
        check_result<bmltb::union_type const, bmltb::union_type>();
        check_result<bmltb::union_type* volatile, bmltb::union_type*>();
        check_result<bmltb::incomplete_class volatile, bmltb::incomplete_class>();
        check_result<int bmltb::class_type::* const, int bmltb::class_type::*>();
        
        check_result<auto (* volatile)(int) -> void, auto (*)(int) -> void>();
        check_result<auto (* const) (int, ...) noexcept -> void,
            auto (*)(int, ...) noexcept -> void>();
        
        check_result<auto (bmltb::class_type::* const)() -> void,
            auto (bmltb::class_type::*)() -> void>();
        check_result<auto (bmltb::class_type::* const volatile)() volatile && noexcept -> void,
            auto (bmltb::class_type::*)() volatile && noexcept -> void>();
    }
    
    // Check that the result names the unqualified version of the input's referred to type when the
    // input is a reference to a const or volatile qualified type.
    {
        check_result<void* const&&, void*>();
        check_result<int volatile&, int>();
        check_result<int const(&)[], int[]>();
        check_result<int const volatile(&&)[3], int[3]>();
        check_result<int* const&, int*>();
        check_result<int volatile* volatile&, int volatile*>();
        
        check_result<bmltb::class_type const&&, bmltb::class_type>();
        check_result<bmltb::enum_class const volatile&, bmltb::enum_class>();
        check_result<bmltb::union_type const&, bmltb::union_type>();
        check_result<bmltb::union_type* volatile&, bmltb::union_type*>();
        check_result<bmltb::incomplete_class volatile&, bmltb::incomplete_class>();
        check_result<int bmltb::class_type::* const&&, int bmltb::class_type::*>();
        
        check_result<auto (* volatile&)(int) -> void, auto (*)(int) -> void>();
        check_result<auto (* const&&) (int, ...) noexcept -> void,
            auto (*)(int, ...) noexcept -> void>();
        
        check_result<auto (bmltb::class_type::* const&&)() -> void,
            auto (bmltb::class_type::*)() -> void>();
        check_result<auto (bmltb::class_type::* const volatile&)() volatile && noexcept -> void,
            auto (bmltb::class_type::*)() volatile && noexcept -> void>();
    }
    
    return 0;
}
