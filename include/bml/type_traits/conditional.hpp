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
    // See std::conditional.
    //
    template <bool B, typename T, typename F>
    struct conditional { using type = T; };

    template <typename T, typename F>
    struct conditional<false, T, F> { using type = F; };

    //
    // See std::conditional_t, except that this is named conditional_ty for POSIX compatibility.
    //
    template <bool B, typename T, typename F>
    using conditional_ty = typename conditional<B, T, F>::type;
}
