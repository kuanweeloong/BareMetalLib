//
// Copyright (c) 2018 Wee Loong Kuan
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
#include <bml/type_traits/add_volatile.hpp>
#include <bml/type_traits/is_same.hpp>

template <typename T, typename U>
auto check_result() noexcept -> void
{
    static_assert(bml::is_same_v<typename bml::add_volatile<T>::type, U>);
    static_assert(bml::is_same_v<bml::add_volatile_ty<T>, U>);
}

auto test_main() noexcept -> int
{
    // Check that the result is the same as the volatile-qualified version of the input when the
    // input is unqualified.
    {
        check_result<void, void volatile>();
        check_result<int, int volatile>();
        check_result<int[3], int volatile[3]>();
        check_result<int*, int* volatile>();
        check_result<double const*, double const* volatile>();
        check_result<bmltb::class_type, bmltb::class_type volatile>();
        check_result<bmltb::enum_class, bmltb::enum_class volatile>();
        check_result<bmltb::union_type, bmltb::union_type volatile>();
        check_result<bmltb::incomplete_class, bmltb::incomplete_class volatile>();
        check_result<int bmltb::class_type::*, int bmltb::class_type::* volatile>();
    }

    // Check that the result is the same as the const-volatile-qualified version of the input when
    // the input is const-qualified.
    {
        check_result<void const, void const volatile>();
        check_result<int const, int const volatile>();
        check_result<int const[3], int const volatile[3]>();
        check_result<int* const, int* const volatile>();
        check_result<double const* const, double const* const volatile>();
        check_result<bmltb::class_type const, bmltb::class_type const volatile>();
        check_result<bmltb::enum_class const, bmltb::enum_class const volatile>();
        check_result<bmltb::union_type const, bmltb::union_type const volatile>();
        check_result<bmltb::incomplete_class const, bmltb::incomplete_class const volatile>();
        check_result<int bmltb::class_type::* const, int bmltb::class_type::* const volatile>();
    }

    // Check that the result is the same as the input when the input is volatile-qualified.
    {
        check_result<void volatile, void volatile>();
        check_result<int volatile, int volatile>();
        check_result<int volatile[3], int volatile[3]>();
        check_result<int* volatile, int* volatile>();
        check_result<double const* volatile, double const* volatile>();
        check_result<bmltb::class_type volatile, bmltb::class_type volatile>();
        check_result<bmltb::enum_class volatile, bmltb::enum_class volatile>();
        check_result<bmltb::union_type volatile, bmltb::union_type volatile>();
        check_result<bmltb::incomplete_class volatile, bmltb::incomplete_class volatile>();
        check_result<int bmltb::class_type::* volatile, int bmltb::class_type::* volatile>();
    }

    // Check that the result is the same as the input when the input is const-volatile-qualified.
    {
        check_result<void const volatile, void const volatile>();
        check_result<int const volatile, int const volatile>();
        check_result<int const volatile[3], int const volatile[3]>();
        check_result<int* const volatile, int* const volatile>();
        check_result<double const* const volatile, double const* const volatile>();
        check_result<bmltb::class_type const volatile, bmltb::class_type const volatile>();
        check_result<bmltb::enum_class const volatile, bmltb::enum_class const volatile>();
        check_result<bmltb::union_type const volatile, bmltb::union_type const volatile>();
        check_result<bmltb::incomplete_class const volatile,
            bmltb::incomplete_class const volatile>();
        check_result<int bmltb::class_type::* const volatile,
            int bmltb::class_type::* const volatile>();
    }

    // Check that the result is the same as the input when the input cannot be volatile-qualified.
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
