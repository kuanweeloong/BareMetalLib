//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "true_type.hpp"
#include "false_type.hpp"

namespace bml
{
    template <typename T> struct is_const          : false_type {};
    template <typename T> struct is_const<T const> : true_type  {};

    template <typename T>
    inline constexpr auto is_const_v = bool(is_const<T>::value);
}
