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
