//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once

namespace bml
{
    struct in_place_ty
    {
        constexpr explicit in_place_ty() noexcept = default;
    };

    inline constexpr auto in_place = in_place_ty();
}
