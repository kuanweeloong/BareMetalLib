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
#include <bml/type_traits/is_scalar.hpp>

template <typename T>
auto check_scalar() noexcept -> void
{
    static_assert(bml::is_scalar<T>::value);
    static_assert(bml::is_scalar_v<T>);
    
    static_assert(bml::is_scalar<T const>::value);
    static_assert(bml::is_scalar_v<T const>);
    
    static_assert(bml::is_scalar<T volatile>::value);
    static_assert(bml::is_scalar_v<T volatile>);
    
    static_assert(bml::is_scalar<T const volatile>::value);
    static_assert(bml::is_scalar_v<T const volatile>);
}

template <typename T>
auto check_not_scalar() noexcept -> void
{
    static_assert(!bml::is_scalar<T>::value);
    static_assert(!bml::is_scalar_v<T>);
    
    static_assert(!bml::is_scalar<T const>::value);
    static_assert(!bml::is_scalar_v<T const>);
    
    static_assert(!bml::is_scalar<T volatile>::value);
    static_assert(!bml::is_scalar_v<T volatile>);
    
    static_assert(!bml::is_scalar<T const volatile>::value);
    static_assert(!bml::is_scalar_v<T const volatile>);
}

enum legacy_enum
{
    legacy_enum_one,
    legacy_enum_two
};

using function_ptr = auto () -> void;

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a scalar type.
    {
        check_scalar<int>();
        check_scalar<double>();
        check_scalar<char>();
        check_scalar<wchar_t>();
        check_scalar<float>();
        check_scalar<double>();
        
        check_scalar<bmltb::enum_class>();
        check_scalar<legacy_enum>();
        
        check_scalar<int*>();
        check_scalar<int const*>();
        check_scalar<int(*)[]>();
        check_scalar<bmltb::class_type*>();
        check_scalar<bmltb::incomplete_class*>();
        check_scalar<auto (*)(int) noexcept -> void>();
        
        check_scalar<int bmltb::class_type::*>();
        check_scalar<function_ptr bmltb::class_type::*>();
        check_scalar<auto (bmltb::class_type::*)() -> void>();
        check_scalar<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
        
        check_scalar<bml::nullptr_ty>();
    }
    
    // Check that the result is false when the input is not a scalar type.
    {
        check_not_scalar<void>();
        check_not_scalar<int[]>();
        check_not_scalar<int[3]>();
        check_not_scalar<int&>();
        check_not_scalar<int const&>();
        check_not_scalar<int&&>();
        check_not_scalar<int(&)[]>();
        
        check_not_scalar<bmltb::class_type>();
        check_not_scalar<bmltb::union_type>();
        check_not_scalar<bmltb::union_type[]>();
        check_not_scalar<bmltb::incomplete_class>();
        check_not_scalar<bmltb::incomplete_class*[][2]>();
        
        check_not_scalar<auto (int) -> void>();
        check_not_scalar<auto (int) const && noexcept -> void>();
        check_not_scalar<auto (&)(int) -> void>();
        check_not_scalar<auto (*&&)(int) noexcept -> void>();
    }

    return 0;
}
