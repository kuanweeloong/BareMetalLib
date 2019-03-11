//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include <stddef.h>
#include "aligned_storage.hpp"
#include "../utilities/max.hpp"

namespace bml
{
    //
    // See std::aligned_union.
    //
    template <::size_t Len, typename... Ts>
    struct aligned_union
    {
        using type = aligned_storage_ty<max(Len, sizeof(Ts)...), max(alignof(Ts)...)>;
    };
    
    //
    // See std::aligned_union_t, except that this is named aligned_union_ty for POSIX compatibility.
    //
    template <::size_t Len, typename... Ts>
    using aligned_union_ty = typename aligned_union<Len, Ts...>::type;
}
