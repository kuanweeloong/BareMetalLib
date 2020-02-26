//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "remove_cv.hpp"

namespace bml
{
    template <typename T> struct remove_pointer                    { using type = T; };
    template <typename T> struct remove_pointer<T*>                { using type = T; };
    template <typename T> struct remove_pointer<T* const>          { using type = T; };
    template <typename T> struct remove_pointer<T* volatile>       { using type = T; };
    template <typename T> struct remove_pointer<T* const volatile> { using type = T; };

    template <typename T>
    using remove_pointer_ty = typename remove_pointer<T>::type;
}
