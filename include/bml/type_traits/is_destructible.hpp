//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "bool_constant.hpp"
#include "is_detected.hpp"
#include "is_array_of_unknown_bound.hpp"
#include "is_reference.hpp"
#include "is_function.hpp"
#include "is_void.hpp"
#include "remove_all_extents.hpp"
#include "../utilities/declval.hpp"

namespace bml
{
    namespace detail::is_destructible_detail
    {
        template <typename T>
        using destructor = decltype(declval<T&>().~T());
        
        template <typename T>
        constexpr auto check() noexcept -> bool
        {
            if constexpr (is_function_v<T> || is_void_v<T> || is_array_of_unknown_bound_v<T>)
            {
                return false;
            }
            else if constexpr (is_reference_v<T>)
            {
                // It looks like some compilers have problems with short-circuiting template
                // variables and reference types in the destructor detection metafunction (see
                // invocation of is_detected below), so this reference check is separated from the
                // destructor check.
                return true;
            }
            else if constexpr (is_detected_v<destructor, remove_all_extents_ty<T>>)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    
    //
    // See std::is_destructible.
    //
    template <typename T>
    struct is_destructible : bool_constant<detail::is_destructible_detail::check<T>()> {};

    //
    // See std::is_destructible_v.
    //
    template <typename T>
    inline constexpr auto is_destructible_v = bool(is_destructible<T>::value);
}