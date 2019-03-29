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
    // See std::remove_const.
    //
    template <typename T> struct remove_const          { using type = T; };
    template <typename T> struct remove_const<T const> { using type = T; };

    //
    // See std::remove_const_t, except that this is named remove_const_ty for POSIX compatibility.
    //
    template <typename T>
    using remove_const_ty = typename remove_const<T>::type;
}
