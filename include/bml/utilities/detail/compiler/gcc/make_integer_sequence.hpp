//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../../../integer_sequence.hpp"

namespace bml::detail::make_integer_sequence_detail
{
    template <typename T, T N>
    using impl = integer_sequence<T, __integer_pack(N)...>;
}
