//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "integral_constant.hpp"

namespace bml
{
    //
    // See std::bool_constant.
    //
    template <bool B>
    using bool_constant = integral_constant<bool, B>;
}
