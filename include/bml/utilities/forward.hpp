//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../type_traits/remove_reference.hpp"
#include "../type_traits/is_lvalue_reference.hpp"

namespace bml
{
    //
    // See std::forward, except that this has been annotated with nodiscard.
    //
    template <typename T>
    [[nodiscard]] constexpr auto forward(remove_reference_ty<T>& t) noexcept -> T&&
    {
        return static_cast<T&&>(t);
    }

    template <typename T>
    [[nodiscard]] constexpr auto forward(remove_reference_ty<T>&& t) noexcept -> T&&
    {
        static_assert(!is_lvalue_reference_v<T>, "Cannot forward rvalue as lvalue.");
        return static_cast<T&&>(t);
    }
}
