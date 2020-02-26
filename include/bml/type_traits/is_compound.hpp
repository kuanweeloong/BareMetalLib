//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "bool_constant.hpp"
#include "is_fundamental.hpp"

namespace bml
{
    template <typename T>
    struct is_compound : bool_constant<!is_fundamental_v<T>> {};

    template <typename T>
    inline constexpr auto is_compound_v = bool(is_compound<T>::value);
}
