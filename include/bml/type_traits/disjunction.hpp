//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "true_type.hpp"
#include "false_type.hpp"
#include "conditional.hpp"

namespace bml
{
    template <typename... Bs>
    struct disjunction : false_type {};
    
    template <typename B>
    struct disjunction<B> : B {};
    
    template <typename B, typename... Bs>
    struct disjunction<B, Bs...> :
        conditional_ty<bool(B::value), B, disjunction<Bs...>> {};
    
    template <typename... Bs>
    inline constexpr auto disjunction_v = bool(disjunction<Bs...>::value);
}
