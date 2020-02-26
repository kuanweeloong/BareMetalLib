//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../type_traits/enable_if.hpp"
#include "../type_traits/is_same.hpp"

namespace bml
{
    template <typename T>
    [[nodiscard]] constexpr auto min(T const& a) noexcept -> T const&
    {
        return a;
    }

    template <typename T, typename... Ts>
    [[nodiscard]] constexpr auto min(T const& a1, T const& a2, Ts const&... an) noexcept
        -> enable_if_ty<is_same_v<T, T, Ts...>, T const&>
    {
        auto& curr_min = (a2 < a1) ? a2 : a1;
        return bml::min(curr_min, an...);
    }
}
