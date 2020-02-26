//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
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
}
