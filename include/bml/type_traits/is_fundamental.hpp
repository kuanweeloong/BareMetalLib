//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "bool_constant.hpp"
#include "is_void.hpp"
#include "is_null_pointer.hpp"
#include "is_arithmetic.hpp"

namespace bml
{
    //
    // See std::is_fundamental.
    //
    template <typename T>
    struct is_fundamental : bool_constant<is_void_v<T> || is_null_pointer_v<T>
        || is_arithmetic_v<T>> {};

    //
    // See std::is_fundamental_v.
    //
    template <typename T>
    inline constexpr auto is_fundamental_v = bool(is_fundamental<T>::value);
}
