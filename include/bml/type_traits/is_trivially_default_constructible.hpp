//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "is_trivially_constructible.hpp"

namespace bml
{
    template <typename T>
    struct is_trivially_default_constructible : is_trivially_constructible<T> {};

    template <typename T>
    inline constexpr auto is_trivially_default_constructible_v =
        bool(is_trivially_default_constructible<T>::value);
}
