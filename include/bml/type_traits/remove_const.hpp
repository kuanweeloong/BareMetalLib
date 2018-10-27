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
    // See std::remove_const.
    //
    template <typename T> struct remove_const          { using type = T; };
    template <typename T> struct remove_const<T const> { using type = T; };

    //
    // See std::remove_const_t, except that this is named remove_const_ty for POSIX compatibility.
    //
    template <typename T>
    using remove_const_ty = typename remove_const<T>::type;
}
