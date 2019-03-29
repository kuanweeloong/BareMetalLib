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
#include "is_trivially_constructible.hpp"

namespace bml
{
    //
    // See std::is_trivially_default_constructible.
    //
    template <typename T>
    struct is_trivially_default_constructible : is_trivially_constructible<T> {};

    //
    // See std::is_trivially_default_constructible_v.
    //
    template <typename T>
    inline constexpr auto is_trivially_default_constructible_v =
        bool(is_trivially_default_constructible<T>::value);
}
