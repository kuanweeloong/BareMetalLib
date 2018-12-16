//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once

// FIXME: Although is_default_constructible can be implemented using is_constructible, GCC needs a
// workaround to deal with arrays with unknown bounds, so is_default_constructible's implementation
// is compiler-specific for now.
#include "../detail/macros/compiler_specific_file.hpp"
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, is_default_constructible.hpp)

namespace bml
{
    //
    // See std::is_default_constructible.
    //
    template <typename T>
    struct is_default_constructible : detail::is_default_constructible_detail::impl<T> {};

    //
    // See std::is_default_constructible_v.
    //
    template <typename T>
    inline constexpr auto is_default_constructible_v = bool(is_default_constructible<T>::value);
}
