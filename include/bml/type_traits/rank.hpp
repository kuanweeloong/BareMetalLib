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
    // See std::rank.
    //
    template <typename T> 
    struct rank : integral_constant<::size_t, 0> {};
    
    template <typename T>
    struct rank<T[]> : integral_constant<::size_t, rank<T>::value + 1> {};
    
    template <typename T, ::size_t N>
    struct rank<T[N]> : integral_constant<::size_t, rank<T>::value + 1> {};

    //
    // See std::rank_v.
    //
    template <typename T>
    inline constexpr auto rank_v = ::size_t(rank<T>::value);
}
