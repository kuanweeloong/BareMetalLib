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
    // See std::alignment_of.
    //
    template <typename T>
    struct alignment_of : integral_constant<::size_t, alignof(T)> {};

    //
    // See std::alignment_of_v.
    //
    template <typename T>
    inline constexpr auto alignment_of_v = ::size_t(alignment_of<T>::value);
}
