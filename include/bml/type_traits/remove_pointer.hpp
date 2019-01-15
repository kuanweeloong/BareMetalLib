//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "remove_cv.hpp"

namespace bml
{
    //
    // See std::remove_pointer.
    //
    template <typename T> struct remove_pointer                    { using type = T; };
    template <typename T> struct remove_pointer<T*>                { using type = T; };
    template <typename T> struct remove_pointer<T* const>          { using type = T; };
    template <typename T> struct remove_pointer<T* volatile>       { using type = T; };
    template <typename T> struct remove_pointer<T* const volatile> { using type = T; };

    //
    // See std::remove_pointer_t, except that this is named remove_pointer_ty for POSIX
    // compatibility.
    //
    template <typename T>
    using remove_pointer_ty = typename remove_pointer<T>::type;
}
