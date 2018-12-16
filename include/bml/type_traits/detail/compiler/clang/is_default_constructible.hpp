//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../../../is_constructible.hpp"

namespace bml::detail::is_default_constructible_detail
{
    template <typename T>
    struct impl : is_constructible<T> {};
}
