//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../detail/macros/compiler_specific_file.hpp"
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, has_virtual_destructor.hpp)

namespace bml
{
    //
    // See std::has_virtual_destructor.
    //
    template <typename T>
    struct has_virtual_destructor : detail::has_virtual_destructor_detail::impl<T> {};

    //
    // See std::has_virtual_destructor_v.
    //
    template <typename T>
    inline constexpr auto has_virtual_destructor_v = bool(has_virtual_destructor<T>::value);
}
