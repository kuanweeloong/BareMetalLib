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
#include <stddef.h>
#include <bml/type_traits/aligned_union.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/type_traits/is_trivial.hpp>
#include <bml/type_traits/is_standard_layout.hpp>
#include <bml/utilities/max.hpp>

template <::size_t Len, typename... Ts>
auto check_result() noexcept -> void
{
    using T = typename bml::aligned_union<Len, Ts...>::type;
    
    static_assert(bml::is_same_v<bml::aligned_union_ty<Len, Ts...>, T>);
    static_assert(bml::is_trivial_v<T>);
    static_assert(bml::is_standard_layout_v<T>);
    static_assert(alignof(T) == bml::max(alignof(Ts)...));
    static_assert(sizeof(T) >= bml::max(Len, sizeof(Ts)...));
}

template <typename... Ts>
auto check_alignment_value() noexcept -> void
{
    static_assert(bml::aligned_union<1, Ts...>::alignment_value == bml::max(alignof(Ts)...));
}

struct alignas(64) aligned_64_size_10 { char c[10]; };

auto test_main() noexcept -> int
{
    // Check that the size of the result is at least the largest of Len and the size of any type in
    // Ts..., and that its alignment is equal to the largest alignment amongst the Ts... types.
    {
        // Len >= all sizeof(Ts)...
        check_result<10, char>();
        check_result<10, char[5]>();
        check_result<10, char[10]>();
        check_result<10, aligned_64_size_10>();
        
        check_result<10, char, char>();
        check_result<10, char, char, char[5]>();
        check_result<10, char, char[5], aligned_64_size_10>();
        check_result<10, char[5], char, char[10], aligned_64_size_10, char[5]>();
        
        // Len < at least one of sizeof(Ts)...
        check_result<3, char[5]>();
        check_result<3, char[10]>();
        check_result<3, aligned_64_size_10>();
        
        check_result<3, char[5], char[5]>();
        check_result<3, char, char, char[5]>();
        check_result<3, char, char[5], aligned_64_size_10>();
        check_result<3, char[5], char, char[10], aligned_64_size_10, char[5]>();
    }
    
    // Check that alignment_value contains the strictest alignment of all types in Ts....
    {
        check_alignment_value<char[5]>();
        check_alignment_value<char[10]>();
        check_alignment_value<aligned_64_size_10>();
        
        check_alignment_value<char[5], char[5]>();
        check_alignment_value<char, char, char[5]>();
        check_alignment_value<char, char[5], aligned_64_size_10>();
        check_alignment_value<char[5], char, char[10], aligned_64_size_10, char[5]>();
    }
    
    return 0;
}
