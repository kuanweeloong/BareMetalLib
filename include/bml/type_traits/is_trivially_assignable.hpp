//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../detail/macros/compiler_specific_file.hpp"
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, is_trivially_assignable.hpp)

namespace bml
{
    //
    // See std::is_trivially_assignable.
    //
    template <typename T, typename U>
    struct is_trivially_assignable : detail::is_trivially_assignable_detail::impl<T, U> {};

    //
    // See std::is_trivially_assignable_v.
    //
    template <typename T, typename U>
    inline constexpr auto is_trivially_assignable_v = bool(is_trivially_assignable<T, U>::value);
}
