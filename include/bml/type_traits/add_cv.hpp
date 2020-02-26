//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "add_const.hpp"
#include "add_volatile.hpp"

namespace bml
{
    template <typename T>
    struct add_cv
    {
        using type = add_const_ty<add_volatile_ty<T>>;
    };

    template <typename T>
    using add_cv_ty = typename add_cv<T>::type;
}
