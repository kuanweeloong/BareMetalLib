//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once

namespace bml
{
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
