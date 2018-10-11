//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once

namespace bml
{
    //
    // See std::integral_constant.
    //
    template <typename T, T Value>
    struct integral_constant
    {
        using value_type = T;
        using type = integral_constant;

        static constexpr auto value = T(Value);

        constexpr operator value_type() const noexcept               { return Value; }
        constexpr auto operator()()     const noexcept -> value_type { return Value; }
    };
}
