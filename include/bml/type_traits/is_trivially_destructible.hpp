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
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, is_trivially_destructible.hpp)

namespace bml
{
    //
    // See std::is_trivially_destructible.
    //
    template <typename T>
    struct is_trivially_destructible : detail::is_trivially_destructible_detail::impl<T> {};

    //
    // See std::is_trivially_destructible_v.
    //
    template <typename T>
    inline constexpr auto is_trivially_destructible_v = bool(is_trivially_destructible<T>::value);
}
