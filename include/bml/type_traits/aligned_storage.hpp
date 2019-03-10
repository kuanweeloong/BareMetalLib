//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include <stddef.h>

namespace bml
{
    //
    // See std::aligned_storage.
    //
    template <::size_t Len, ::size_t Align = alignof(::max_align_t)>
    struct aligned_storage
    {
        struct alignas(Align) type
        {
            unsigned char data[Len];
        };
    };
    
    //
    // See std::aligned_storage_t, except that this is named aligned_storage_ty for POSIX
    // compatibility.
    //
    template <::size_t Len, ::size_t Align = alignof(::max_align_t)>
    using aligned_storage_ty = typename aligned_storage<Len, Align>::type;
}
