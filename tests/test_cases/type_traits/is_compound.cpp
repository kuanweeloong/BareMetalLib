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
#include <bml/type_traits/is_compound.hpp>

template <typename T>
auto check_compound() noexcept -> void
{
    static_assert(bml::is_compound<T>::value);
    static_assert(bml::is_compound_v<T>);
    
    static_assert(bml::is_compound<T const>::value);
    static_assert(bml::is_compound_v<T const>);
    
    static_assert(bml::is_compound<T volatile>::value);
    static_assert(bml::is_compound_v<T volatile>);
    
    static_assert(bml::is_compound<T const volatile>::value);
    static_assert(bml::is_compound_v<T const volatile>);
}

template <typename T>
auto check_not_compound() noexcept -> void
{
    static_assert(!bml::is_compound<T>::value);
    static_assert(!bml::is_compound_v<T>);
    
    static_assert(!bml::is_compound<T const>::value);
    static_assert(!bml::is_compound_v<T const>);
    
    static_assert(!bml::is_compound<T volatile>::value);
    static_assert(!bml::is_compound_v<T volatile>);
    
    static_assert(!bml::is_compound<T const volatile>::value);
    static_assert(!bml::is_compound_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a compound type.
    {
        check_compound<int[]>();
        check_compound<int[3]>();
        check_compound<bmltb::incomplete_class*[][2]>();
        
        check_compound<auto (int) -> void>();
        check_compound<auto (int) const && noexcept -> void>();
        
        check_compound<void*>();
        check_compound<void const volatile*>();
        check_compound<int*>();
        check_compound<int const*>();
        check_compound<int(*)[]>();
        check_compound<bmltb::class_type*>();
        check_compound<bmltb::incomplete_class*>();
        check_compound<auto (*)(int) noexcept -> void>();
        
        check_compound<int&>();
        check_compound<int const&>();
        check_compound<int(&)[]>();
        check_compound<int&&>();
        check_compound<auto (&)(int) -> void>();
        check_compound<auto (*&&)(int) noexcept -> void>();
        
        check_compound<bmltb::class_type>();
        check_compound<bmltb::union_type>();
        check_compound<bmltb::enum_class>();
        check_compound<bmltb::incomplete_class>();
        
        check_compound<int bmltb::class_type::*>();
        check_compound<auto (bmltb::class_type::*)() -> void>();
        check_compound<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }
    
    // Check that the result is false when the input is not a compound type.
    {
        check_not_compound<void>();
        
        check_not_compound<bml::nullptr_ty>();
        
        check_not_compound<int>();
        check_not_compound<unsigned long>();
        check_not_compound<long long>();
        check_not_compound<char>();
        check_not_compound<wchar_t>();
        check_not_compound<float>();
        check_not_compound<double>();
    }

    return 0;
}
