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
#include <bml/type_traits/is_void.hpp>

template <typename T>
auto check_void() noexcept -> void
{
    static_assert(bml::is_void<T>::value);
    static_assert(bml::is_void_v<T>);
}

template <typename T>
auto check_not_void() noexcept -> void
{
    static_assert(!bml::is_void<T>::value);
    static_assert(!bml::is_void_v<T>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is void.
    {
        check_void<void>();
        check_void<void const>();
        check_void<void volatile>();
        check_void<void const volatile>();
    }
    
    // Check that the result is false when the input is not void.
    {
        check_not_void<void*>();
        check_not_void<void const*>();
        check_not_void<void volatile*>();
        check_not_void<void const volatile*>();
        check_not_void<void* const>();
        check_not_void<void const* volatile>();
        
        check_not_void<int>();
        check_not_void<int*>();
        check_not_void<int&>();
        check_not_void<int&&>();
        check_not_void<int volatile* const>();
        check_not_void<bmltb::class_type>();
        check_not_void<int bmltb::class_type::*>();
        check_not_void<bmltb::class_type const>();
        check_not_void<bmltb::union_type[]>();
        check_not_void<bmltb::enum_class>();
        check_not_void<bmltb::incomplete_class>();
        check_not_void<bmltb::incomplete_class*[][2]>();
        check_not_void<auto (int) -> void>();
        check_not_void<auto (int) const && noexcept -> void>();
        check_not_void<auto (&)(int) -> void>();
        check_not_void<auto (*)(int) noexcept -> void>();
        check_not_void<auto (*&&)(int) noexcept -> void>();
        check_not_void<auto (bmltb::class_type::*)() -> void>();
        check_not_void<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }

    return 0;
}
