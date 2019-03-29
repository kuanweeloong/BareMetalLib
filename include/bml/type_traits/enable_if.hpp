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

namespace bml
{
    //
    // See std::enable_if.
    //
    template <bool B, typename T = void>
    struct enable_if {};
    
    template <typename T>
    struct enable_if<true, T> { using type = T; };

    //
    // See std::enable_if_t, except that this is named enable_if_ty for POSIX compatibility.
    //
    template <bool B, typename T = void>
    using enable_if_ty = typename enable_if<B, T>::type;
}
