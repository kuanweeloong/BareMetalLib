//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "remove_const.hpp"
#include "remove_volatile.hpp"

namespace bml
{
    //
    // See std::remove_cv.
    //
    template <typename T>
    struct remove_cv { using type = remove_volatile_ty<remove_const_ty<T>>; };

    //
    // See std::remove_cv_t, except that this is named remove_cv_ty for POSIX compatibility.
    //
    template <typename T>
    using remove_cv_ty = typename remove_cv<T>::type;
}
