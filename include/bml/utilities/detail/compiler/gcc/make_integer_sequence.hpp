//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../../../integer_sequence.hpp"

namespace bml::detail::make_integer_sequence_detail
{
    template <typename T, T N>
    using impl = integer_sequence<T, __integer_pack(N)...>;
}
