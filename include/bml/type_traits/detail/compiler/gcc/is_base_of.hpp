//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../../../bool_constant.hpp"

namespace bml::detail::is_base_of_detail
{
    template <typename Base, typename Derived>
    struct impl : bool_constant<__is_base_of(Base, Derived)> {};
}
