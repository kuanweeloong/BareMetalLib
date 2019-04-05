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
#include "../detail/INVOKE.hpp"
#include "../type_traits/invoke_result.hpp"
#include "../utilities/forward.hpp"

namespace bml
{
    //
    // See std::invoke.
    //
    template <typename F, typename... Args>
    constexpr auto invoke(F&& f, Args&&... args) noexcept -> invoke_result_ty<F, Args...>
    {
        return detail::INVOKE(forward<F>(f), forward<Args>(args)...);
    }
}
