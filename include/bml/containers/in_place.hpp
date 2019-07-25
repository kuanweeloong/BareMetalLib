//
// Copyright (c) 2019 Wee Loong Kuan
//
// BareMetalLib is based on libc++ (https://libcxx.llvm.org/).
// 
// This file is licensed under under the Apache License v2.0 with LLVM Exceptions. For more details,
// see the LICENSE.md file in the top-level directory of this distribution, or copy at 
// https://llvm.org/LICENSE.txt.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once

namespace bml
{
    //
    // See std::in_place_t, except that this is named in_place_ty for POSIX compatibility.
    //
    struct in_place_ty
    {
        constexpr explicit in_place_ty() noexcept = default;
    };

    //
    // See std::in_place.
    //
    inline constexpr auto in_place = in_place_ty();
}
