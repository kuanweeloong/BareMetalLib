//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "bool_constant.hpp"
#include "is_fundamental.hpp"

namespace bml
{
    //
    // See std::is_compound.
    //
    template <typename T>
    struct is_compound : bool_constant<!is_fundamental_v<T>> {};

    //
    // See std::is_compound_v.
    //
    template <typename T>
    inline constexpr auto is_compound_v = bool(is_compound<T>::value);
}
