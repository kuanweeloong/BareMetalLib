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
#include <bml/type_traits/is_final.hpp>

template <typename T>
auto check_final() noexcept -> void
{
    static_assert(bml::is_final<T>::value);
    static_assert(bml::is_final_v<T>);
    
    static_assert(bml::is_final<T const>::value);
    static_assert(bml::is_final_v<T const>);
    
    static_assert(bml::is_final<T volatile>::value);
    static_assert(bml::is_final_v<T volatile>);
    
    static_assert(bml::is_final<T const volatile>::value);
    static_assert(bml::is_final_v<T const volatile>);
}

template <typename T>
auto check_not_final() noexcept -> void
{
    static_assert(!bml::is_final<T>::value);
    static_assert(!bml::is_final_v<T>);
    
    static_assert(!bml::is_final<T const>::value);
    static_assert(!bml::is_final_v<T const>);
    
    static_assert(!bml::is_final<T volatile>::value);
    static_assert(!bml::is_final_v<T volatile>);
    
    static_assert(!bml::is_final<T const volatile>::value);
    static_assert(!bml::is_final_v<T const volatile>);
}

struct final_class final {};
union final_union final {};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a final class or union.
    {
        check_final<final_class>();
        check_final<final_union>();
    }
    
    // Check that the result is false when the input is not a final class or union.
    {
        check_not_final<void>();
        check_not_final<int>();
        check_not_final<int*>();
        check_not_final<int const*>();
        check_not_final<int&>();
        check_not_final<int const&>();
        check_not_final<int&&>();
        check_not_final<int(&)[]>();
        check_not_final<int[3]>();
        check_not_final<int(*)[]>();
        check_not_final<double>();
        check_not_final<char>();
        
        check_not_final<bmltb::enum_class>();
        check_not_final<bmltb::class_type>();
        check_not_final<bmltb::union_type>();
        check_not_final<bmltb::union_type[2]>();
        check_not_final<int bmltb::class_type::*>();
        check_not_final<bmltb::incomplete_class*>();
        check_not_final<bmltb::incomplete_class*[1][2]>();
        
        check_not_final<auto (*)(int) noexcept -> void>();
        check_not_final<auto (bmltb::class_type::*)() -> void>();
        check_not_final<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
        
        check_not_final<auto (int) -> void>();
        check_not_final<auto (int) const && noexcept -> void>();
        check_not_final<auto (&)(int) -> void>();
        check_not_final<auto (*&&)(int) noexcept -> void>();
    }

    return 0;
}
