//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../utilities/declval.hpp"
#include "bool_constant.hpp"
#include "is_detected.hpp"
#include "is_class.hpp"
#include "is_union.hpp"
#include "is_void.hpp"
#include "is_reference.hpp"
#include "is_null_pointer.hpp"

namespace bml
{
    namespace detail::is_function_detail
    {
        template <typename T>
        using referenced_type = T&;

        template <typename T>
        constexpr auto decay_check(T*) noexcept -> void;

        template <typename T>
        using ref_decays_to_pointer = decltype(decay_check<T>(declval<T&>()));
        
        template <typename T>
        constexpr auto check() noexcept -> bool
        {
            if constexpr (is_class_v<T> || is_union_v<T> || is_void_v<T> || is_reference_v<T>
                || is_null_pointer_v<T>)
            {
                return false;
            }
            else if constexpr (!is_detected_v<referenced_type, T>)
            {
                return true;
            }
            else if constexpr (is_detected_v<ref_decays_to_pointer, T>)
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
    // See std::is_function.
    //
    template <typename T>
    struct is_function : bool_constant<detail::is_function_detail::check<T>()> {};

    //
    // See std::is_function_v.
    //
    template <typename T>
    inline constexpr auto is_function_v = bool(is_function<T>::value);
}
