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
