//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "detected_or.hpp"
#include "nonesuch.hpp"

namespace bml
{
    //
    // See Library Fundamentals TS v3's std::experimental::detected_t, except that this is named
    // detected_ty for POSIX compatibility.
    //
    template <template <typename...> typename Op, typename... Args>
    using detected_ty = typename detected_or<bml::nonesuch, Op, Args...>::type;
}
