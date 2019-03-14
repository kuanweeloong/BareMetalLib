//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
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
