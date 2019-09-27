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
#include "../detail/macros/compiler_specific_file.hpp"
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, is_integral.hpp)
#include "remove_cv.hpp"

namespace bml
{
    //
    // See std::is_integral.
    //
    template <typename T>
    struct is_integral : detail::is_integral_detail::impl<remove_cv_ty<T>> {};

    //
    // See std::is_integral_v.
    //
    template <typename T>
    inline constexpr auto is_integral_v = bool(is_integral<T>::value);
}
