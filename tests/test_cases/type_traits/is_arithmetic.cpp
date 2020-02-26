//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_arithmetic.hpp>

template <typename T>
auto check_arithmetic() noexcept -> void
{
    static_assert(bml::is_arithmetic<T>::value);
    static_assert(bml::is_arithmetic_v<T>);
    
    static_assert(bml::is_arithmetic<T const>::value);
    static_assert(bml::is_arithmetic_v<T const>);
    
    static_assert(bml::is_arithmetic<T volatile>::value);
    static_assert(bml::is_arithmetic_v<T volatile>);
    
    static_assert(bml::is_arithmetic<T const volatile>::value);
    static_assert(bml::is_arithmetic_v<T const volatile>);
}

template <typename T>
auto check_not_arithmetic() noexcept -> void
{
    static_assert(!bml::is_arithmetic<T>::value);
    static_assert(!bml::is_arithmetic_v<T>);
    
    static_assert(!bml::is_arithmetic<T const>::value);
    static_assert(!bml::is_arithmetic_v<T const>);
    
    static_assert(!bml::is_arithmetic<T volatile>::value);
    static_assert(!bml::is_arithmetic_v<T volatile>);
    
    static_assert(!bml::is_arithmetic<T const volatile>::value);
    static_assert(!bml::is_arithmetic_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is an arithmetic type.
    {
        check_arithmetic<bool>();
        check_arithmetic<char>();
        check_arithmetic<wchar_t>();
        check_arithmetic<char16_t>();
        check_arithmetic<char32_t>();
        check_arithmetic<signed char>();
        check_arithmetic<unsigned char>();
        check_arithmetic<short>();
        check_arithmetic<unsigned short>();
        check_arithmetic<int>();
        check_arithmetic<unsigned int>();
        check_arithmetic<long>();
        check_arithmetic<unsigned long>();
        check_arithmetic<long long>();
        check_arithmetic<unsigned long long>();
        
        check_arithmetic<float>();
        check_arithmetic<double>();
        check_arithmetic<long double>();
    }
    
    // Check that the result is false when the input is not an arithmetic type.
    {
        check_not_arithmetic<int*>();
        check_not_arithmetic<int&>();
        check_not_arithmetic<int const&>();
        check_not_arithmetic<int&&>();
        check_not_arithmetic<int volatile*>();
        check_not_arithmetic<int[]>();
        check_not_arithmetic<int[3]>();
        check_not_arithmetic<int(&)[]>();
        check_not_arithmetic<int[][2]>();
        
        check_not_arithmetic<float*>();
        check_not_arithmetic<float const*>();
        check_not_arithmetic<float&>();
        check_not_arithmetic<float const volatile&>();
        check_not_arithmetic<float&&>();
        check_not_arithmetic<float volatile&&>();
        check_not_arithmetic<float[]>();
        check_not_arithmetic<float[3]>();
        check_not_arithmetic<float(&)[]>();
        check_not_arithmetic<float[][2]>();
        
        check_not_arithmetic<void>();
        
        check_not_arithmetic<bmltb::class_type>();
        check_not_arithmetic<int bmltb::class_type::*>();
        check_not_arithmetic<bmltb::union_type[]>();
        check_not_arithmetic<bmltb::enum_class>();
        check_not_arithmetic<bmltb::incomplete_class>();
        check_not_arithmetic<bmltb::incomplete_class*[][2]>();
        
        check_not_arithmetic<auto (int) -> void>();
        check_not_arithmetic<auto (int) const && noexcept -> void>();
        check_not_arithmetic<auto (&)(int) -> void>();
        check_not_arithmetic<auto (*)(int) noexcept -> void>();
        check_not_arithmetic<auto (*&&)(int) noexcept -> void>();
        check_not_arithmetic<auto (bmltb::class_type::*)() -> void>();
        check_not_arithmetic<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }

    return 0;
}
