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
    // See std::remove_reference.
    //
    template <typename T> struct remove_reference      { using type = T; };
    template <typename T> struct remove_reference<T&>  { using type = T; };
    template <typename T> struct remove_reference<T&&> { using type = T; };

    //
    // See std::remove_reference_t, except that this is named remove_reference_ty for POSIX
    // compatibility.
    //
    template <typename T>
    using remove_reference_ty = typename remove_reference<T>::type;
}
