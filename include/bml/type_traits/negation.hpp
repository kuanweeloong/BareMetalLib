//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "bool_constant.hpp"

namespace bml
{
    //
    // See std::negation.
    //
    template <typename B>
    struct negation : bool_constant<!bool(B::value)> {};
    
    //
    // See std::negation_v.
    //
    template <typename B>
    inline constexpr auto negation_v = bool(negation<B>::value);
}
