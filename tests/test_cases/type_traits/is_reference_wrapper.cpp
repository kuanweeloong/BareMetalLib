//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_reference_wrapper.hpp>
#include <bml/utilities/reference_wrapper.hpp>

template <typename T>
auto check_wrapper() noexcept -> void
{
    static_assert(bml::is_reference_wrapper<T>::value);
    static_assert(bml::is_reference_wrapper_v<T>);
    
    static_assert(bml::is_reference_wrapper<T const>::value);
    static_assert(bml::is_reference_wrapper_v<T const>);
    
    static_assert(bml::is_reference_wrapper<T volatile>::value);
    static_assert(bml::is_reference_wrapper_v<T volatile>);
    
    static_assert(bml::is_reference_wrapper<T const volatile>::value);
    static_assert(bml::is_reference_wrapper_v<T const volatile>);
}

template <typename T>
auto check_not_wrapper() noexcept -> void
{
    static_assert(!bml::is_reference_wrapper<T>::value);
    static_assert(!bml::is_reference_wrapper_v<T>);
    
    static_assert(!bml::is_reference_wrapper<T const>::value);
    static_assert(!bml::is_reference_wrapper_v<T const>);
    
    static_assert(!bml::is_reference_wrapper<T volatile>::value);
    static_assert(!bml::is_reference_wrapper_v<T volatile>);
    
    static_assert(!bml::is_reference_wrapper<T const volatile>::value);
    static_assert(!bml::is_reference_wrapper_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input type is a reference_wrapper.
    {
        check_wrapper<bml::reference_wrapper<int>>();
        check_wrapper<bml::reference_wrapper<int const>>();
        check_wrapper<bml::reference_wrapper<int[3]>>();
        check_wrapper<bml::reference_wrapper<auto (bmltb::class_type::*)() -> void>>();
        check_wrapper<bml::reference_wrapper<auto (bmltb::class_type::*)() const -> void>>();
        check_wrapper<bml::reference_wrapper<int bmltb::class_type::*>>();
        check_wrapper<bml::reference_wrapper<auto () -> int>>();
        
        auto i = 42;
        auto r = bml::reference_wrapper(i);
        
        static_assert(bml::is_reference_wrapper<decltype(r)>::value);
        static_assert(bml::is_reference_wrapper_v<decltype(r)>);
    }
    
    // Check that the result is false when the input type is not a reference_wrapper.
    {
        check_not_wrapper<bml::reference_wrapper<int>*>();
        check_not_wrapper<bml::reference_wrapper<int>&>();
        check_not_wrapper<bml::reference_wrapper<int>&&>();
        check_not_wrapper<bml::reference_wrapper<int>[3]>();
        check_not_wrapper<bml::reference_wrapper<int>[]>();
        
        check_not_wrapper<void>();
        
        check_not_wrapper<int>();
        check_not_wrapper<int*>();
        check_not_wrapper<int const*>();
        check_not_wrapper<int&>();
        check_not_wrapper<int const volatile&>();
        check_not_wrapper<int&&>();
        check_not_wrapper<int[3]>();
        check_not_wrapper<int[]>();
        
        check_not_wrapper<int bmltb::class_type::*>();
        check_not_wrapper<bmltb::enum_class>();
        check_not_wrapper<bmltb::union_type[]>();
        check_not_wrapper<bmltb::incomplete_class*>();
        check_not_wrapper<bmltb::incomplete_class*[][2]>();
        
        check_not_wrapper<auto (int) -> void>();
        check_not_wrapper<auto (int) const && noexcept -> void>();
        check_not_wrapper<auto (&)(int) -> void>();
        check_not_wrapper<auto (*)(int) noexcept -> void>();
        check_not_wrapper<auto (*&&)(int) noexcept -> void>();
        check_not_wrapper<auto (bmltb::class_type::*)() -> void>();
        check_not_wrapper<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }
    
    return 0;
}
