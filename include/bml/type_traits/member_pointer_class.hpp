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
    struct member_pointer_class {};
    
    template <typename C, typename T>
    struct member_pointer_class<T C::*>
    {
        using type = C;
    };
    
    template <typename T>
    using member_pointer_class_ty = typename member_pointer_class<T>::type;
}
