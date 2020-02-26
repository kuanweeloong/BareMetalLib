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
#include "aligned_storage.hpp"
#include "alignment_of.hpp"
#include "size_of.hpp"
#include "../utilities/max.hpp"

namespace bml
{
    template <::ptrdiff_t Len, typename... Ts>
    struct aligned_union
    {
        static_assert(Len >= 0, "Len cannot be negative.");
        
        static constexpr auto alignment_value = ::ptrdiff_t(bml::max(alignment_of_v<Ts>...));
        using type = aligned_storage_ty<bml::max(Len, size_of_v<Ts>...), alignment_value>;
    };
    
    template <::ptrdiff_t Len, typename... Ts>
    using aligned_union_ty = typename aligned_union<Len, Ts...>::type;
}
