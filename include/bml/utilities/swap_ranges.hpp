//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once

// This function is provided by swap.hpp instead of its own header to make it much easier to
// implement the swap overload for arrays; putting it in its own header would result in a lot of
// forward declaration/circular include shenanigans.
#include "swap.hpp"
