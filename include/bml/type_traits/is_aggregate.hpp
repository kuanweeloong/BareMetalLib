//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../detail/macros/compiler_specific_file.hpp"
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, is_aggregate.hpp)

namespace bml
{
    //
    // See std::is_aggregate.
    //
    template <typename T>
    struct is_aggregate : detail::is_aggregate_detail::impl<T> {};

    //
    // See std::is_aggregate_v.
    //
    template <typename T>
    inline constexpr auto is_aggregate_v = bool(is_aggregate<T>::value);
}
