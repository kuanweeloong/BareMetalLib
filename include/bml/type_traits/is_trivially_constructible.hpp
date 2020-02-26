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
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, is_trivially_constructible.hpp)

namespace bml
{
    template <typename T, typename... Args>
    struct is_trivially_constructible
        : detail::is_trivially_constructible_detail::impl<T, Args...> {};

    template <typename T, typename... Args>
    inline constexpr auto is_trivially_constructible_v =
        bool(is_trivially_constructible<T, Args...>::value);
}
