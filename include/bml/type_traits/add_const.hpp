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
    // See std::add_const.
    //
    template <typename T>
    struct add_const { using type = T const; };

    //
    // See std::add_const_t, except that this is named add_const_ty for POSIX compatibility.
    //
    template <typename T>
    using add_const_ty = typename add_const<T>::type;
}
