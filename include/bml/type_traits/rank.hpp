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
    template <typename T> 
    struct rank : integral_constant<::ptrdiff_t, 0> {};
    
    template <typename T>
    struct rank<T[]> : integral_constant<::ptrdiff_t, rank<T>::value + 1> {};
    
    template <typename T, ::ptrdiff_t N>
    struct rank<T[N]> : integral_constant<::ptrdiff_t, rank<T>::value + 1> {};

    template <typename T>
    inline constexpr auto rank_v = ::ptrdiff_t(rank<T>::value);
}
