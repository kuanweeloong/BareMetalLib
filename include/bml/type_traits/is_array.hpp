//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include <stddef.h>
#include "true_type.hpp"
#include "false_type.hpp"

namespace bml
{
    //
    // See std::is_array.
    //
    template <typename T> struct is_array                   : false_type {};
    template <typename T> struct is_array<T[]>              : true_type  {};
    template <typename T, ::size_t N> struct is_array<T[N]> : true_type  {};

    //
    // See std::is_array_v.
    //
    template <typename T>
    inline constexpr auto is_array_v = bool(is_array<T>::value);
}
