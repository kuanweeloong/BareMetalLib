//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include <stddef.h>
#include "integral_constant.hpp"
#include "../detail/size_to_ptrdiff.hpp"

namespace bml
{
    template <typename T>
    struct alignment_of : integral_constant<::ptrdiff_t, detail::size_to_ptrdiff<alignof(T)>()> {};

    template <typename T>
    inline constexpr auto alignment_of_v = ::ptrdiff_t(alignment_of<T>::value);
}
