//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_trivial.hpp>

template <typename T>
auto check_trivial() noexcept -> void
{
    static_assert(bml::is_trivial<T>::value);
    static_assert(bml::is_trivial_v<T>);
    
    static_assert(bml::is_trivial<T const>::value);
    static_assert(bml::is_trivial_v<T const>);
    
    static_assert(bml::is_trivial<T volatile>::value);
    static_assert(bml::is_trivial_v<T volatile>);
    
    static_assert(bml::is_trivial<T const volatile>::value);
    static_assert(bml::is_trivial_v<T const volatile>);
}

template <typename T>
auto check_not_trivial() noexcept -> void
{
    static_assert(!bml::is_trivial<T>::value);
    static_assert(!bml::is_trivial_v<T>);
    
    static_assert(!bml::is_trivial<T const>::value);
    static_assert(!bml::is_trivial_v<T const>);
    
    static_assert(!bml::is_trivial<T volatile>::value);
    static_assert(!bml::is_trivial_v<T volatile>);
    
    static_assert(!bml::is_trivial<T const volatile>::value);
    static_assert(!bml::is_trivial_v<T const volatile>);
}

struct trivial_class {};

struct non_trivial_class
{
    non_trivial_class();
};

struct non_standard_trivial_class
{
public:

    int i;
    
protected:

    int j;
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a trivial type.
    {
        check_trivial<int>();
        check_trivial<double>();
        check_trivial<int*>();
        check_trivial<int const*>();
        check_trivial<char[3]>();
        check_trivial<char(*)[]>();
        
        check_trivial<bmltb::enum_class>();
        check_trivial<trivial_class>();
        check_trivial<bmltb::union_type[2]>();
        check_trivial<int bmltb::class_type::*>();
        check_trivial<bmltb::incomplete_class*>();
        check_trivial<bmltb::incomplete_class*[3][2]>();
        check_trivial<non_standard_trivial_class>();
        
        check_trivial<auto (*)(int) noexcept -> void>();
        check_trivial<auto (bmltb::class_type::*)() -> void>();
        check_trivial<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }
    
    // Check that the result is false when the input is not a trivial type.
    {
        check_not_trivial<void>();
        check_not_trivial<int&>();
        check_not_trivial<int const&>();
        check_not_trivial<int&&>();
        check_not_trivial<int(&)[]>();
        
        check_not_trivial<non_trivial_class>();
        
        check_not_trivial<auto (int) -> void>();
        check_not_trivial<auto (int) const && noexcept -> void>();
        check_not_trivial<auto (&)(int) -> void>();
        check_not_trivial<auto (*&&)(int) noexcept -> void>();
    }

    return 0;
}
