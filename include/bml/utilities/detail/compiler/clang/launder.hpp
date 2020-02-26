//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
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
        static_assert(!is_function_v<T>, "Cannot launder function.");
        static_assert(!is_void_v<T>, "Cannot launder void.");
        
        // TODO: remove __has_builtin check once __builtin_launder hits clang stable.
        #if __has_builtin(__builtin_launder)
            return __builtin_launder(p);
        #else
            return p;
        #endif
    }
}
