//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_class.hpp>

template <typename T>
auto check_class() noexcept -> void
{
    static_assert(bml::is_class<T>::value);
    static_assert(bml::is_class_v<T>);
    
    static_assert(bml::is_class<T const>::value);
    static_assert(bml::is_class_v<T const>);
    
    static_assert(bml::is_class<T volatile>::value);
    static_assert(bml::is_class_v<T volatile>);
    
    static_assert(bml::is_class<T const volatile>::value);
    static_assert(bml::is_class_v<T const volatile>);
}

template <typename T>
auto check_not_class() noexcept -> void
{
    static_assert(!bml::is_class<T>::value);
    static_assert(!bml::is_class_v<T>);
    
    static_assert(!bml::is_class<T const>::value);
    static_assert(!bml::is_class_v<T const>);
    
    static_assert(!bml::is_class<T volatile>::value);
    static_assert(!bml::is_class_v<T volatile>);
    
    static_assert(!bml::is_class<T const volatile>::value);
    static_assert(!bml::is_class_v<T const volatile>);
}

struct empty {};

struct abstract
{
    virtual ~abstract() = 0;
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a class type.
    {
        check_class<bmltb::class_type>();
        check_class<empty>();
        check_class<abstract>();
        check_class<bmltb::incomplete_class>();
    }
    
    // Check that the result is false when the input is not a class type.
    {
        check_not_class<bmltb::class_type*>();
        check_not_class<bmltb::class_type&>();
        check_not_class<bmltb::class_type const&>();
        check_not_class<bmltb::class_type&&>();
        check_not_class<bmltb::class_type volatile*>();
        check_not_class<bmltb::class_type(&)[]>();
        check_not_class<bmltb::class_type(*)[]>();
        check_not_class<bmltb::class_type[]>();
        check_not_class<bmltb::class_type[3]>();
        check_not_class<bmltb::class_type[][2]>();
        
        check_not_class<void>();
        check_not_class<int>();
        check_not_class<float>();
        
        check_not_class<int bmltb::class_type::*>();
        check_not_class<bmltb::enum_class>();
        check_not_class<bmltb::union_type[]>();
        check_not_class<bmltb::incomplete_class*>();
        check_not_class<bmltb::incomplete_class*[][2]>();
        
        check_not_class<auto (int) -> void>();
        check_not_class<auto (int) const && noexcept -> void>();
        check_not_class<auto (&)(int) -> void>();
        check_not_class<auto (*)(int) noexcept -> void>();
        check_not_class<auto (*&&)(int) noexcept -> void>();
        check_not_class<auto (bmltb::class_type::*)() -> void>();
        check_not_class<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }

    return 0;
}
