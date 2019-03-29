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
#include "../../../../type_traits/is_function.hpp"
#include "../../../../type_traits/is_void.hpp"

namespace bml::detail::launder_detail
{
    template <typename T>
    [[nodiscard]] constexpr auto launder(T* p) noexcept -> T*
    {
        static_assert(!is_function_v<T>, "Cannot launder functions.");
        static_assert(!is_void_v<T>, "Cannot launder void.");

        return __builtin_launder(p);
    }
}
