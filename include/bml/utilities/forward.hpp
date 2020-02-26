//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../type_traits/remove_reference.hpp"
#include "../type_traits/is_lvalue_reference.hpp"

namespace bml
{
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
