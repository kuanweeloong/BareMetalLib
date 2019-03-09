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
    // See std::type_identity.
    //
    template <typename T>
    struct type_identity
    {
        using type = T;
    };

    //
    // See std::type_identity_t, except that this is named type_identity_ty for POSIX compatibility.
    //
    template <typename T>
    using type_identity_ty = typename type_identity<T>::type;
}
