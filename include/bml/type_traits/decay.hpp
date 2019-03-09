//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
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
    
    //
    // See std::decay.
    //
    template <typename T>
    struct decay : decltype(detail::decay_detail::impl<T>()) {};

    //
    // See std::decay_t, except that this is named decay_ty for POSIX compatibility.
    //
    template <typename T>
    using decay_ty = typename decay<T>::type;
}
