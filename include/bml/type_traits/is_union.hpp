//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../detail/macros/compiler_specific_file.hpp"
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, is_union.hpp)

namespace bml
{
    //
    // See std::is_union.
    //
    template <typename T>
    struct is_union : detail::is_union_detail::impl<T>{};

    //
    // See std::is_union_v.
    //
    template <typename T>
    inline constexpr auto is_union_v = bool(is_union<T>::value);
}
