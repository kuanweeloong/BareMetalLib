//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../type_traits/integral_constant.hpp"
#include "../type_traits/is_member_function_pointer.hpp"
#include "../type_traits/is_member_object_pointer.hpp"
#include "../type_traits/is_base_of.hpp"
#include "../type_traits/member_pointer_class.hpp"
#include "../type_traits/type_pack_element.hpp"
#include "../type_traits/decay.hpp"
#include "../type_traits/pack_size.hpp"
#include "../type_traits/is_reference_wrapper.hpp"
#include "../utilities/forward.hpp"

namespace bml::detail
{
    // Tag to mark that INVOKE failed (i.e. inputs were not invocable).
    struct INVOKE_failure {};
    
    namespace INVOKE_detail
    {
        template <int N>
        using bullet = integral_constant<int, N>;
        
        struct any_bullet
        {
            constexpr any_bullet(...) noexcept {};
        };
        
        template <typename F, typename T1, typename... Tn>
        constexpr auto impl(bullet<1>, F&& f, T1&& t1, Tn&&... tn) noexcept
            -> decltype((bml::forward<T1>(t1).*bml::forward<F>(f))(bml::forward<Tn>(tn)...))
        {
            return (bml::forward<T1>(t1).*bml::forward<F>(f))(bml::forward<Tn>(tn)...);
        }
        
        template <typename F, typename T1, typename... Tn>
        constexpr auto impl(bullet<2>, F&& f, T1&& t1, Tn&&... tn) noexcept
            -> decltype((bml::forward<T1>(t1).get().*bml::forward<F>(f))(bml::forward<Tn>(tn)...))
        {
            return (bml::forward<T1>(t1).get().*bml::forward<F>(f))(bml::forward<Tn>(tn)...);
        }
        
        template <typename F, typename T1, typename... Tn>
        constexpr auto impl(bullet<3>, F&& f, T1&& t1, Tn&&... tn) noexcept
            -> decltype(((*bml::forward<T1>(t1)).*bml::forward<F>(f))(bml::forward<Tn>(tn)...))
        {
            return ((*bml::forward<T1>(t1)).*bml::forward<F>(f))(bml::forward<Tn>(tn)...);
        }
        
        template <typename F, typename T>
        constexpr auto impl(bullet<4>, F&& f, T&& t) noexcept
            -> decltype(bml::forward<T>(t).*bml::forward<F>(f))
        {
            return bml::forward<T>(t).*bml::forward<F>(f);
        }
        
        template <typename F, typename T>
        constexpr auto impl(bullet<5>, F&& f, T&& t) noexcept
            -> decltype(bml::forward<T>(t).get().*bml::forward<F>(f))
        {
            return bml::forward<T>(t).get().*bml::forward<F>(f);
        }
        
        template <typename F, typename T>
        constexpr auto impl(bullet<6>, F&& f, T&& t) noexcept
            -> decltype((*bml::forward<T>(t)).*bml::forward<F>(f))
        {
            return (*bml::forward<T>(t)).*bml::forward<F>(f);
        }
        
        template <typename F, typename... ArgTypes>
        constexpr auto impl(bullet<7>, F&& f, ArgTypes&&... args) noexcept
            -> decltype(bml::forward<F>(f)(bml::forward<ArgTypes>(args)...))
        {
            return bml::forward<F>(f)(bml::forward<ArgTypes>(args)...);
        }
        
        // Default catch-all when something is not invocable
        template <typename... Ts>
        constexpr auto impl(any_bullet, Ts&&...)  noexcept -> INVOKE_failure
        {
            return INVOKE_failure();
        }
    }
    
    // Implements INVOKE as detailed in N4659's (the C++17 final working draft) [func.require],
    // except that this is also constexpr. For now, this does not support invocation via
    // reference_wrapper.
    template <typename F, typename... ArgTypes>
    constexpr auto INVOKE(F&& f, ArgTypes&&... args) noexcept -> decltype(auto)
    {
        if constexpr (is_member_function_pointer_v<decay_ty<F>> && pack_size_v<ArgTypes...> > 0)
        {
            if constexpr (is_base_of_v<member_pointer_class_ty<decay_ty<F>>,
                decay_ty<type_pack_element_ty<0, ArgTypes...>>>)
            {
                // [1.1] INVOKE(f, t1, t2, ..., tN) is equivalent to (t1.*f)(t2, ..., tN) when f is
                // a pointer to a member function of a class T and is_base_of_v<T, decay_ty<
                // decltype(t1)>> is true.
                
                return INVOKE_detail::impl(INVOKE_detail::bullet<1>(), bml::forward<F>(f),
                    bml::forward<ArgTypes>(args)...);
            }
            else if constexpr(is_reference_wrapper_v<
                decay_ty<type_pack_element_ty<0, ArgTypes...>>>)
            {
                // [1.2] INVOKE(f, t1, t2, ..., tN) is equivalent to (t1.get().*f)(t2, ..., tN) when
                // f is a pointer to a member function of a class T and decay_ty<decltype(t1)> is a
                // specialization of reference_wrapper.
                
                return INVOKE_detail::impl(INVOKE_detail::bullet<2>(), bml::forward<F>(f),
                    bml::forward<ArgTypes>(args)...);
            }
            else
            {
                // [1.3] INVOKE(f, t1, t2, ..., tN) is equivalent to ((*t1).*f)(t2, ..., tN) when f
                // is a pointer to a member function of a class T and t1 does not satisfy the
                // previous two items.
                
                return INVOKE_detail::impl(INVOKE_detail::bullet<3>(), bml::forward<F>(f),
                    bml::forward<ArgTypes>(args)...);
            }
        }
        else if constexpr (pack_size_v<ArgTypes...> == 1 && is_member_object_pointer_v<decay_ty<F>>)
        {
            if constexpr (is_base_of_v<member_pointer_class_ty<decay_ty<F>>,
                decay_ty<type_pack_element_ty<0, ArgTypes...>>>)
            {
                // [1.4] INVOKE(f, t1, t2, ..., tN) is equivalent to t1.*f when N == 1 and f is a
                // pointer to data member of a class T and is_base_of_v<T, decay_ty<decltype(t1)>>
                // is true.
                
                return INVOKE_detail::impl(INVOKE_detail::bullet<4>(), bml::forward<F>(f),
                    bml::forward<ArgTypes>(args)...);
            }
            else if constexpr (is_reference_wrapper_v<
                decay_ty<type_pack_element_ty<0, ArgTypes...>>>)
            {
                // [1.5] INVOKE(f, t1, t2, ..., tN) is equivalent to t1.get().*f when N == 1 and f
                // is a pointer to data member of a class T and decay_ty<decltype(t1)> is a
                // specialization of reference_wrapper.
                
                return INVOKE_detail::impl(INVOKE_detail::bullet<5>(), bml::forward<F>(f),
                    bml::forward<ArgTypes>(args)...);
            }
            else
            {
                // [1.6] INVOKE(f, t1, t2, ..., tN) is equivalent to (*t1).*f when N == 1 and f is a
                // pointer to data member of a class T and t1 does not satisfy the previous two
                // items.
                
                return INVOKE_detail::impl(INVOKE_detail::bullet<6>(), bml::forward<F>(f),
                    bml::forward<ArgTypes>(args)...);
            }
        }
        else
        {
            // [1.7] INVOKE(f, t1, t2, ..., tN) is equivalent to f(t1, t2, ..., tN) in all other
            // cases.
            
            return INVOKE_detail::impl(INVOKE_detail::bullet<7>(), bml::forward<F>(f),
                bml::forward<ArgTypes>(args)...);
        }
    }
}
