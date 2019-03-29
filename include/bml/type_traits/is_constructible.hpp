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
#include "../detail/macros/compiler_specific_file.hpp"
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, is_constructible.hpp)

namespace bml
{
    //
    // See std::is_constructible.
    //
    template <typename T, typename... Args>
    struct is_constructible : detail::is_constructible_detail::impl<T, Args...> {};

    //
    // See std::is_constructible_v.
    //
    template <typename T, typename... Args>
    inline constexpr auto is_constructible_v = bool(is_constructible<T, Args...>::value);
}
