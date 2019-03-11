//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../type_traits/remove_reference.hpp"

namespace bml
{
    //
    // See std::move, except that this has been annotated with nodiscard.
    //
    template <typename T>
    [[nodiscard]] constexpr auto move(T&& t) noexcept -> remove_reference_ty<T>&&
    {
        return static_cast<remove_reference_ty<T>&&>(t);
    }
}
