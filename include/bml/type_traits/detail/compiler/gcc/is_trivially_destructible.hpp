//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../../../bool_constant.hpp"
#include "../../../is_destructible.hpp"

namespace bml::detail::is_trivially_destructible_detail
{
    template <typename T>
    struct impl : bool_constant<is_destructible_v<T> && __has_trivial_destructor(T)> {};
}
