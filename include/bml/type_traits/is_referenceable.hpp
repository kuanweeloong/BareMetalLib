//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "is_detected.hpp"

namespace bml
{
    namespace is_referenceable_detail
    {
        template <typename T>
        using referenced_type = T&;
    }
    
    template <typename T>
    struct is_referenceable : is_detected<is_referenceable_detail::referenced_type, T> {};
    
    template <typename T>
    inline constexpr auto is_referenceable_v = bool(is_referenceable<T>::value);
}
