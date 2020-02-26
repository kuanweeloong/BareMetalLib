//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once

namespace bml
{
    template <typename T>
    struct type_identity
    {
        using type = T;
    };

    template <typename T>
    using type_identity_ty = typename type_identity<T>::type;
}
