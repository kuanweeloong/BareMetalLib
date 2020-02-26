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
#include "integer_sequence.hpp"

namespace bml
{
    template <::ptrdiff_t... Is>
    using index_sequence = integer_sequence<::ptrdiff_t, Is...>;
}
