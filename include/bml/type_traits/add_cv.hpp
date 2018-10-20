//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "add_const.hpp"
#include "add_volatile.hpp"

namespace bml
{
    //
    // See std::add_cv.
    //
    template <typename T>
    struct add_cv
    {
        using type = add_const_ty<add_volatile_ty<T>>;
    };

    //
    // See std::add_cv_t, except that this is named add_cv_ty for POSIX compatibility.
    //
    template <typename T>
    using add_cv_ty = typename add_cv<T>::type;
}
