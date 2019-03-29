//
// Copyright (c) 2019 Wee Loong Kuan
//
// BareMetalLib is based on libc++ (https://libcxx.llvm.org/).
// 
// This file is licensed under under the Apache License v2.0 with LLVM Exceptions. For more details,
// see the LICENSE.md file in the top-level directory of this distribution, or copy at 
// https://llvm.org/LICENSE.txt.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "true_type.hpp"
#include "false_type.hpp"
#include "conditional.hpp"

namespace bml
{
    //
    // See std::disjunction.
    //
    template <typename... Bs>
    struct disjunction : false_type {};
    
    template <typename B>
    struct disjunction<B> : B {};
    
    template <typename B, typename... Bs>
    struct disjunction<B, Bs...> :
        conditional_ty<bool(B::value), B, disjunction<Bs...>> {};
    
    //
    // See std::disjunction_v.
    //
    template <typename... Bs>
    inline constexpr auto disjunction_v = bool(disjunction<Bs...>::value);
}
