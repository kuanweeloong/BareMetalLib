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
#include <bml/type_traits/is_empty.hpp>

template <typename T>
auto check_empty() noexcept -> void
{
    static_assert(bml::is_empty<T>::value);
    static_assert(bml::is_empty_v<T>);
    
    static_assert(bml::is_empty<T const>::value);
    static_assert(bml::is_empty_v<T const>);
    
    static_assert(bml::is_empty<T volatile>::value);
    static_assert(bml::is_empty_v<T volatile>);
    
    static_assert(bml::is_empty<T const volatile>::value);
    static_assert(bml::is_empty_v<T const volatile>);
}

template <typename T>
auto check_not_empty() noexcept -> void
{
    static_assert(!bml::is_empty<T>::value);
    static_assert(!bml::is_empty_v<T>);
    
    static_assert(!bml::is_empty<T const>::value);
    static_assert(!bml::is_empty_v<T const>);
    
    static_assert(!bml::is_empty<T volatile>::value);
    static_assert(!bml::is_empty_v<T volatile>);
    
    static_assert(!bml::is_empty<T const volatile>::value);
    static_assert(!bml::is_empty_v<T const volatile>);
}

struct empty {};
struct not_empty { int i; };

struct empty_base : empty {};
struct virtual_empty_base: virtual empty {};
struct non_empty_base : not_empty {};
struct virtual_non_empty_base: virtual not_empty {};

struct static_member
{
    static int i;
};

struct bit_zero
{
    int : 0;
};

struct bit_one
{
    int i : 1;
};

struct virtual_func
{
    virtual ~virtual_func();
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is an empty type.
    {
        check_empty<empty>();
        check_empty<empty_base>();
        check_empty<static_member>();
        check_empty<bit_zero>();
    }
    
    // Check that the result is false when the input is not an empty type.
    {
        check_not_empty<not_empty>();
        check_not_empty<virtual_empty_base>();
        check_not_empty<non_empty_base>();
        check_not_empty<virtual_non_empty_base>();
        check_not_empty<bit_one>();
        check_not_empty<virtual_func>();
        
        check_not_empty<void>();
        check_not_empty<int>();
        check_not_empty<double>();
        check_not_empty<int*>();
        check_not_empty<int const*>();
        check_not_empty<char[3]>();
        check_not_empty<char[]>();
        check_not_empty<char(*)[]>();
        check_not_empty<int&>();
        check_not_empty<int const&>();
        check_not_empty<int&&>();
        check_not_empty<int(&)[]>();
        
        check_not_empty<bmltb::class_type>();
        check_not_empty<int bmltb::class_type::*>();
        check_not_empty<bmltb::enum_class>();
        check_not_empty<bmltb::union_type>();
        check_not_empty<bmltb::incomplete_class*>();
        check_not_empty<bmltb::incomplete_class*[][2]>();
        
        check_not_empty<auto (int) -> void>();
        check_not_empty<auto (int) const && noexcept -> void>();
        check_not_empty<auto (*)(int) noexcept -> void>();
        check_not_empty<auto (&)(int) -> void>();
        check_not_empty<auto (*&&)(int) noexcept -> void>();
        check_not_empty<auto (bmltb::class_type::*)() -> void>();
        check_not_empty<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }

    return 0;
}
