//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include <stddef.h>
#include "aligned_storage.hpp"
#include "alignment_of.hpp"
#include "size_of.hpp"
#include "../utilities/max.hpp"

namespace bml
{
    //
    // See std::aligned_union, except that Len's type is ptrdiff_t instead of size_t.
    //
    template <::ptrdiff_t Len, typename... Ts>
    struct aligned_union
    {
        static_assert(Len >= 0, "Len cannot be negative.");
        
        using type = aligned_storage_ty<bml::max(Len, size_of_v<Ts>...),
            bml::max(alignment_of_v<Ts>...)>;
    };
    
    //
    // See std::aligned_union_t, except that this is named aligned_union_ty for POSIX compatibility,
    // and Len's type is ptrdiff_t instead of size_t.
    //
    template <::ptrdiff_t Len, typename... Ts>
    using aligned_union_ty = typename aligned_union<Len, Ts...>::type;
}
