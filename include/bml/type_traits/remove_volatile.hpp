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
    template <typename T> struct remove_volatile             { using type = T; };
    template <typename T> struct remove_volatile<T volatile> { using type = T; };

    template <typename T>
    using remove_volatile_ty = typename remove_volatile<T>::type;
}
