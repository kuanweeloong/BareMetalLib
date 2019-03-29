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

namespace bml::detail::addressof_detail
{
    template <typename T>
    [[nodiscard]] __attribute__((no_sanitize("cfi"))) constexpr auto addressof(T& arg) noexcept
        -> T*
    {
        return __builtin_addressof(arg);
    }

    template <typename T>
    auto addressof(T const&&) noexcept -> T const* = delete;
}
