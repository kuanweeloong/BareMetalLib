//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include <stddef.h>
#include "integer_sequence.hpp"

namespace bml
{
    //
    // See std::index_sequence.
    //
    template <::size_t... Is>
    using index_sequence = integer_sequence<::size_t, Is...>;
}
