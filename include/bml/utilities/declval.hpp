//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../type_traits/add_rvalue_reference.hpp"

namespace bml
{
    //
    // See std::declval.
    //
    template <typename T>
    auto declval() noexcept -> add_rvalue_reference_ty<T>;
}
