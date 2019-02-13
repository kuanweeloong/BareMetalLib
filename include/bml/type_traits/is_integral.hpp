//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "true_type.hpp"
#include "false_type.hpp"
#include "remove_cv.hpp"

namespace bml
{
    namespace detail::is_integral_detail
    {
        template <typename T> struct impl : false_type {};
        
        // Standard integral types. 
        template <> struct impl<bool>               : true_type {};
        template <> struct impl<char>               : true_type {};
        template <> struct impl<wchar_t>            : true_type {};
        template <> struct impl<char16_t>           : true_type {};
        template <> struct impl<char32_t>           : true_type {};
        template <> struct impl<signed char>        : true_type {};
        template <> struct impl<unsigned char>      : true_type {};
        template <> struct impl<short>              : true_type {};
        template <> struct impl<unsigned short>     : true_type {};
        template <> struct impl<int>                : true_type {};
        template <> struct impl<unsigned int>       : true_type {};
        template <> struct impl<long>               : true_type {};
        template <> struct impl<unsigned long>      : true_type {};
        template <> struct impl<long long>          : true_type {};
        template <> struct impl<unsigned long long> : true_type {};
    }
    
    //
    // See std::is_integral, except that implementation-defined types are not included; such types
    // are moving targets and it's impossible to test for a missing specialization. Users should
    // specialize is_integral if they need support for such types.
    //
    template <typename T>
    struct is_integral : detail::is_integral_detail::impl<remove_cv_ty<T>> {};

    //
    // See std::is_integral_v.
    //
    template <typename T>
    inline constexpr auto is_integral_v = bool(is_integral<T>::value);
}
