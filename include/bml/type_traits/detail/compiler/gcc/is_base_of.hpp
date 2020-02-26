//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../../../bool_constant.hpp"

namespace bml::detail::is_base_of_detail
{
    template <typename Base, typename Derived>
    struct impl : bool_constant<__is_base_of(Base, Derived)> {};
}
