//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once

namespace bml
{
    template <typename T> struct remove_const          { using type = T; };
    template <typename T> struct remove_const<T const> { using type = T; };

    template <typename T>
    using remove_const_ty = typename remove_const<T>::type;
}
