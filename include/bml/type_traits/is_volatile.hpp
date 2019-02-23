//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "true_type.hpp"
#include "false_type.hpp"

namespace bml
{
    //
    // See std::is_volatile.
    //
    template <typename T> struct is_volatile             : false_type {};
    template <typename T> struct is_volatile<T volatile> : true_type  {};

    //
    // See std::is_volatile_v.
    //
    template <typename T>
    inline constexpr auto is_volatile_v = bool(is_volatile<T>::value);
}
