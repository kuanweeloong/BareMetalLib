//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../detail/macros/compiler_specific_file.hpp"
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, is_trivial.hpp)

namespace bml
{
    //
    // See std::is_trivial.
    //
    template <typename T>
    struct is_trivial : detail::is_trivial_detail::impl<T>{};

    //
    // See std::is_trivial_v.
    //
    template <typename T>
    inline constexpr auto is_trivial_v = bool(is_trivial<T>::value);
}
