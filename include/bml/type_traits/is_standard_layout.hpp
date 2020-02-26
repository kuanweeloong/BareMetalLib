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
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, is_standard_layout.hpp)

namespace bml
{
    template <typename T>
    struct is_standard_layout : detail::is_standard_layout_detail::impl<T> {};

    template <typename T>
    inline constexpr auto is_standard_layout_v = bool(is_standard_layout<T>::value);
}
