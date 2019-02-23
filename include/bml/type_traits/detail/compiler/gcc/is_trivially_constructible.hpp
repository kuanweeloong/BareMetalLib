//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../../../bool_constant.hpp"
#include "../../../is_constructible.hpp"

namespace bml::detail::is_trivially_constructible_detail
{
    // GCC's __is_trivially_constructible is a bit wonky with incomplete types (e.g. it thinks that
    // arrays with unknown bounds are trivially constructible) - is_constructible_v is there to
    // catch such edge cases.
    template <typename T, typename... Args>
    struct impl : bool_constant<is_constructible_v<T, Args...>
        && __is_trivially_constructible(T, Args...)> {};
}
