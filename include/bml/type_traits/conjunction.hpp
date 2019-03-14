//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "true_type.hpp"
#include "false_type.hpp"
#include "conditional.hpp"

namespace bml
{
    //
    // See std::conjunction.
    //
    template <typename... Bs>
    struct conjunction : true_type {};
    
    template <typename B>
    struct conjunction<B> : B {};
    
    template <typename B, typename... Bs>
    struct conjunction<B, Bs...> :
        conditional_ty<bool(B::value), conjunction<Bs...>, B> {};
    
    //
    // See std::conjunction_v.
    //
    template <typename... Bs>
    inline constexpr auto conjunction_v = bool(conjunction<Bs...>::value);
}
