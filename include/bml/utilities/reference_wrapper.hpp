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
    //
    // See std::reference_wrapper.
    //
    template <typename T>
    class reference_wrapper
    {
    private:
    
        T* m_ptr;
        
        static constexpr auto FUN(T&) noexcept -> void {}
        static constexpr auto FUN(T&&) noexcept = delete;
        
        static constexpr auto convert(T& t) noexcept -> T& { return t; }
        
    public:
        
        //
        // Type alias which names the type being referenced.
        //
        using type = T;
        
        //
        // Constructs a reference_wrapper. This does not participate in overload resolution if the
        // argument is also a reference_wrapper wrapping the same type, or if the argument is not
        // implicitly convertiable to T&, or if the argument is a temporary.
        //
        template <typename U,
            typename = enable_if_ty<!is_same_v<remove_cvref_ty<U>, reference_wrapper>>,
            typename = decltype(FUN(bml::declval<U>()))>
        constexpr reference_wrapper(U&& u) noexcept
            : m_ptr(bml::addressof(convert(bml::forward<U>(u))))
        {}
        
        //
        // Copy construction and assignment.
        //
        constexpr reference_wrapper(reference_wrapper const& other) = default;
        constexpr auto operator=(reference_wrapper const& other) -> reference_wrapper& = default;
        
        //
        // Provides access to the stored reference.
        //
        constexpr operator T&() const noexcept { return *m_ptr; }
        constexpr auto get() const noexcept -> T& { return *m_ptr; }
        
        //
        // Invokes the stored reference with the provided arguments.
        //
        template <typename... Args>
        constexpr auto operator()(Args&&... args) const noexcept -> invoke_result_ty<T&, Args...>
        {
            return bml::invoke(get(), bml::forward<Args>(args)...);
        }
    };
    
    template <typename T>
    reference_wrapper(T&) -> reference_wrapper<T>;
}
