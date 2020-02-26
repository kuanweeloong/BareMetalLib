//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "bool_constant.hpp"

namespace bml
{
    template <typename B>
    struct negation : bool_constant<!bool(B::value)> {};
    
    template <typename B>
    inline constexpr auto negation_v = bool(negation<B>::value);
}
