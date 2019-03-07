//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../detail/macros/compiler_specific_file.hpp"
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, has_unique_object_representations.hpp)

namespace bml
{
    //
    // See std::has_unique_object_representations.
    //
    template <typename T>
    struct has_unique_object_representations :
        detail::has_unique_object_representations_detail::impl<T> {};

    //
    // See std::has_unique_object_representations_v.
    //
    template <typename T>
    inline constexpr auto has_unique_object_representations_v =
        bool(has_unique_object_representations<T>::value);
}
