//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include <stddef.h>
#include "alignment_of.hpp"

namespace bml
{
    template <::ptrdiff_t Len, ::ptrdiff_t Align = alignment_of_v<::max_align_t>>
    struct aligned_storage
    {
        static_assert(Len >= 0,   "Len cannot be negative.");
        static_assert(Align >= 0, "Alignment cannot be negative.");
        
        struct alignas(Align) type
        {
            unsigned char data[Len];
        };
    };
    
    template <::ptrdiff_t Len, ::ptrdiff_t Align = alignment_of_v<::max_align_t>>
    using aligned_storage_ty = typename aligned_storage<Len, Align>::type;
}
