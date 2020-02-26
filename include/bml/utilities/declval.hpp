//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../type_traits/add_rvalue_reference.hpp"

namespace bml
{
    template <typename T>
    auto declval() noexcept -> add_rvalue_reference_ty<T>;
}
