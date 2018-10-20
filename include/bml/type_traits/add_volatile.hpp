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
    // See std::add_volatile.
    //
    template <typename T>
    struct add_volatile { using type = T volatile; };

    //
    // See std::add_volatile_t, except that this is named add_volatile_ty for POSIX compatibility.
    //
    template <typename T>
    using add_volatile_ty = typename add_volatile<T>::type;
}
