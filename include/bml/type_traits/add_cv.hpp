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
#include "add_const.hpp"
#include "add_volatile.hpp"

namespace bml
{
    //
    // See std::add_cv.
    //
    template <typename T>
    struct add_cv
    {
        using type = add_const_ty<add_volatile_ty<T>>;
    };

    //
    // See std::add_cv_t, except that this is named add_cv_ty for POSIX compatibility.
    //
    template <typename T>
    using add_cv_ty = typename add_cv<T>::type;
}
