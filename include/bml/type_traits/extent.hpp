//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include <stddef.h>
#include "integral_constant.hpp"

namespace bml
{
    //
    // See std::extent.
    //
    template <typename T, unsigned N = 0>
    struct extent : integral_constant<::size_t, 0> {};
    
    template <typename T>
    struct extent<T[], 0> : integral_constant<::size_t, 0> {};
    
    template <typename T, ::size_t Len>
    struct extent<T[Len], 0> : integral_constant<::size_t, Len> {};
    
    template <typename T, unsigned N>
    struct extent<T[], N> : extent<T, N - 1> {};
    
    template <typename T, unsigned N, ::size_t Len>
    struct extent<T[Len], N> : extent<T, N - 1> {};

    //
    // See std::extent_v.
    //
    template <typename T, unsigned N = 0>
    inline constexpr auto extent_v = ::size_t(extent<T, N>::value);
}
