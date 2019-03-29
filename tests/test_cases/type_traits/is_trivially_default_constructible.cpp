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
#include <bml/type_traits/is_trivially_default_constructible.hpp>

template <typename T>
auto check_trivially_default_constructible() noexcept -> void
{
    static_assert(bml::is_trivially_default_constructible<T>::value);
    static_assert(bml::is_trivially_default_constructible_v<T>);
    
    static_assert(bml::is_trivially_default_constructible<T const>::value);
    static_assert(bml::is_trivially_default_constructible_v<T const>);
    
    static_assert(bml::is_trivially_default_constructible<T volatile>::value);
    static_assert(bml::is_trivially_default_constructible_v<T volatile>);
    
    static_assert(bml::is_trivially_default_constructible<T const volatile>::value);
    static_assert(bml::is_trivially_default_constructible_v<T const volatile>);
}

template <typename T>
auto check_not_trivially_default_constructible() noexcept -> void
{
    static_assert(!bml::is_trivially_default_constructible<T>::value);
    static_assert(!bml::is_trivially_default_constructible_v<T>);
    
    static_assert(!bml::is_trivially_default_constructible<T const>::value);
    static_assert(!bml::is_trivially_default_constructible_v<T const>);
    
    static_assert(!bml::is_trivially_default_constructible<T volatile>::value);
    static_assert(!bml::is_trivially_default_constructible_v<T volatile>);
    
    static_assert(!bml::is_trivially_default_constructible<T const volatile>::value);
    static_assert(!bml::is_trivially_default_constructible_v<T const volatile>);
}

struct empty {};

struct bit_zero
{
    int : 0;
};

union empty_union {};

struct abstract
{
    virtual auto foo() -> void = 0;
};

struct no_default_ctor
{
    no_default_ctor(int);
};

struct public_ctor
{
    public_ctor();
};

class private_ctor
{
    private_ctor();
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input type is trivially default constructible.
    {
        check_trivially_default_constructible<int>();
        check_trivially_default_constructible<double>();
        check_trivially_default_constructible<int*>();
        check_trivially_default_constructible<int const*>();
        check_trivially_default_constructible<char[3]>();
        check_trivially_default_constructible<char[5][3]>();
        check_trivially_default_constructible<char[5][3][2]>();
        
        check_trivially_default_constructible<empty_union>();
        check_trivially_default_constructible<bmltb::enum_class>();
        check_trivially_default_constructible<empty>();
        check_trivially_default_constructible<bit_zero>();
    }
    
    // Check that the result is false when the input type is not trivially default constructible.
    {
        check_not_trivially_default_constructible<public_ctor>();
    }
    
    // Check that the result is false when the input type is not default constructible.
    {
        check_not_trivially_default_constructible<void>();
        check_not_trivially_default_constructible<int&>();
        check_not_trivially_default_constructible<int&&>();
        check_not_trivially_default_constructible<char[]>();
        check_not_trivially_default_constructible<char[][3]>();
        check_not_trivially_default_constructible<char[][3][5]>();
        
        check_not_trivially_default_constructible<abstract>();
        check_not_trivially_default_constructible<no_default_ctor>();
        check_not_trivially_default_constructible<private_ctor>();
        
        check_not_trivially_default_constructible<auto () -> void>();
        check_not_trivially_default_constructible<auto () const -> void>();
        check_not_trivially_default_constructible<auto () volatile noexcept -> void>();
        check_not_trivially_default_constructible<auto () volatile & -> void>();
        check_not_trivially_default_constructible<auto () const & noexcept -> void>();
        check_not_trivially_default_constructible<auto () const volatile && -> void >();
    }
    
    return 0;
}
