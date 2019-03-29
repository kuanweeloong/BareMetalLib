//
// Copyright (c) 2019 Wee Loong Kuan
//
// BareMetalLib is based on libc++ (https://libcxx.llvm.org/).
// 
// This file is licensed under under the Apache License v2.0 with LLVM Exceptions. For more details,
// see the LICENSE.md file in the top-level directory of this distribution, or copy at 
// https://llvm.org/LICENSE.txt.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
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
