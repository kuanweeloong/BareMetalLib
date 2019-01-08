//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "detected_or.hpp"
#include "nonesuch.hpp"

namespace bml
{
    //
    // See Library Fundamentals TS v3's std::experimental::is_detected.
    //
    template <template <typename...> typename Op, typename... Args>
    using is_detected = typename detected_or<nonesuch, Op, Args...>::value_ty;

    //
    // See Library Fundamentals TS v3's std::experimental::is_detected_v.
    //
    template <template <typename...> typename Op, typename... Args>
    inline constexpr auto is_detected_v = bool(is_detected<Op, Args...>::value);
}
