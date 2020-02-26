//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/basic_types/nullptr_ty.hpp>
#include <bml/type_traits/is_fundamental.hpp>

template <typename T>
auto check_fundamental() noexcept -> void
{
    static_assert(bml::is_fundamental<T>::value);
    static_assert(bml::is_fundamental_v<T>);
    
    static_assert(bml::is_fundamental<T const>::value);
    static_assert(bml::is_fundamental_v<T const>);
    
    static_assert(bml::is_fundamental<T volatile>::value);
    static_assert(bml::is_fundamental_v<T volatile>);
    
    static_assert(bml::is_fundamental<T const volatile>::value);
    static_assert(bml::is_fundamental_v<T const volatile>);
}

template <typename T>
auto check_not_fundamental() noexcept -> void
{
    static_assert(!bml::is_fundamental<T>::value);
    static_assert(!bml::is_fundamental_v<T>);
    
    static_assert(!bml::is_fundamental<T const>::value);
    static_assert(!bml::is_fundamental_v<T const>);
    
    static_assert(!bml::is_fundamental<T volatile>::value);
    static_assert(!bml::is_fundamental_v<T volatile>);
    
    static_assert(!bml::is_fundamental<T const volatile>::value);
    static_assert(!bml::is_fundamental_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a fundamental type.
    {
        check_fundamental<void>();
        
        check_fundamental<bml::nullptr_ty>();
        
        check_fundamental<int>();
        check_fundamental<unsigned long>();
        check_fundamental<long long>();
        check_fundamental<char>();
        check_fundamental<wchar_t>();
        check_fundamental<float>();
        check_fundamental<double>();
    }
    
    // Check that the result is false when the input is not a fundamental type.
    {
        check_not_fundamental<int[]>();
        check_not_fundamental<int[3]>();
        check_not_fundamental<int&>();
        check_not_fundamental<int const&>();
        check_not_fundamental<int&&>();
        check_not_fundamental<int(&)[]>();
        
        check_not_fundamental<bmltb::class_type>();
        check_not_fundamental<bmltb::enum_class>();
        check_not_fundamental<bmltb::union_type>();
        check_not_fundamental<bmltb::union_type[]>();
        check_not_fundamental<bmltb::incomplete_class>();
        check_not_fundamental<bmltb::incomplete_class*[][2]>();
        
        check_not_fundamental<int*>();
        check_not_fundamental<int const*>();
        check_not_fundamental<int(*)[]>();
        check_not_fundamental<bmltb::class_type*>();
        check_not_fundamental<bmltb::incomplete_class*>();
        
        check_not_fundamental<int bmltb::class_type::*>();
        check_not_fundamental<auto (bmltb::class_type::*)() -> void>();
        check_not_fundamental<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
        
        check_not_fundamental<auto (int) -> void>();
        check_not_fundamental<auto (int) const && noexcept -> void>();
        check_not_fundamental<auto (*)(int) noexcept -> void>();
        check_not_fundamental<auto (&)(int) -> void>();
        check_not_fundamental<auto (*&&)(int) noexcept -> void>();
    }

    return 0;
}
