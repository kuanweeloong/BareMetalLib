//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once

namespace bml
{
    //
    // See std::enable_if.
    //
    template <bool B, typename T = void>
    struct enable_if {};
    
    template <typename T>
    struct enable_if<true, T> { using type = T; };

    //
    // See std::enable_if_t, except that this is named enable_if_ty for POSIX compatibility.
    //
    template <bool B, typename T = void>
    using enable_if_ty = typename enable_if<B, T>::type;
}
