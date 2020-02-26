//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/has_virtual_destructor.hpp>

template <typename T>
auto check_has_virtual_destructor() noexcept -> void
{
    static_assert(bml::has_virtual_destructor<T>::value);
    static_assert(bml::has_virtual_destructor_v<T>);
    
    static_assert(bml::has_virtual_destructor<T const>::value);
    static_assert(bml::has_virtual_destructor_v<T const>);
    
    static_assert(bml::has_virtual_destructor<T volatile>::value);
    static_assert(bml::has_virtual_destructor_v<T volatile>);
    
    static_assert(bml::has_virtual_destructor<T const volatile>::value);
    static_assert(bml::has_virtual_destructor_v<T const volatile>);
}

template <typename T>
auto check_no_virtual_destructor() noexcept -> void
{
    static_assert(!bml::has_virtual_destructor<T>::value);
    static_assert(!bml::has_virtual_destructor_v<T>);
    
    static_assert(!bml::has_virtual_destructor<T const>::value);
    static_assert(!bml::has_virtual_destructor_v<T const>);
    
    static_assert(!bml::has_virtual_destructor<T volatile>::value);
    static_assert(!bml::has_virtual_destructor_v<T volatile>);
    
    static_assert(!bml::has_virtual_destructor<T const volatile>::value);
    static_assert(!bml::has_virtual_destructor_v<T const volatile>);
}

struct normal_dtor { ~normal_dtor(); };
struct normal_dtor_derived : normal_dtor {};

struct virt_dtor { virtual ~virt_dtor(); };
struct virt_dtor_derived : virt_dtor {};

struct pure_virt_dtor { virtual ~pure_virt_dtor() = 0; };
struct pure_virt_dtor_derived : pure_virt_dtor {};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input has a virtual destructor.
    {
        check_has_virtual_destructor<virt_dtor>();
        check_has_virtual_destructor<virt_dtor_derived>();
        
        check_has_virtual_destructor<pure_virt_dtor>();
        check_has_virtual_destructor<pure_virt_dtor_derived>();
    }
    
    // Check that the result is false when the input does not have a virtual destructor.
    {
        check_no_virtual_destructor<void>();
        check_no_virtual_destructor<int>();
        check_no_virtual_destructor<int*>();
        check_no_virtual_destructor<int const*>();
        check_no_virtual_destructor<int&>();
        check_no_virtual_destructor<int const&>();
        check_no_virtual_destructor<int&&>();
        check_no_virtual_destructor<int(&)[]>();
        check_no_virtual_destructor<int[3]>();
        check_no_virtual_destructor<int(*)[]>();
        check_no_virtual_destructor<double>();
        check_no_virtual_destructor<char>();
        
        check_no_virtual_destructor<normal_dtor>();
        check_no_virtual_destructor<normal_dtor_derived>();
        
        check_no_virtual_destructor<bmltb::enum_class>();
        check_no_virtual_destructor<bmltb::class_type>();
        check_no_virtual_destructor<bmltb::union_type>();
        check_no_virtual_destructor<bmltb::union_type[2]>();
        check_no_virtual_destructor<int bmltb::class_type::*>();
        check_no_virtual_destructor<bmltb::incomplete_class*>();
        check_no_virtual_destructor<bmltb::incomplete_class*[1][2]>();
        
        check_no_virtual_destructor<auto (*)(int) noexcept -> void>();
        check_no_virtual_destructor<auto (bmltb::class_type::*)() -> void>();
        check_no_virtual_destructor<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
        
        check_no_virtual_destructor<auto (int) -> void>();
        check_no_virtual_destructor<auto (int) const && noexcept -> void>();
        check_no_virtual_destructor<auto (&)(int) -> void>();
        check_no_virtual_destructor<auto (*&&)(int) noexcept -> void>();
    }

    return 0;
}
