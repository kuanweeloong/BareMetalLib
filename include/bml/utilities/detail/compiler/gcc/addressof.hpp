//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once

namespace bml::detail::addressof_detail
{
    template <typename T>
    [[nodiscard]] constexpr auto addressof(T& arg) noexcept -> T*
    {
        return __builtin_addressof(arg);
    }

    template <typename T>
    auto addressof(T const&&) noexcept -> T* = delete;
}
