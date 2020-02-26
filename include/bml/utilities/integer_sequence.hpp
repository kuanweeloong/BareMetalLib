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
#include "../detail/size_to_ptrdiff.hpp"

namespace bml
{
    template <typename T, T... Is>
    struct integer_sequence
    {
        using value_type = T;
        
        [[nodiscard]] static constexpr auto size() noexcept -> ::ptrdiff_t
        {
            return detail::size_to_ptrdiff<sizeof...(Is)>();
        }
    };
}
