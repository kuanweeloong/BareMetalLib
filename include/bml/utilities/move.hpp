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

namespace bml
{
    template <typename T>
    [[nodiscard]] constexpr auto move(T&& t) noexcept -> remove_reference_ty<T>&&
    {
        return static_cast<remove_reference_ty<T>&&>(t);
    }
}
