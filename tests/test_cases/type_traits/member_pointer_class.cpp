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
#include <bml/type_traits/member_pointer_class.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/type_traits/is_detected.hpp>

template <typename T, typename Expected>
auto check_result() noexcept -> void
{
    static_assert(bml::is_same_v<typename bml::member_pointer_class<T>::type, Expected>);
    static_assert(bml::is_same_v<bml::member_pointer_class_ty<T>, Expected>);
}

template <typename T>
using type_member_alias = typename T::type;

template <typename T>
using valid_member_pointer_class_ty = bml::member_pointer_class_ty<T>;

template <typename T>
auto check_no_alias() noexcept -> void
{
    static_assert(!bml::is_detected_v<type_member_alias, bml::member_pointer_class<T>>);
    static_assert(!bml::is_detected_v<valid_member_pointer_class_ty, T>);
}

struct c;

auto test_main() noexcept -> int
{
    // Check that the result names the class containing the member being pointed to by the input.
    // 
    {
        // Pointer to data members.
        using int_arr = int[3];
        using incomplete_int_arr = int[];
        
        check_result<void* c::*, c>();
        check_result<int c::*, c>();
        check_result<int const volatile c::*, c>();
        check_result<int const* c::*, c>();
        check_result<int const* const c::*, c>();
        check_result<int_arr c::*, c>();
        check_result<incomplete_int_arr c::*, c>();
        check_result<double const c::*, c>();
        
        check_result<bmltb::class_type c::*, c>();
        check_result<bmltb::union_type c::*, c>();
        check_result<bmltb::incomplete_class c::*, c>();
        
        // Pointer to member functions.
        check_result<auto (c::*)() -> int, c>();
        check_result<auto (c::*)() noexcept -> int, c>();
        check_result<auto (c::*)() const volatile & -> int, c>();
        check_result<auto (c::*)() const && noexcept -> int, c>();
    }
    
    // Check that there is no type member alias when the input is not a pointer to class member.
    {
        check_no_alias<int c::*[5]>();
        check_no_alias<int c::*[]>();
        
        check_no_alias<auto (c::*[2])() -> int>();
        check_no_alias<auto (c::*[])() -> int>();
        
        check_no_alias<void>();
        check_no_alias<void const>();
        check_no_alias<void volatile>();
        check_no_alias<void const volatile>();
        
        check_no_alias<int>();
        check_no_alias<int* const>();
        check_no_alias<int&>();
        check_no_alias<int const volatile&&>();
        check_no_alias<int[3]>();
        check_no_alias<int const[]>();
        
        check_no_alias<bmltb::class_type>();
        check_no_alias<bmltb::class_type*>();
        check_no_alias<bmltb::class_type const*>();
        check_no_alias<bmltb::class_type const&&>();
        check_no_alias<bmltb::class_type volatile[3]>();
        check_no_alias<bmltb::class_type const volatile[]>();
        
        check_no_alias<auto () -> int>();
        check_no_alias<auto (...) && -> int>();
        check_no_alias<auto (int, bmltb::class_type) && -> int>();
        
        check_no_alias<auto (*)() -> int>();
        check_no_alias<auto (&)() -> int>();
        check_no_alias<auto (&&)() -> int>();
    }
    
    return 0;
}
