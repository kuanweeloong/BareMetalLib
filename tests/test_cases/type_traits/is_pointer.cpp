//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_pointer.hpp>

template <typename T>
auto check_pointer() noexcept -> void
{
    static_assert(bml::is_pointer<T>::value);
    static_assert(bml::is_pointer_v<T>);
    
    static_assert(bml::is_pointer<T const>::value);
    static_assert(bml::is_pointer_v<T const>);
    
    static_assert(bml::is_pointer<T volatile>::value);
    static_assert(bml::is_pointer_v<T volatile>);
    
    static_assert(bml::is_pointer<T const volatile>::value);
    static_assert(bml::is_pointer_v<T const volatile>);
}

template <typename T>
auto check_not_pointer() noexcept -> void
{
    static_assert(!bml::is_pointer<T>::value);
    static_assert(!bml::is_pointer_v<T>);
    
    static_assert(!bml::is_pointer<T const>::value);
    static_assert(!bml::is_pointer_v<T const>);
    
    static_assert(!bml::is_pointer<T volatile>::value);
    static_assert(!bml::is_pointer_v<T volatile>);
    
    static_assert(!bml::is_pointer<T const volatile>::value);
    static_assert(!bml::is_pointer_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a pointer.
    {
        check_pointer<void*>();
        check_pointer<int*>();
        check_pointer<int const*>();
        check_pointer<char(*)[]>();
        
        check_pointer<bmltb::class_type*>();
        check_pointer<bmltb::incomplete_class*>();
        
        check_pointer<auto (*)() -> void>();
        check_pointer<auto (*)(int) noexcept -> void>();
    }
    
    // Check that the result is false when the input is not a pointer.
    {
        check_not_pointer<void>();
        check_not_pointer<int>();
        check_not_pointer<double>();
        check_not_pointer<char[3]>();
        check_not_pointer<char[]>();
        check_not_pointer<int&>();
        check_not_pointer<int const&>();
        check_not_pointer<int&&>();
        check_not_pointer<int(&)[]>();
        
        check_not_pointer<bmltb::class_type>();
        check_not_pointer<int bmltb::class_type::*>();
        check_not_pointer<bmltb::enum_class>();
        check_not_pointer<bmltb::union_type>();
        check_not_pointer<bmltb::incomplete_class*[][2]>();
        
        check_not_pointer<auto (int) -> void>();
        check_not_pointer<auto (int) const && noexcept -> void>();
        check_not_pointer<auto (&)(int) -> void>();
        check_not_pointer<auto (*&&)(int) noexcept -> void>();
        check_not_pointer<auto (bmltb::class_type::*)() -> void>();
        check_not_pointer<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }

    return 0;
}
