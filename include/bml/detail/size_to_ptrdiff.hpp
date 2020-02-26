//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include <stddef.h>
#include <stdint.h>

namespace bml::detail
{
    // A helper function to perform checked conversion from size_t to ptrdiff_t.
    template <::size_t N>
    [[nodiscard]] constexpr auto size_to_ptrdiff() noexcept -> ::ptrdiff_t
    {
        static_assert(N <= static_cast<::size_t>(PTRDIFF_MAX), "Input is larger than PTRDIFF_MAX.");
        return static_cast<::ptrdiff_t>(N);
    }
}
