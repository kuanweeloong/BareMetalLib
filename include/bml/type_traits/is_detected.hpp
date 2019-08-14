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
#include "detected_or.hpp"
#include "nonesuch.hpp"

namespace bml
{
    //
    // See Library Fundamentals TS v3's std::experimental::is_detected, except that this is a struct
    // instead of a type alias.
    //
    template <template <typename...> typename Op, typename... Args>
    struct is_detected : detected_or<nonesuch, Op, Args...>::value_ty {};

    //
    // See Library Fundamentals TS v3's std::experimental::is_detected_v.
    //
    template <template <typename...> typename Op, typename... Args>
    inline constexpr auto is_detected_v = bool(is_detected<Op, Args...>::value);
}
