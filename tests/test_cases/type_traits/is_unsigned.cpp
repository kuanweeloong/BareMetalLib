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
#include <bml/type_traits/is_unsigned.hpp>

template <typename T>
auto check_unsigned() noexcept -> void
{
    static_assert(bml::is_unsigned<T>::value);
    static_assert(bml::is_unsigned_v<T>);
    
    static_assert(bml::is_unsigned<T const>::value);
    static_assert(bml::is_unsigned_v<T const>);
    
    static_assert(bml::is_unsigned<T volatile>::value);
    static_assert(bml::is_unsigned_v<T volatile>);
    
    static_assert(bml::is_unsigned<T const volatile>::value);
    static_assert(bml::is_unsigned_v<T const volatile>);
}

template <typename T>
auto check_not_unsigned() noexcept -> void
{
    static_assert(!bml::is_unsigned<T>::value);
    static_assert(!bml::is_unsigned_v<T>);
    
    static_assert(!bml::is_unsigned<T const>::value);
    static_assert(!bml::is_unsigned_v<T const>);
    
    static_assert(!bml::is_unsigned<T volatile>::value);
    static_assert(!bml::is_unsigned_v<T volatile>);
    
    static_assert(!bml::is_unsigned<T const volatile>::value);
    static_assert(!bml::is_unsigned_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is an unsigned type. Note that types with
    // implementation-defined signed-ness are deliberately left out (e.g. char, wchar_t).
    {
        check_unsigned<unsigned char>();
        check_unsigned<unsigned short>();
        check_unsigned<unsigned int>();
        check_unsigned<unsigned long>();
        check_unsigned<unsigned long long>();
        
        check_unsigned<bool>();
        check_unsigned<char16_t>();
        check_unsigned<char32_t>();
    }
    
    // Check that the result is false when the input is not an unsigned type.
    {
        check_not_unsigned<signed char>();
        check_not_unsigned<short>();
        check_not_unsigned<int>();
        check_not_unsigned<long>();
        check_not_unsigned<long long>();
        
        check_not_unsigned<float>();
        check_not_unsigned<double>();
        check_not_unsigned<long double>();
        
        check_not_unsigned<int*>();
        check_not_unsigned<int&>();
        check_not_unsigned<int const&>();
        check_not_unsigned<int&&>();
        check_not_unsigned<int volatile*>();
        check_not_unsigned<int[]>();
        check_not_unsigned<int[3]>();
        check_not_unsigned<int(&)[]>();
        check_not_unsigned<int[][2]>();
        
        check_not_unsigned<float*>();
        check_not_unsigned<float const*>();
        check_not_unsigned<float&>();
        check_not_unsigned<float const volatile&>();
        check_not_unsigned<float&&>();
        check_not_unsigned<float volatile&&>();
        check_not_unsigned<float[]>();
        check_not_unsigned<float[3]>();
        check_not_unsigned<float(&)[]>();
        check_not_unsigned<float[][2]>();
        
        check_not_unsigned<void>();
        
        check_not_unsigned<bmltb::class_type>();
        check_not_unsigned<int bmltb::class_type::*>();
        check_not_unsigned<bmltb::union_type[]>();
        check_not_unsigned<bmltb::enum_class>();
        check_not_unsigned<bmltb::incomplete_class>();
        check_not_unsigned<bmltb::incomplete_class*[][2]>();
        
        check_not_unsigned<auto (int) -> void>();
        check_not_unsigned<auto (int) const && noexcept -> void>();
        check_not_unsigned<auto (&)(int) -> void>();
        check_not_unsigned<auto (*)(int) noexcept -> void>();
        check_not_unsigned<auto (*&&)(int) noexcept -> void>();
        check_not_unsigned<auto (bmltb::class_type::*)() -> void>();
        check_not_unsigned<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }

    return 0;
}
