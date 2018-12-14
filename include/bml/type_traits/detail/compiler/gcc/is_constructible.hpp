//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../../../bool_constant.hpp"

namespace bml::detail::is_constructible_detail
{
    template <typename T, typename... Args>
    struct impl : bool_constant<__is_constructible(T, Args...)> {};
}
