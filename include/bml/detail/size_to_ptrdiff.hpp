//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include <stddef.h>
#include <stdint.h>

namespace bml::detail
{
    //
    // A helper function to perform checked conversion from size_t to ptrdiff_t.
    //
    template <::size_t N>
    [[nodiscard]] constexpr auto size_to_ptrdiff() noexcept -> ::ptrdiff_t
    {
        static_assert(N <= static_cast<::size_t>(PTRDIFF_MAX), "Input is larger than PTRDIFF_MAX.");
        return static_cast<::ptrdiff_t>(N);
    }
}
