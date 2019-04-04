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
    // If T is a pointer to a member of a class C, this provides a member type alias "type" which
    // names C. Otherwise, there is no member type alias "type".
    //
    template <typename T>
    struct member_pointer_class {};
    
    template <typename C, typename T>
    struct member_pointer_class<T C::*>
    {
        using type = C;
    };
    
    //
    // This is a helper type alias for member_pointer_class<T>::type.
    //
    template <typename T>
    using member_pointer_class_ty = typename member_pointer_class<T>::type;
}
