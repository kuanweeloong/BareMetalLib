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
#include <bml/type_traits/is_standard_layout.hpp>

template <typename T>
auto check_standard_layout() noexcept -> void
{
    static_assert(bml::is_standard_layout<T>::value);
    static_assert(bml::is_standard_layout_v<T>);
    
    static_assert(bml::is_standard_layout<T const>::value);
    static_assert(bml::is_standard_layout_v<T const>);
    
    static_assert(bml::is_standard_layout<T volatile>::value);
    static_assert(bml::is_standard_layout_v<T volatile>);
    
    static_assert(bml::is_standard_layout<T const volatile>::value);
    static_assert(bml::is_standard_layout_v<T const volatile>);
}

template <typename T>
auto check_not_standard_layout() noexcept -> void
{
    static_assert(!bml::is_standard_layout<T>::value);
    static_assert(!bml::is_standard_layout_v<T>);
    
    static_assert(!bml::is_standard_layout<T const>::value);
    static_assert(!bml::is_standard_layout_v<T const>);
    
    static_assert(!bml::is_standard_layout<T volatile>::value);
    static_assert(!bml::is_standard_layout_v<T volatile>);
    
    static_assert(!bml::is_standard_layout<T const volatile>::value);
    static_assert(!bml::is_standard_layout_v<T const volatile>);
}

struct mixed_access
{
public:

    int i;
    
protected:

    int j;
};

struct base
{
    int i;
};

struct derived : base
{
    int j;
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a standard layout type.
    {
        check_standard_layout<int>();
        check_standard_layout<double>();
        check_standard_layout<int*>();
        check_standard_layout<int const*>();
        check_standard_layout<char[3]>();
        check_standard_layout<char(*)[]>();
        
        check_standard_layout<base>();
        check_standard_layout<bmltb::enum_class>();
        check_standard_layout<bmltb::union_type[2]>();
        check_standard_layout<int bmltb::class_type::*>();
        check_standard_layout<bmltb::incomplete_class*>();
        check_standard_layout<bmltb::incomplete_class*[3][2]>();
        
        check_standard_layout<auto (*)(int) noexcept -> void>();
        check_standard_layout<auto (bmltb::class_type::*)() -> void>();
        check_standard_layout<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }
    
    // Check that the result is false when the input is not a standard layout type.
    {
        check_not_standard_layout<void>();
        check_not_standard_layout<int&>();
        check_not_standard_layout<int const&>();
        check_not_standard_layout<int&&>();
        check_not_standard_layout<int(&)[]>();
        
        check_not_standard_layout<mixed_access>();
        check_not_standard_layout<derived>();
        
        check_not_standard_layout<auto (int) -> void>();
        check_not_standard_layout<auto (int) const && noexcept -> void>();
        check_not_standard_layout<auto (&)(int) -> void>();
        check_not_standard_layout<auto (*&&)(int) noexcept -> void>();
    }

    return 0;
}
