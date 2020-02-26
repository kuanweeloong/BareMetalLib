//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../../../bool_constant.hpp"
#include "../../../is_destructible.hpp"

namespace bml::detail::is_trivially_destructible_detail
{
    template <typename T>
    struct impl : bool_constant<is_destructible_v<T> && __has_trivial_destructor(T)> {};
}
