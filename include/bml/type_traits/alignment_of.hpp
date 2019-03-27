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
    // See std::alignment_of, except that this exposes alignment as ptrdiff_t.
    //
    template <typename T>
    struct alignment_of : integral_constant<::ptrdiff_t, detail::size_to_ptrdiff<alignof(T)>()> {};

    //
    // See std::alignment_of_v, except that this exposes alignment as ptrdiff_t.
    //
    template <typename T>
    inline constexpr auto alignment_of_v = ::ptrdiff_t(alignment_of<T>::value);
}
