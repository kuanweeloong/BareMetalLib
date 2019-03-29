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
    // See std::remove_all_extents.
    //
    template <typename T>
    struct remove_all_extents { using type = T; };
    
    template <typename T>
    struct remove_all_extents<T[]> { using type = typename remove_all_extents<T>::type; };
    
    template <typename T, ::ptrdiff_t N>
    struct remove_all_extents<T[N]> { using type = typename remove_all_extents<T>::type; };

    //
    // See std::remove_all_extents_t, except that this is named remove_all_extents_ty for POSIX
    // compatibility.
    //
    template <typename T>
    using remove_all_extents_ty = typename remove_all_extents<T>::type;
}
