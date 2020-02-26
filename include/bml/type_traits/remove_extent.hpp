//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include <stddef.h>

namespace bml
{
    template <typename T>                struct remove_extent       { using type = T; };
    template <typename T>                struct remove_extent<T[]>  { using type = T; };
    template <typename T, ::ptrdiff_t N> struct remove_extent<T[N]> { using type = T; };

    template <typename T>
    using remove_extent_ty = typename remove_extent<T>::type;
}
