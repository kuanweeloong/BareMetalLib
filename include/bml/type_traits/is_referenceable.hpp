//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
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
    
    //
    // is_referenceable is a unary type trait with a base characteristic of true_type if T is a
    // referenceable type (see [defns.referenceable]); otherwise, its base characteristic is of
    // false_type.
    //
    template <typename T>
    struct is_referenceable : is_detected<is_referenceable_detail::referenced_type, T> {};
    
    //
    // is_referenceable_v is a variable template that yields true if T is a referenceable type, and
    // false otherwise.
    //
    template <typename T>
    inline constexpr auto is_referenceable_v = bool(is_referenceable<T>::value);
}
