//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../detail/macros/compiler_specific_file.hpp"
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, addressof.hpp)

namespace bml
{
    //
    // See std::addressof, except that this has been annotated with nodiscard.
    //
    using detail::addressof_detail::addressof;
}
