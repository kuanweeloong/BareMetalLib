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
#include <bml/type_traits/alignment_of.hpp>

template <typename T>
auto check_alignment() noexcept -> void
{
    static_assert(bml::alignment_of<T>::value == alignof(T));
    static_assert(bml::alignment_of_v<T> == alignof(T));
    
    static_assert(bml::alignment_of<T const>::value == alignof(T));
    static_assert(bml::alignment_of_v<T const> == alignof(T));
    
    static_assert(bml::alignment_of<T volatile>::value == alignof(T));
    static_assert(bml::alignment_of_v<T volatile> == alignof(T));
    
    static_assert(bml::alignment_of<T const volatile>::value == alignof(T));
    static_assert(bml::alignment_of_v<T const volatile> == alignof(T));
}

struct alignas(64) aligned64 {};

auto test_main() noexcept -> int
{
    // Check that the result is the same as the output of the alignof operator.
    {
        check_alignment<bool>();
        check_alignment<int>();
        check_alignment<int*>();
        check_alignment<int const*>();
        check_alignment<int&>();
        check_alignment<int const&>();
        check_alignment<int&&>();
        check_alignment<int(&)[]>();
        check_alignment<int[3]>();
        check_alignment<int(*)[]>();
        check_alignment<double>();
        check_alignment<char>();
        
        check_alignment<aligned64>();
        
        check_alignment<bmltb::enum_class>();
        check_alignment<bmltb::class_type>();
        check_alignment<bmltb::union_type>();
        check_alignment<bmltb::union_type[2]>();
        check_alignment<int bmltb::class_type::*>();
        check_alignment<bmltb::incomplete_class*>();
        check_alignment<bmltb::incomplete_class*[1][2]>();
        
        check_alignment<auto (*)(int) noexcept -> void>();
        check_alignment<auto (bmltb::class_type::*)() -> void>();
        check_alignment<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
        check_alignment<auto (*&&)(int) noexcept -> void>();
    }

    return 0;
}
