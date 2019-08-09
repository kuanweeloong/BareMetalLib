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
#include "../detail/size_to_ptrdiff.hpp"

namespace bml
{
    //
    // See std::integer_sequence.
    //
    template <typename T, T... Is>
    struct integer_sequence
    {
        using value_type = T;
        
        [[nodiscard]] static constexpr auto size() noexcept -> ::ptrdiff_t
        {
            return detail::size_to_ptrdiff<sizeof...(Is)>();
        }
    };
}
