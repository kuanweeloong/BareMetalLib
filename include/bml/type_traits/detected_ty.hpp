//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "detected_or.hpp"
#include "nonesuch.hpp"

namespace bml
{
    template <template <typename...> typename Op, typename... Args>
    using detected_ty = typename detected_or<nonesuch, Op, Args...>::type;
}
