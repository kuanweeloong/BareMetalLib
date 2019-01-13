//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "remove_cv.hpp"
#include "true_type.hpp"
#include "false_type.hpp"

namespace bml
{
    namespace detail::is_void_detail
    {
        template <typename T>
        struct impl : false_type {};
        
        template <>
        struct impl<void> : true_type {};
    }
    
    //
    // See std::is_void.
    //
    template <typename T>
    struct is_void : detail::is_void_detail::impl<remove_cv_ty<T>>{};

    //
    // See std::is_void_v.
    //
    template <typename T>
    inline constexpr auto is_void_v = bool(is_void<T>::value);
}
