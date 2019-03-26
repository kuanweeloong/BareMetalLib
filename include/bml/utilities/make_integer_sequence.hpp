//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../detail/macros/compiler_specific_file.hpp"
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, make_integer_sequence.hpp)

namespace bml
{
    template <typename T, T N>
    using make_integer_sequence = detail::make_integer_sequence_detail::impl<T, N>;
}
