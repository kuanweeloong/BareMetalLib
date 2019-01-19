//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "is_constructible.hpp"

namespace bml
{
    //
    // See std::is_default_constructible.
    //
    template <typename T>
    struct is_default_constructible : is_constructible<T> {};

    //
    // See std::is_default_constructible_v.
    //
    template <typename T>
    inline constexpr auto is_default_constructible_v = bool(is_default_constructible<T>::value);
}
