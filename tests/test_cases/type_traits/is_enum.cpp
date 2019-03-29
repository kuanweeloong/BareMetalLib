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
#include <bml/type_traits/is_enum.hpp>

template <typename T>
auto check_enum() noexcept -> void
{
    static_assert(bml::is_enum<T>::value);
    static_assert(bml::is_enum_v<T>);
    
    static_assert(bml::is_enum<T const>::value);
    static_assert(bml::is_enum_v<T const>);
    
    static_assert(bml::is_enum<T volatile>::value);
    static_assert(bml::is_enum_v<T volatile>);
    
    static_assert(bml::is_enum<T const volatile>::value);
    static_assert(bml::is_enum_v<T const volatile>);
}

template <typename T>
auto check_not_enum() noexcept -> void
{
    static_assert(!bml::is_enum<T>::value);
    static_assert(!bml::is_enum_v<T>);
    
    static_assert(!bml::is_enum<T const>::value);
    static_assert(!bml::is_enum_v<T const>);
    
    static_assert(!bml::is_enum<T volatile>::value);
    static_assert(!bml::is_enum_v<T volatile>);
    
    static_assert(!bml::is_enum<T const volatile>::value);
    static_assert(!bml::is_enum_v<T const volatile>);
}

enum classic_enum
{
    classic_enum_one,
    classic_enum_two
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is an enum type.
    {
        check_enum<bmltb::enum_class>();
        check_enum<classic_enum>();
    }
    
    // Check that the result is false when the input is not an enum type.
    {
        check_not_enum<bmltb::enum_class*>();
        check_not_enum<bmltb::enum_class&>();
        check_not_enum<bmltb::enum_class const&>();
        check_not_enum<bmltb::enum_class&&>();
        check_not_enum<bmltb::enum_class volatile*>();
        check_not_enum<bmltb::enum_class(&)[]>();
        check_not_enum<bmltb::enum_class(*)[]>();
        check_not_enum<bmltb::enum_class[]>();
        check_not_enum<bmltb::enum_class[3]>();
        check_not_enum<bmltb::enum_class[][2]>();
        
        check_not_enum<classic_enum*>();
        check_not_enum<classic_enum&>();
        check_not_enum<classic_enum const&>();
        check_not_enum<classic_enum&&>();
        check_not_enum<classic_enum volatile*>();
        check_not_enum<classic_enum(&)[]>();
        check_not_enum<classic_enum(*)[]>();
        check_not_enum<classic_enum[]>();
        check_not_enum<classic_enum[3]>();
        check_not_enum<classic_enum[][2]>();
        
        check_not_enum<void>();
        check_not_enum<int>();
        check_not_enum<float>();
        
        check_not_enum<bmltb::class_type>();
        check_not_enum<int bmltb::class_type::*>();
        check_not_enum<bmltb::incomplete_class>();
        check_not_enum<bmltb::union_type[]>();
        check_not_enum<bmltb::incomplete_class*>();
        check_not_enum<bmltb::incomplete_class*[][2]>();
        
        check_not_enum<auto (int) -> void>();
        check_not_enum<auto (int) const && noexcept -> void>();
        check_not_enum<auto (&)(int) -> void>();
        check_not_enum<auto (*)(int) noexcept -> void>();
        check_not_enum<auto (*&&)(int) noexcept -> void>();
        check_not_enum<auto (bmltb::class_type::*)() -> void>();
        check_not_enum<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }

    return 0;
}
