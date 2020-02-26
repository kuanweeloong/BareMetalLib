//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../basic_types/nullptr_ty.hpp"
#include "is_same.hpp"
#include "remove_cv.hpp"

namespace bml
{
    template <typename T>
    struct is_null_pointer : is_same<nullptr_ty, remove_cv_ty<T>> {};

    template <typename T>
    inline constexpr auto is_null_pointer_v = bool(is_null_pointer<T>::value);
}
