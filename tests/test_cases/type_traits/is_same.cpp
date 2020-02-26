//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_same.hpp>

template <typename T>
auto check_same() noexcept -> void
{
    // Binary case - like std::is_same.
    static_assert(bml::is_same<T, T>::value);
    static_assert(bml::is_same_v<T, T>);
    
    // N-rary case - our own extension.
    static_assert(bml::is_same<T, T, T>::value);
    static_assert(bml::is_same_v<T, T, T>);
    
    static_assert(bml::is_same<T, T, T, T>::value);
    static_assert(bml::is_same_v<T, T, T, T>);
}

template <typename T, typename U>
auto check_different() noexcept -> void
{
    // Binary case - like std::is_same.
    static_assert(!bml::is_same<T, U>::value);
    static_assert(!bml::is_same_v<T, U>);

    static_assert(!bml::is_same<U, T>::value);
    static_assert(!bml::is_same_v<U, T>);
    
    // N-rary case - our own extension.
    static_assert(!bml::is_same<T, U, T>::value);
    static_assert(!bml::is_same_v<T, U, T>);
    
    static_assert(!bml::is_same<T, U, U>::value);
    static_assert(!bml::is_same_v<T, U, U>);

    static_assert(!bml::is_same<U, T, U>::value);
    static_assert(!bml::is_same_v<U, T, U>);
    
    static_assert(!bml::is_same<T, T, U>::value);
    static_assert(!bml::is_same_v<T, T, U>);
    
    static_assert(!bml::is_same<T, T, U, U>::value);
    static_assert(!bml::is_same_v<T, T, U, U>);
}

auto test_main() noexcept -> int
{
    // Check that value is true when inputs are the same type.
    {
        check_same<void>();
        check_same<void const>();
        check_same<int>();
        check_same<int*>();
        check_same<int&>();
        check_same<int&&>();
        check_same<int volatile* const>();
        check_same<bmltb::class_type>();
        check_same<int bmltb::class_type::*>();
        check_same<bmltb::class_type const>();
        check_same<bmltb::union_type[]>();
        check_same<bmltb::enum_class>();
        check_same<bmltb::incomplete_class>();
        check_same<bmltb::incomplete_class*[][2]>();
        check_same<auto (int) -> void>();
        check_same<auto (int) const && noexcept -> void>();
    }

    // Check that value is false when inputs are different types.
    {
        check_different<void, void const>();
        check_different<int const, int volatile>();
        check_different<bmltb::class_type, bmltb::class_type const>();
        check_different<int*, int* const>();

        check_different<int, void>();
        check_different<int, void const>();
        check_different<int, int&>();
        check_different<int&, int&&>();
        check_different<int[], int>();
        check_different<int volatile, int*>();
        check_different<int*, int&>();
        check_different<bmltb::class_type, int*>();
        check_different<bmltb::class_type const, bmltb::enum_class const>();
        check_different<bmltb::union_type, bmltb::class_type>();
        check_different<bmltb::incomplete_class, bmltb::class_type>();
        check_different<bmltb::incomplete_class, bmltb::incomplete_class const>();
        check_different<int bmltb::class_type::*, char bmltb::class_type::*>();
        check_different<void, auto (int) -> void>();

        check_different<auto (int) -> void, auto (int) -> int>();
        check_different<auto (int) -> void, auto (int) volatile && -> void>();
        check_different<auto () const && noexcept -> void, auto () volatile && noexcept -> void>();
        check_different<auto (int) -> void, auto (int, int) -> void>();
    }

    return 0;
}
