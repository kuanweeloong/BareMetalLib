//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../../../bool_constant.hpp"

namespace bml::detail::has_virtual_destructor_detail
{
    template <typename T>
    struct impl : bool_constant<__has_virtual_destructor(T)> {};
}
