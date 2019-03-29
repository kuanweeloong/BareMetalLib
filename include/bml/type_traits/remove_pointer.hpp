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
#include "remove_cv.hpp"

namespace bml
{
    //
    // See std::remove_pointer.
    //
    template <typename T> struct remove_pointer                    { using type = T; };
    template <typename T> struct remove_pointer<T*>                { using type = T; };
    template <typename T> struct remove_pointer<T* const>          { using type = T; };
    template <typename T> struct remove_pointer<T* volatile>       { using type = T; };
    template <typename T> struct remove_pointer<T* const volatile> { using type = T; };

    //
    // See std::remove_pointer_t, except that this is named remove_pointer_ty for POSIX
    // compatibility.
    //
    template <typename T>
    using remove_pointer_ty = typename remove_pointer<T>::type;
}
