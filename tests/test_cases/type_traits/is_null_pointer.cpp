//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_null_pointer.hpp>

template <typename T>
auto check_null_pointer() noexcept -> void
{
    static_assert(bml::is_null_pointer<T>::value);
    static_assert(bml::is_null_pointer_v<T>);
    
    static_assert(bml::is_null_pointer<T const>::value);
    static_assert(bml::is_null_pointer_v<T const>);
    
    static_assert(bml::is_null_pointer<T volatile>::value);
    static_assert(bml::is_null_pointer_v<T volatile>);
    
    static_assert(bml::is_null_pointer<T const volatile>::value);
    static_assert(bml::is_null_pointer_v<T const volatile>);
}

template <typename T>
auto check_not_null_pointer() noexcept -> void
{
    static_assert(!bml::is_null_pointer<T>::value);
    static_assert(!bml::is_null_pointer_v<T>);
    
    static_assert(!bml::is_null_pointer<T const>::value);
    static_assert(!bml::is_null_pointer_v<T const>);
    
    static_assert(!bml::is_null_pointer<T volatile>::value);
    static_assert(!bml::is_null_pointer_v<T volatile>);
    
    static_assert(!bml::is_null_pointer<T const volatile>::value);
    static_assert(!bml::is_null_pointer_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a null pointer.
    {
        check_null_pointer<bml::nullptr_ty>();
    }
    
    // Check that the result is false when the input is not a null pointer.
    {
        check_not_null_pointer<void>();
        check_not_null_pointer<int>();
        check_not_null_pointer<double>();
        check_not_null_pointer<int*>();
        check_not_null_pointer<int const*>();
        check_not_null_pointer<char[3]>();
        check_not_null_pointer<char[]>();
        check_not_null_pointer<char(*)[]>();
        check_not_null_pointer<int&>();
        check_not_null_pointer<int const&>();
        check_not_null_pointer<int&&>();
        check_not_null_pointer<int(&)[]>();
        
        check_not_null_pointer<bmltb::class_type>();
        check_not_null_pointer<int bmltb::class_type::*>();
        check_not_null_pointer<bmltb::enum_class>();
        check_not_null_pointer<bmltb::union_type[]>();
        check_not_null_pointer<bmltb::incomplete_class>();
        check_not_null_pointer<bmltb::incomplete_class*>();
        check_not_null_pointer<bmltb::incomplete_class*[][2]>();
        
        check_not_null_pointer<auto (int) -> void>();
        check_not_null_pointer<auto (int) const && noexcept -> void>();
        check_not_null_pointer<auto (*)(int) noexcept -> void>();
        check_not_null_pointer<auto (&)(int) -> void>();
        check_not_null_pointer<auto (*&&)(int) noexcept -> void>();
        check_not_null_pointer<auto (bmltb::class_type::*)() -> void>();
        check_not_null_pointer<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }

    return 0;
}
