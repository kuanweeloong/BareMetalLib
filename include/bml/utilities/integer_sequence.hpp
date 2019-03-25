//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include <stddef.h>
#include "../type_traits/is_integral.hpp"

namespace bml
{
    //
    // See std::integer_sequence.
    //
    template <typename T, T... Is>
    struct integer_sequence
    {
        static_assert(is_integral_v<T>, "T is not integral.");
        
        using value_type = T;
        
        [[nodiscard]] static constexpr auto size() noexcept -> ::size_t
        {
            return sizeof...(Is);
        }
    };
}
