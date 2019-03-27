//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include <stddef.h>
#include "integral_constant.hpp"
#include "../detail/size_to_ptrdiff.hpp"

namespace bml
{
    //
    // size_of is a unary type trait with a base characteristic of integral_constant<ptrdiff_t,
    // Value>, where Value is equivalent to sizeof(T). If sizeof(T) is larger than the maximum value
    // that ptrdiff_t can hold, or if T is a type incompatible with the sizeof operator (e.g.
    // incomplete types), the program is ill-formed.
    //
    template <typename T>
    struct size_of : integral_constant<::ptrdiff_t, detail::size_to_ptrdiff<sizeof(T)>()> {};

    //
    // size_of_v is a variable template of type ptrdiff_t, whose value is equivalent to sizeof(T).
    // If sizeof(T) is larger than the maximum value that ptrdiff_t can hold, or if T is a type
    // incompatible with the sizeof operator (e.g. incomplete types), the program is ill-formed.
    //
    template <typename T>
    inline constexpr auto size_of_v = ::ptrdiff_t(size_of<T>::value);
}
