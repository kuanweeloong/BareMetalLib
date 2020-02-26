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
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, is_trivially_assignable.hpp)

namespace bml
{
    template <typename T, typename U>
    struct is_trivially_assignable : detail::is_trivially_assignable_detail::impl<T, U> {};

    template <typename T, typename U>
    inline constexpr auto is_trivially_assignable_v = bool(is_trivially_assignable<T, U>::value);
}
