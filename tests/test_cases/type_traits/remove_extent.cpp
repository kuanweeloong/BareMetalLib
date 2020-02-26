//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/remove_extent.hpp>
#include <bml/type_traits/is_same.hpp>

template <typename T, typename U>
auto check_result() noexcept -> void
{
    static_assert(bml::is_same_v<typename bml::remove_extent<T>::type, U>);
    static_assert(bml::is_same_v<bml::remove_extent_ty<T>, U>);
}

auto test_main() noexcept -> int
{
    // Check that the result names the underlying array type if the input is a 1D array.
    {
        check_result<int[3], int>();
        check_result<int[], int>();
        check_result<int const volatile[3], int const volatile>();
        check_result<int const volatile[], int const volatile>();
    }
    
    // Check that the result names the same type as the input, except with the 1st dimension
    // removed, if the input type is an array with 2 or more dimensions.
    {
        check_result<int[2][3], int[3]>();
        check_result<int[][3], int[3]>();
        check_result<int const volatile[2][3], int const volatile[3]>();
        check_result<int const volatile[][3], int const volatile[3]>();
        
        check_result<int[2][3][5], int[3][5]>();
        check_result<int[][3][5], int[3][5]>();
        check_result<int const volatile[2][3][5], int const volatile[3][5]>();
        check_result<int const volatile[][3][5], int const volatile[3][5]>();
    }
    
    // Check that the result names the same type as the input when the input type is not an array.
    {
        check_result<int(*)[3], int(*)[3]>();
        check_result<int(*)[], int(*)[]>();
        check_result<int(&)[3], int(&)[3]>();
        check_result<int(&)[], int(&)[]>();
        check_result<int(&)[3], int(&)[3]>();
        check_result<int(&&)[], int(&&)[]>();
        check_result<int(*)[][3], int(*)[][3]>();
        check_result<int(&)[][3], int(&)[][3]>();
        check_result<int(&&)[][3], int(&&)[][3]>();
        
        check_result<void, void>();
        check_result<void*, void*>();
        check_result<int, int>();
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
    
    return 0;
}
