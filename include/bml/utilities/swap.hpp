//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../type_traits/enable_if.hpp"
#include "../type_traits/is_move_constructible.hpp"
#include "../type_traits/is_move_assignable.hpp"
#include "move.hpp"

namespace bml
{
    //
    // See std::swap.
    //
    template <typename T>
    constexpr auto swap(T& x, T& y) noexcept
        -> enable_if_ty<is_move_constructible_v<T> && is_move_assignable_v<T>>
    {
        T t(bml::move(x));
        x = bml::move(y);
        y = bml::move(t);
    }
}
