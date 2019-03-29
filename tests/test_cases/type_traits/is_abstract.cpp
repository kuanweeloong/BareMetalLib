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
#include <bml/type_traits/is_abstract.hpp>

template <typename T>
auto check_abstract() noexcept -> void
{
    static_assert(bml::is_abstract<T>::value);
    static_assert(bml::is_abstract_v<T>);
    
    static_assert(bml::is_abstract<T const>::value);
    static_assert(bml::is_abstract_v<T const>);
    
    static_assert(bml::is_abstract<T volatile>::value);
    static_assert(bml::is_abstract_v<T volatile>);
    
    static_assert(bml::is_abstract<T const volatile>::value);
    static_assert(bml::is_abstract_v<T const volatile>);
}

template <typename T>
auto check_not_abstract() noexcept -> void
{
    static_assert(!bml::is_abstract<T>::value);
    static_assert(!bml::is_abstract_v<T>);
    
    static_assert(!bml::is_abstract<T const>::value);
    static_assert(!bml::is_abstract_v<T const>);
    
    static_assert(!bml::is_abstract<T volatile>::value);
    static_assert(!bml::is_abstract_v<T volatile>);
    
    static_assert(!bml::is_abstract<T const volatile>::value);
    static_assert(!bml::is_abstract_v<T const volatile>);
}

struct non_virt_base { auto foo() -> void; };
struct non_virt_derived : non_virt_base {};

struct virt_base { virtual auto foo() -> void {} };
struct virt_derived : virt_base {};

struct pure_virt_base { virtual auto foo() -> void = 0; };
struct pure_virt_derived : pure_virt_base {};

struct pure_virt_dtor { virtual ~pure_virt_dtor() = 0; };

template <typename>
struct abstract_template
{
    virtual auto test() -> void = 0;
};

template <>
struct abstract_template<double> {};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is an abstract type.
    {
        check_abstract<pure_virt_base>();
        check_abstract<pure_virt_derived>();
        check_abstract<pure_virt_dtor>();
        check_abstract<abstract_template<int>>();
    }
    
    // Check that the result is false when the input is not an abstract type.
    {
        check_not_abstract<void>();
        check_not_abstract<int>();
        check_not_abstract<int*>();
        check_not_abstract<int const*>();
        check_not_abstract<int&>();
        check_not_abstract<int const&>();
        check_not_abstract<int&&>();
        check_not_abstract<int(&)[]>();
        check_not_abstract<int[3]>();
        check_not_abstract<int(*)[]>();
        check_not_abstract<double>();
        check_not_abstract<char>();
        
        check_not_abstract<non_virt_base>();
        check_not_abstract<non_virt_derived>();
        check_not_abstract<virt_base>();
        check_not_abstract<virt_derived>();
        check_not_abstract<abstract_template<double>>();
        
        check_not_abstract<bmltb::enum_class>();
        check_not_abstract<bmltb::class_type>();
        check_not_abstract<bmltb::union_type>();
        check_not_abstract<bmltb::union_type[2]>();
        check_not_abstract<int bmltb::class_type::*>();
        check_not_abstract<bmltb::incomplete_class*>();
        check_not_abstract<bmltb::incomplete_class*[1][2]>();
        
        check_not_abstract<auto (*)(int) noexcept -> void>();
        check_not_abstract<auto (bmltb::class_type::*)() -> void>();
        check_not_abstract<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
        
        check_not_abstract<auto (int) -> void>();
        check_not_abstract<auto (int) const && noexcept -> void>();
        check_not_abstract<auto (&)(int) -> void>();
        check_not_abstract<auto (*&&)(int) noexcept -> void>();
    }

    return 0;
}
