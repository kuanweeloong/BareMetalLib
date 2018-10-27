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
    // See std::remove_volatile.
    //
    template <typename T> struct remove_volatile             { using type = T; };
    template <typename T> struct remove_volatile<T volatile> { using type = T; };

    //
    // See std::remove_volatile_t, except that this is named remove_volatile_ty for POSIX
    // compatibility.
    //
    template <typename T>
    using remove_volatile_ty = typename remove_volatile<T>::type;
}
