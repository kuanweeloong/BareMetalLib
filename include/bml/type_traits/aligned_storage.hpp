//
// Copyright (c) 2018 Wee Loong Kuan
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
#include "alignment_of.hpp"

namespace bml
{
    //
    // See std::aligned_storage, except that template arguments are ptrdiff_t instead of size_t.
    //
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
    
    //
    // See std::aligned_storage_t, except that this is named aligned_storage_ty for POSIX
    // compatibility, and template arguments are ptrdiff_t instead of size_t.
    //
    template <::ptrdiff_t Len, ::ptrdiff_t Align = alignment_of_v<::max_align_t>>
    using aligned_storage_ty = typename aligned_storage<Len, Align>::type;
}
