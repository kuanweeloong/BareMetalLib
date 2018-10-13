//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once

namespace bml
{
    //
    // See std::void_t, except that this is named void_ty for POSIX compatibility.
    //
    template <typename... Ts>
    using void_ty = void;
}
