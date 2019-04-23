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
#include "../utilities/declval.hpp"
#include "decay.hpp"
#include "conditional.hpp"
#include "is_same.hpp"
#include "is_detected.hpp"

namespace bml
{
    //
    // See std::common_type, as detailed in N4659's (the C++17 final working draft)
    // [meta.trans.other].
    //
    template <typename... Ts>
    struct common_type;
    
    namespace detail::common_type_detail
    {
        // Two types.
        template <typename D1, typename D2>
        using two_types_result = decay_ty<decltype(false ? bml::declval<D1>() : bml::declval<D2>())>;
        
        template <typename D1, typename D2, bool = is_detected_v<two_types_result, D1, D2>>
        struct two_types
        {
            using type = two_types_result<D1, D2>;
        };
        
        template <typename D1, typename D2>
        struct two_types<D1, D2, false> {};
        
        // Three or more types.
        template <typename T>
        using type_mem_alias = typename T::type;
        
        template <bool HasCommonType, typename T1, typename T2, typename... Ts>
        struct gt_two_types : common_type<typename common_type<T1, T2>::type, Ts...> {};
        
        template <typename T1, typename T2, typename... Ts>
        struct gt_two_types<false, T1, T2, Ts...> {};
    }
    
    // [3.1] Case where sizeof...(Ts) == 0.
    template <>
    struct common_type<> {};
    
    // [3.2] Case where sizeof...(Ts) == 1.
    template <typename T>
    struct common_type<T> : common_type<T, T> {};
    
    // [3.3] Case where sizeof...(Ts) == 2.
    template <typename T1, typename T2>
    struct common_type<T1, T2> : conditional_ty<
        !is_same_v<T1, decay_ty<T1>> || !is_same_v<T2, decay_ty<T2>>,
        common_type<decay_ty<T1>, decay_ty<T2>>,
        detail::common_type_detail::two_types<decay_ty<T1>, decay_ty<T2>>> {};

    // [3.4] Case where sizeof...(Ts) > 2.
    template <typename T1, typename T2, typename... Ts>
    struct common_type<T1, T2, Ts...> : detail::common_type_detail::gt_two_types<
        is_detected_v<detail::common_type_detail::type_mem_alias, common_type<T1, T2>>,
        T1, T2, Ts...> {};
    
    //
    // See std::common_type_t, except that this is named common_type_ty for POSIX compatibility.
    //
    template <typename... Ts>
    using common_type_ty = typename common_type<Ts...>::type;
}
