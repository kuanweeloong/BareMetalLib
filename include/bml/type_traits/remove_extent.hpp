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
#include <stddef.h>

namespace bml
{
    //
    // See std::remove_extent.
    //
    template <typename T>                struct remove_extent       { using type = T; };
    template <typename T>                struct remove_extent<T[]>  { using type = T; };
    template <typename T, ::ptrdiff_t N> struct remove_extent<T[N]> { using type = T; };

    //
    // See std::remove_extent_t, except that this is named remove_extent_ty for POSIX compatibility.
    //
    template <typename T>
    using remove_extent_ty = typename remove_extent<T>::type;
}
