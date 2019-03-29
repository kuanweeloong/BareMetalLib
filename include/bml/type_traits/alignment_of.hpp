//
// Copyright (c) 2019 Wee Loong Kuan
//
// BareMetalLib is based on libc++ (https://libcxx.llvm.org/).
// 
// This file is licensed under under the Apache License v2.0 with LLVM Exceptions. For more details,
// see the LICENSE.md file in the top-level directory of this distribution, or copy at 
// https://llvm.org/LICENSE.txt.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include <stddef.h>
#include "integral_constant.hpp"
#include "../detail/size_to_ptrdiff.hpp"

namespace bml
{
    //
    // See std::alignment_of, except that this exposes alignment as ptrdiff_t. In addition, if the
    // alignment of T is larger than the maximum value that ptrdiff_t can hold, the program is
    // ill-formed.
    //
    template <typename T>
    struct alignment_of : integral_constant<::ptrdiff_t, detail::size_to_ptrdiff<alignof(T)>()> {};

    //
    // See std::alignment_of_v, except that this exposes alignment as ptrdiff_t. In addition, if the 
    // alignment of T is larger than the maximum value that ptrdiff_t can hold, the program is
    // ill-formed.
    //
    template <typename T>
    inline constexpr auto alignment_of_v = ::ptrdiff_t(alignment_of<T>::value);
}
