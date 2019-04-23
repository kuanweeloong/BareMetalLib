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
#include <stddef.h>
#include "integer_sequence.hpp"

namespace bml
{
    //
    // See std::index_sequence, except that this uses ptrdiff_t instead of size_t for the underlying
    // integer type.
    //
    template <::ptrdiff_t... Is>
    using index_sequence = integer_sequence<::ptrdiff_t, Is...>;
}
