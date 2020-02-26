//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "remove_const.hpp"
#include "remove_volatile.hpp"

namespace bml
{
    template <typename T>
    struct remove_cv { using type = remove_volatile_ty<remove_const_ty<T>>; };

    template <typename T>
    using remove_cv_ty = typename remove_cv<T>::type;
}
