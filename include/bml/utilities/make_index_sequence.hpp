//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include <stddef.h>
#include "index_sequence.hpp"
#include "make_integer_sequence.hpp"

namespace bml
{
    template <::ptrdiff_t N>
    using make_index_sequence = make_integer_sequence<::ptrdiff_t, N>;
}
