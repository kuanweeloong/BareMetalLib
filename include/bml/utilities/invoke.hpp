//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../detail/INVOKE.hpp"
#include "../type_traits/invoke_result.hpp"
#include "../utilities/forward.hpp"

namespace bml
{
    template <typename F, typename... Args>
    constexpr auto invoke(F&& f, Args&&... args) noexcept -> invoke_result_ty<F, Args...>
    {
        return detail::INVOKE(bml::forward<F>(f), bml::forward<Args>(args)...);
    }
}
