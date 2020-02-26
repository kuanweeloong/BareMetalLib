//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../type_traits/enable_if.hpp"
#include "../type_traits/is_same.hpp"
#include "../type_traits/remove_cvref.hpp"
#include "../type_traits/invoke_result.hpp"
#include "invoke.hpp"
#include "declval.hpp"
#include "forward.hpp"
#include "addressof.hpp"

namespace bml
{
    template <typename T>
    class reference_wrapper
    {
    private:
    
        T* m_ptr;
        
        static constexpr auto FUN(T&) noexcept -> void {}
        static constexpr auto FUN(T&&) noexcept = delete;
        
        static constexpr auto convert(T& t) noexcept -> T& { return t; }
        
    public:
        
        using type = T;
        
        template <typename U,
            typename = enable_if_ty<!is_same_v<remove_cvref_ty<U>, reference_wrapper>>,
            typename = decltype(FUN(bml::declval<U>()))>
        constexpr reference_wrapper(U&& u) noexcept
            : m_ptr(bml::addressof(convert(bml::forward<U>(u))))
        {}
        
        constexpr reference_wrapper(reference_wrapper const& other) noexcept = default;
        constexpr auto operator=(reference_wrapper const& other) noexcept -> reference_wrapper&
            = default;
        
        constexpr operator T&() const noexcept { return *m_ptr; }
        constexpr auto get() const noexcept -> T& { return *m_ptr; }
        
        template <typename... Args>
        constexpr auto operator()(Args&&... args) const noexcept -> invoke_result_ty<T&, Args...>
        {
            return bml::invoke(get(), bml::forward<Args>(args)...);
        }
    };
    
    template <typename T>
    reference_wrapper(T&) -> reference_wrapper<T>;
}
