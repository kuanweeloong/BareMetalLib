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
#include "remove_reference.hpp"

namespace bml
{
    template <typename T>
    struct remove_cvref { using type = remove_cv_ty<remove_reference_ty<T>>; };

    template <typename T>
    using remove_cvref_ty = typename remove_cvref<T>::type;
}
