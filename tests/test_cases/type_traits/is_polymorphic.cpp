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
#include <bml/type_traits/is_polymorphic.hpp>

template <typename T>
auto check_polymorphic() noexcept -> void
{
    static_assert(bml::is_polymorphic<T>::value);
    static_assert(bml::is_polymorphic_v<T>);
    
    static_assert(bml::is_polymorphic<T const>::value);
    static_assert(bml::is_polymorphic_v<T const>);
    
    static_assert(bml::is_polymorphic<T volatile>::value);
    static_assert(bml::is_polymorphic_v<T volatile>);
    
    static_assert(bml::is_polymorphic<T const volatile>::value);
    static_assert(bml::is_polymorphic_v<T const volatile>);
}

template <typename T>
auto check_not_polymorphic() noexcept -> void
{
    static_assert(!bml::is_polymorphic<T>::value);
    static_assert(!bml::is_polymorphic_v<T>);
    
    static_assert(!bml::is_polymorphic<T const>::value);
    static_assert(!bml::is_polymorphic_v<T const>);
    
    static_assert(!bml::is_polymorphic<T volatile>::value);
    static_assert(!bml::is_polymorphic_v<T volatile>);
    
    static_assert(!bml::is_polymorphic<T const volatile>::value);
    static_assert(!bml::is_polymorphic_v<T const volatile>);
}

struct non_virt_base { auto foo() -> void; };
struct non_virt_derived : non_virt_base {};

struct virt_base { virtual auto foo() -> void = 0; };
struct virt_derived : virt_base {};

struct virt_dtor { virtual ~virt_dtor() = 0; };

struct final_class final {};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a polymorphic type.
    {
        check_polymorphic<virt_base>();
        check_polymorphic<virt_derived>();
        check_polymorphic<virt_dtor>();
    }
    
    // Check that the result is false when the input is not a polymorphic type.
    {
        check_not_polymorphic<void>();
        check_not_polymorphic<int>();
        check_not_polymorphic<int*>();
        check_not_polymorphic<int const*>();
        check_not_polymorphic<int&>();
        check_not_polymorphic<int const&>();
        check_not_polymorphic<int&&>();
        check_not_polymorphic<int(&)[]>();
        check_not_polymorphic<int[3]>();
        check_not_polymorphic<int(*)[]>();
        check_not_polymorphic<double>();
        check_not_polymorphic<char>();
        
        check_not_polymorphic<non_virt_base>();
        check_not_polymorphic<non_virt_derived>();
        check_not_polymorphic<final_class>();
        check_not_polymorphic<bmltb::enum_class>();
        check_not_polymorphic<bmltb::class_type>();
        check_not_polymorphic<bmltb::union_type>();
        check_not_polymorphic<bmltb::union_type[2]>();
        check_not_polymorphic<int bmltb::class_type::*>();
        check_not_polymorphic<bmltb::incomplete_class*>();
        check_not_polymorphic<bmltb::incomplete_class*[1][2]>();
        
        check_not_polymorphic<auto (*)(int) noexcept -> void>();
        check_not_polymorphic<auto (bmltb::class_type::*)() -> void>();
        check_not_polymorphic<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
        
        check_not_polymorphic<auto (int) -> void>();
        check_not_polymorphic<auto (int) const && noexcept -> void>();
        check_not_polymorphic<auto (&)(int) -> void>();
        check_not_polymorphic<auto (*&&)(int) noexcept -> void>();
    }

    return 0;
}
