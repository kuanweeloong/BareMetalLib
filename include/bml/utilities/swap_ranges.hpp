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

//
// See std::swap_ranges, except that this does not have the overload with ExecutionPolicy.
//

// This function is provided by swap.hpp.
//
// This function is placed in swap.hpp instead of its own header to make it much easier to implement
// the swap overload for arrays; putting it in its own header would result in a lot of forward
// declaration/circular include shenanigans.
#include "swap.hpp"
