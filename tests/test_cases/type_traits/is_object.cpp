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
#include <bml/type_traits/is_object.hpp>

template <typename T>
auto check_object() noexcept -> void
{
    static_assert(bml::is_object<T>::value);
    static_assert(bml::is_object_v<T>);
    
    static_assert(bml::is_object<T const>::value);
    static_assert(bml::is_object_v<T const>);
    
    static_assert(bml::is_object<T volatile>::value);
    static_assert(bml::is_object_v<T volatile>);
    
    static_assert(bml::is_object<T const volatile>::value);
    static_assert(bml::is_object_v<T const volatile>);
}

template <typename T>
auto check_not_object() noexcept -> void
{
    static_assert(!bml::is_object<T>::value);
    static_assert(!bml::is_object_v<T>);
    
    static_assert(!bml::is_object<T const>::value);
    static_assert(!bml::is_object_v<T const>);
    
    static_assert(!bml::is_object<T volatile>::value);
    static_assert(!bml::is_object_v<T volatile>);
    
    static_assert(!bml::is_object<T const volatile>::value);
    static_assert(!bml::is_object_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is an object type.
    {
        check_object<int>();
        check_object<double>();
        check_object<char>();
        check_object<wchar_t>();
        check_object<float>();
        check_object<double>();
        check_object<int[]>();
        check_object<int[3]>();
        
        check_object<bmltb::class_type>();
        check_object<bmltb::enum_class>();
        check_object<bmltb::union_type>();
        check_object<bmltb::union_type[]>();
        check_object<bmltb::incomplete_class>();
        check_object<bmltb::incomplete_class*[][2]>();
        
        check_object<int*>();
        check_object<int const*>();
        check_object<int(*)[]>();
        check_object<bmltb::class_type*>();
        check_object<bmltb::incomplete_class*>();
        check_object<auto (*)(int) noexcept -> void>();
        
        check_object<int bmltb::class_type::*>();
        check_object<auto (bmltb::class_type::*)() -> void>();
        check_object<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
        
        check_object<bml::nullptr_ty>();
    }
    
    // Check that the result is false when the input is not an object type.
    {
        check_not_object<void>();

        check_not_object<int&>();
        check_not_object<int const&>();
        check_not_object<int&&>();
        check_not_object<int(&)[]>();
        
        check_not_object<auto (int) -> void>();
        check_not_object<auto (int) const && noexcept -> void>();
        check_not_object<auto (&)(int) -> void>();
        check_not_object<auto (*&&)(int) noexcept -> void>();
    }

    return 0;
}
