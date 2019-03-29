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
    // See std::rank, except that this exposes rank as a ptrdiff_t instead of size_t.
    //
    template <typename T> 
    struct rank : integral_constant<::ptrdiff_t, 0> {};
    
    template <typename T>
    struct rank<T[]> : integral_constant<::ptrdiff_t, rank<T>::value + 1> {};
    
    template <typename T, ::ptrdiff_t N>
    struct rank<T[N]> : integral_constant<::ptrdiff_t, rank<T>::value + 1> {};

    //
    // See std::rank_v, except that this is a ptrdiff_t instead of size_t.
    //
    template <typename T>
    inline constexpr auto rank_v = ::ptrdiff_t(rank<T>::value);
}
