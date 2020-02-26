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
    template <typename T>
    struct remove_all_extents { using type = T; };
    
    template <typename T>
    struct remove_all_extents<T[]> { using type = typename remove_all_extents<T>::type; };
    
    template <typename T, ::ptrdiff_t N>
    struct remove_all_extents<T[N]> { using type = typename remove_all_extents<T>::type; };

    template <typename T>
    using remove_all_extents_ty = typename remove_all_extents<T>::type;
}
