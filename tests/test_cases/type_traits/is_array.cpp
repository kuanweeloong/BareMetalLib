//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_array.hpp>

template <typename T>
auto check_array() noexcept -> void
{
    static_assert(bml::is_array<T>::value);
    static_assert(bml::is_array_v<T>);
    
    static_assert(bml::is_array<T const>::value);
    static_assert(bml::is_array_v<T const>);
    
    static_assert(bml::is_array<T volatile>::value);
    static_assert(bml::is_array_v<T volatile>);
    
    static_assert(bml::is_array<T const volatile>::value);
    static_assert(bml::is_array_v<T const volatile>);
}

template <typename T>
auto check_not_array() noexcept -> void
{
    static_assert(!bml::is_array<T>::value);
    static_assert(!bml::is_array_v<T>);
    
    static_assert(!bml::is_array<T const>::value);
    static_assert(!bml::is_array_v<T const>);
    
    static_assert(!bml::is_array<T volatile>::value);
    static_assert(!bml::is_array_v<T volatile>);
    
    static_assert(!bml::is_array<T const volatile>::value);
    static_assert(!bml::is_array_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is an array type.
    {
        check_array<int[]>();
        check_array<int[3]>();
        check_array<int[][2]>();
        check_array<bmltb::union_type[]>();
        check_array<bmltb::incomplete_class*[][2]>();
    }
    
    // Check that the result is false when the input is not an array type.
    {
        check_not_array<int*>();
        check_not_array<int&>();
        check_not_array<int const&>();
        check_not_array<int&&>();
        check_not_array<int volatile*>();
        check_not_array<int(&)[]>();
        check_not_array<int(*)[]>();
        check_not_array<void>();
        check_not_array<float>();
        
        check_not_array<bmltb::class_type>();
        check_not_array<int bmltb::class_type::*>();
        check_not_array<bmltb::enum_class>();
        check_not_array<bmltb::incomplete_class>();
        
        check_not_array<auto (int) -> void>();
        check_not_array<auto (int) const && noexcept -> void>();
        check_not_array<auto (&)(int) -> void>();
        check_not_array<auto (*)(int) noexcept -> void>();
        check_not_array<auto (*&&)(int) noexcept -> void>();
        check_not_array<auto (bmltb::class_type::*)() -> void>();
        check_not_array<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }

    return 0;
}
