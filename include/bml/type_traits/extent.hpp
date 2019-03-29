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

#pragma once
#include <stddef.h>
#include "integral_constant.hpp"

namespace bml
{
    //
    // See std::extent, except that:
    //   1. This exposes the extent as a ptrdiff_t instead of size_t.
    //   2. N is an int instead of unsigned. If N is negative, the program is ill-formed.
    //   3. This deduces array length as ptrdiff_t instead of size_t.
    //
    template <typename T, int N = 0>
    struct extent : integral_constant<::ptrdiff_t, 0>
    {
        static_assert(N >= 0, "N cannot be negative.");
    };
    
    template <typename T>
    struct extent<T[], 0> : integral_constant<::ptrdiff_t, 0> {};
    
    template <typename T, ::ptrdiff_t Len>
    struct extent<T[Len], 0> : integral_constant<::ptrdiff_t, Len> {};
    
    template <typename T, int N>
    struct extent<T[], N> : extent<T, N - 1> {};
    
    template <typename T, int N, ::ptrdiff_t Len>
    struct extent<T[Len], N> : extent<T, N - 1> {};

    //
    // See std::extent_v, except that this is a ptrdiff_t instead of size_t, and N is int instead of
    // unsigned.
    //
    template <typename T, int N = 0>
    inline constexpr auto extent_v = ::ptrdiff_t(extent<T, N>::value);
}
