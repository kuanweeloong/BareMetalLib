//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
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
