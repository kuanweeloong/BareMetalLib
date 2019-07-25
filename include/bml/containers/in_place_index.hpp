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
#include <stddef.h>

namespace bml
{
    //
    // See std::in_place_index_t, except that this is named in_place_index_ty for POSIX
    // compatibility and uses ptrdiff_t instead of size_t for the index.
    //
    template <::ptrdiff_t I>
    struct in_place_index_ty
    {
        constexpr explicit in_place_index_ty() noexcept = default;
    };
    
    //
    // See std::in_place_index, except that this uses ptrdiff_t instead of size_t for the index.
    //
    template <::ptrdiff_t I>
    inline constexpr auto in_place_index = in_place_index_ty<I>();
}
