//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "remove_reference.hpp"
#include "type_identity.hpp"
#include "is_referenceable.hpp"
#include "remove_cv.hpp"
#include "is_array.hpp"
#include "remove_extent.hpp"
#include "is_function.hpp"
#include "add_pointer.hpp"

namespace bml
{
    namespace detail::decay_detail
    {
        template <typename T>
        auto impl() noexcept
        {
            using U = remove_reference_ty<T>;
            
            if constexpr (!is_referenceable_v<U>)
            {
                return type_identity<remove_cv_ty<U>>();
            }
            else if constexpr (is_array_v<U>)
            {
                return type_identity<remove_extent_ty<U>*>();
            }
            else if constexpr (is_function_v<U>)
            {
                return type_identity<add_pointer_ty<U>>();
            }
            else
            {
                return type_identity<remove_cv_ty<U>>();
            }
        };
    }

    template <typename T>
    struct decay : decltype(detail::decay_detail::impl<T>()) {};

    template <typename T>
    using decay_ty = typename decay<T>::type;
}
