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
#include "remove_reference.hpp"

namespace bml
{
    //
    // See std::remove_cvref.
    //
    template <typename T>
    struct remove_cvref { using type = remove_cv_ty<remove_reference_ty<T>>; };

    //
    // See std::remove_cvref_t, except that this is named remove_cvref_ty for POSIX compatibility.
    //
    template <typename T>
    using remove_cvref_ty = typename remove_cvref<T>::type;
}
