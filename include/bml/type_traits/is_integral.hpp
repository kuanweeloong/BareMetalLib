//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../detail/macros/compiler_specific_file.hpp"
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, is_integral.hpp)
#include "remove_cv.hpp"

namespace bml
{
    template <typename T>
    struct is_integral : detail::is_integral_detail::impl<remove_cv_ty<T>> {};

    template <typename T>
    inline constexpr auto is_integral_v = bool(is_integral<T>::value);
}
