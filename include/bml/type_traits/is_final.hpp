//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../detail/macros/compiler_specific_file.hpp"
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, is_final.hpp)

namespace bml
{
    //
    // See std::is_final.
    //
    template <typename T>
    struct is_final : detail::is_final_detail::impl<T> {};

    //
    // See std::is_abstract_v.
    //
    template <typename T>
    inline constexpr auto is_final_v = bool(is_final<T>::value);
}
