//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include <stddef.h>
#include "integral_constant.hpp"

namespace bml
{
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

    template <typename T, int N = 0>
    inline constexpr auto extent_v = ::ptrdiff_t(extent<T, N>::value);
}
