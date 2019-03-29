//
// Copyright (c) 2018 Wee Loong Kuan
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
    // See std::add_const.
    //
    template <typename T>
    struct add_const { using type = T const; };

    //
    // See std::add_const_t, except that this is named add_const_ty for POSIX compatibility.
    //
    template <typename T>
    using add_const_ty = typename add_const<T>::type;
}
