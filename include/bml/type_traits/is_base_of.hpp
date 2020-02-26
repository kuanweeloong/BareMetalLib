//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../detail/macros/compiler_specific_file.hpp"
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, is_base_of.hpp)

namespace bml
{
    template <typename Base, typename Derived>
    struct is_base_of : detail::is_base_of_detail::impl<Base, Derived> {};

    template <typename Base, typename Derived>
    inline constexpr auto is_base_of_v = bool(is_base_of<Base, Derived>::value);
}
