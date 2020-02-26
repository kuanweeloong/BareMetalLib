//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/add_const.hpp>
#include <bml/type_traits/is_same.hpp>

template <typename T, typename U>
auto check_result() noexcept -> void
{
    static_assert(bml::is_same_v<typename bml::add_const<T>::type, U>);
    static_assert(bml::is_same_v<bml::add_const_ty<T>, U>);
}

auto test_main() noexcept -> int
{
    // Check that the result is the same as the const-qualified version of the input when the input
    // is unqualified.
    {
        check_result<void, void const>();
        check_result<int, int const>();
        check_result<int[3], int const[3]>();
        check_result<int*, int* const>();
        check_result<double volatile*, double volatile* const>();
        check_result<bmltb::class_type, bmltb::class_type const>();
        check_result<bmltb::enum_class, bmltb::enum_class const>();
        check_result<bmltb::union_type, bmltb::union_type const>();
        check_result<bmltb::incomplete_class, bmltb::incomplete_class const>();
        check_result<int bmltb::class_type::*, int bmltb::class_type::* const>();
    }
    
    // Check that the result is the same as the const-volatile-qualified version of the input when
    // the input is volatile-qualified.
    {
        check_result<void volatile, void const volatile>();
        check_result<int volatile, int const volatile>();
        check_result<int volatile[3], int const volatile[3]>();
        check_result<int* volatile, int* const volatile>();
        check_result<double volatile* volatile, double volatile* const volatile>();
        check_result<bmltb::class_type volatile, bmltb::class_type const volatile>();
        check_result<bmltb::enum_class volatile, bmltb::enum_class const volatile>();
        check_result<bmltb::union_type volatile, bmltb::union_type const volatile>();
        check_result<bmltb::incomplete_class volatile, bmltb::incomplete_class const volatile>();
        check_result<int bmltb::class_type::* volatile, int bmltb::class_type::* const volatile>();
    }

    // Check that the result is the same as the input when the input is const-qualified.
    {
        check_result<void const, void const>();
        check_result<int const, int const>();
        check_result<int const[3], int const[3]>();
        check_result<int* const, int* const>();
        check_result<double volatile* const, double volatile* const>();
        check_result<bmltb::class_type const, bmltb::class_type const>();
        check_result<bmltb::enum_class const, bmltb::enum_class const>();
        check_result<bmltb::union_type const, bmltb::union_type const>();
        check_result<bmltb::incomplete_class const, bmltb::incomplete_class const>();
        check_result<int bmltb::class_type::* const, int bmltb::class_type::* const>();
    }

    // Check that the result is the same as the input when the input is const-volatile-qualified.
    {
        check_result<void const volatile, void const volatile>();
        check_result<int const volatile, int const volatile>();
        check_result<int const volatile[3], int const volatile[3]>();
        check_result<int* const volatile, int* const volatile>();
        check_result<double volatile* const volatile, double volatile* const volatile>();
        check_result<bmltb::class_type const volatile, bmltb::class_type const volatile>();
        check_result<bmltb::enum_class const volatile, bmltb::enum_class const volatile>();
        check_result<bmltb::union_type const volatile, bmltb::union_type const volatile>();
        check_result<bmltb::incomplete_class const volatile,
            bmltb::incomplete_class const volatile>();
        check_result<int bmltb::class_type::* const volatile,
            int bmltb::class_type::* const volatile>();
    }

    // Check that the result is the same as the input when the input cannot be const-qualified.
    {
        check_result<int&, int&>();
        check_result<int&&, int&&>();
        check_result<auto (int) -> void, auto (int) -> void>();
        check_result<auto (int, ...) noexcept -> void, auto (int, ...) noexcept -> void>();
        check_result<auto (int) const && -> void, auto (int) const && -> void>();
        check_result<auto () const && noexcept -> void, auto () const && noexcept -> void>();
    }
    
    return 0;
}
