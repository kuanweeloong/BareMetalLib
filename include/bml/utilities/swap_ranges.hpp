//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once

//
// See std::swap_ranges, except that this does not have the overload with ExecutionPolicy.
//

// This function is provided by swap.hpp.
//
// This function is placed in swap.hpp instead of its own header to make it much easier to implement
// the swap overload for arrays; putting it in its own header would result in a lot of forward
// declaration/circular include shenanigans.
#include "swap.hpp"
