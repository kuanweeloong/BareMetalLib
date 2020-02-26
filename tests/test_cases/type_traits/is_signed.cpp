//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_signed.hpp>

template <typename T>
auto check_signed() noexcept -> void
{
    static_assert(bml::is_signed<T>::value);
    static_assert(bml::is_signed_v<T>);
    
    static_assert(bml::is_signed<T const>::value);
    static_assert(bml::is_signed_v<T const>);
    
    static_assert(bml::is_signed<T volatile>::value);
    static_assert(bml::is_signed_v<T volatile>);
    
    static_assert(bml::is_signed<T const volatile>::value);
    static_assert(bml::is_signed_v<T const volatile>);
}

template <typename T>
auto check_not_signed() noexcept -> void
{
    static_assert(!bml::is_signed<T>::value);
    static_assert(!bml::is_signed_v<T>);
    
    static_assert(!bml::is_signed<T const>::value);
    static_assert(!bml::is_signed_v<T const>);
    
    static_assert(!bml::is_signed<T volatile>::value);
    static_assert(!bml::is_signed_v<T volatile>);
    
    static_assert(!bml::is_signed<T const volatile>::value);
    static_assert(!bml::is_signed_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a signed type. Note that types with
    // implementation-defined signed-ness are deliberately left out (e.g. char, wchar_t).
    {
        check_signed<signed char>();
        check_signed<short>();
        check_signed<int>();
        check_signed<long>();
        check_signed<long long>();
        
        check_signed<float>();
        check_signed<double>();
        check_signed<long double>();
    }
    
    // Check that the result is false when the input is not a signed type.
    {
        check_not_signed<bool>();
        check_not_signed<char16_t>();
        check_not_signed<char32_t>();
        check_not_signed<unsigned char>();
        check_not_signed<unsigned short>();
        check_not_signed<unsigned int>();
        check_not_signed<unsigned long>();
        check_not_signed<unsigned long long>();
        
        check_not_signed<int*>();
        check_not_signed<int&>();
        check_not_signed<int const&>();
        check_not_signed<int&&>();
        check_not_signed<int volatile*>();
        check_not_signed<int[]>();
        check_not_signed<int[3]>();
        check_not_signed<int(&)[]>();
        check_not_signed<int[][2]>();
        
        check_not_signed<float*>();
        check_not_signed<float const*>();
        check_not_signed<float&>();
        check_not_signed<float const volatile&>();
        check_not_signed<float&&>();
        check_not_signed<float volatile&&>();
        check_not_signed<float[]>();
        check_not_signed<float[3]>();
        check_not_signed<float(&)[]>();
        check_not_signed<float[][2]>();
        
        check_not_signed<void>();
        
        check_not_signed<bmltb::class_type>();
        check_not_signed<int bmltb::class_type::*>();
        check_not_signed<bmltb::union_type[]>();
        check_not_signed<bmltb::enum_class>();
        check_not_signed<bmltb::incomplete_class>();
        check_not_signed<bmltb::incomplete_class*[][2]>();
        
        check_not_signed<auto (int) -> void>();
        check_not_signed<auto (int) const && noexcept -> void>();
        check_not_signed<auto (&)(int) -> void>();
        check_not_signed<auto (*)(int) noexcept -> void>();
        check_not_signed<auto (*&&)(int) noexcept -> void>();
        check_not_signed<auto (bmltb::class_type::*)() -> void>();
        check_not_signed<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }

    return 0;
}
