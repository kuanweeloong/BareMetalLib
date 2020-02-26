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
#include BML_COMPILER_SPECIFIC_FILE(detail/compiler, has_virtual_destructor.hpp)

namespace bml
{
    template <typename T>
    struct has_virtual_destructor : detail::has_virtual_destructor_detail::impl<T> {};

    template <typename T>
    inline constexpr auto has_virtual_destructor_v = bool(has_virtual_destructor<T>::value);
}
