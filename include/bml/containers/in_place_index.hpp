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

namespace bml
{
    template <::ptrdiff_t I>
    struct in_place_index_ty
    {
        constexpr explicit in_place_index_ty() noexcept = default;
    };
    
    template <::ptrdiff_t I>
    inline constexpr auto in_place_index = in_place_index_ty<I>();
}
