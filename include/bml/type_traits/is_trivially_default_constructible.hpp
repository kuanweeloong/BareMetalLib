//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "is_trivially_constructible.hpp"

namespace bml
{
    //
    // See std::is_trivially_default_constructible.
    //
    template <typename T>
    struct is_trivially_default_constructible : is_trivially_constructible<T> {};

    //
    // See std::is_trivially_default_constructible_v.
    //
    template <typename T>
    inline constexpr auto is_trivially_default_constructible_v =
        bool(is_trivially_default_constructible<T>::value);
}
