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
#include <stddef.h>
#include "../type_traits/is_copy_constructible.hpp"
#include "../type_traits/is_trivially_copy_constructible.hpp"
#include "../type_traits/is_move_constructible.hpp"
#include "../type_traits/is_trivially_move_constructible.hpp"
#include "../type_traits/is_copy_assignable.hpp"
#include "../type_traits/is_trivially_copy_assignable.hpp"
#include "../type_traits/is_move_assignable.hpp"
#include "../type_traits/is_trivially_move_assignable.hpp"
#include "../type_traits/is_destructible.hpp"
#include "../type_traits/is_trivially_destructible.hpp"
#include "../type_traits/common_type.hpp"
#include "../type_traits/remove_cvref.hpp"
#include "../type_traits/pack_size.hpp"
#include "../type_traits/is_same.hpp"
#include "../type_traits/true_type.hpp"
#include "../type_traits/false_type.hpp"
#include "../type_traits/add_const.hpp"
#include "../type_traits/add_volatile.hpp"
#include "../type_traits/add_cv.hpp"
#include "../type_traits/enable_if.hpp"
#include "../type_traits/type_pack_element.hpp"
#include "../type_traits/is_constructible.hpp"
#include "../type_traits/conjunction.hpp"
#include "../type_traits/disjunction.hpp"
#include "../type_traits/is_void.hpp"
#include "../type_traits/is_array.hpp"
#include "../type_traits/is_reference.hpp"
#include "../type_traits/is_swappable.hpp"
#include "../utilities/move.hpp"
#include "../utilities/forward.hpp"
#include "../utilities/index_sequence.hpp"
#include "../utilities/make_index_sequence.hpp"
#include "../utilities/invoke.hpp"
#include "../utilities/launder.hpp"
#include "../utilities/new.hpp"
#include "../utilities/swap.hpp"
#include "in_place.hpp"
#include "in_place_index.hpp"

namespace bml
{
    template <typename... Ts> class variant;
    
    namespace detail::variant_detail
    {
        // Functions to determine if variant's special member functions should be trivial,
        // unavailable or "normal" (i.e. non-trivial but available) based on the traits of its
        // alternatives' special member functions.
        namespace sp_mem
        {
            enum class trait
            {
                trivial,
                normal,
                unavailable
            };
            
            template <template <typename> typename AvailCheck,
                template <typename> typename TrivialCheck,
                typename... Ts>
            constexpr auto get_trait() noexcept -> trait
            {
                if ((... || !AvailCheck<Ts>::value))
                {
                    return trait::unavailable;
                }
                else if ((... && TrivialCheck<Ts>::value))
                {
                    return trait::trivial;
                }
                else
                {
                    return trait::normal;
                }
            }
            
            // variant should be not destructible if at least one alternative is indestructible;
            // otherwise, it should be trivially destructible if all alternatives are trivially
            // destructible.
            template <typename... Ts>
            constexpr auto dtor_trait() noexcept -> trait
            {
                return sp_mem::get_trait<
                    is_destructible, is_trivially_destructible,
                    Ts...>();
            }
            
            // variant should be not copy constructible if at least one alternative is not copy
            // constructible; otherwise, it should be trivially copy constructible if all
            // alternatives are trivially copy constructible.
            template <typename... Ts>
            constexpr auto copy_ctor_trait() noexcept -> trait
            {
                return sp_mem::get_trait<
                    is_copy_constructible, is_trivially_copy_constructible,
                    Ts...>();
            }
            
            // variant should be not move constructible if at least one alternative is not move
            // constructible; otherwise, it should be trivially move constructible if all
            // alternatives are trivially move constructible.
            template <typename... Ts>
            constexpr auto move_ctor_trait() noexcept -> trait
            {
                return sp_mem::get_trait<
                    is_move_constructible, is_trivially_move_constructible,
                    Ts...>();
            }
            
            // variant should be not copy assignable if at least one alternative is not copy
            // constructible or copy assignable (copy construction is needed when assigning variants
            // that hold alternatives at different indices); otherwise, it should be trivially copy
            // assignable if all alternatives are trivially copy assignable, trivially copy
			// constructible and trivially destructible (the assignee's destructor needs to run when
			// copy assigning variants holding alternatives at different indices).
            template <typename... Ts>
            constexpr auto copy_assign_trait() noexcept -> trait
            {
                auto copy_assign = sp_mem::get_trait<
                    is_copy_assignable, is_trivially_copy_assignable,
                    Ts...>();
                
                auto copy_ctor = copy_ctor_trait<Ts...>();
                auto dtor = dtor_trait<Ts...>();
                
                if (copy_assign == trait::unavailable || copy_ctor == trait::unavailable)
                {
                    return trait::unavailable;
                }
                else if (copy_assign == trait::trivial && copy_ctor == trait::trivial
                    && dtor == trait::trivial)
                {
                    return trait::trivial;
                }
                else
                {
                    return trait::normal;
                }
            }
            
            // variant should be not move assignable if at least one alternative is not move
            // constructible or move assignable (move construction is needed when assigning variants
            // that hold alternatives at different indices); otherwise, it should be trivially move
            // assignable if all alternatives are trivially move assignable, trivivally move
			// constructible and trivially destructible (the assignee's destructor needs to run when
			// move assigning variants holding alternatives at different indices).
            template <typename... Ts>
            constexpr auto move_assign_trait() noexcept -> trait
            {
                auto move_assign = sp_mem::get_trait<
                    is_move_assignable, is_trivially_move_assignable,
                    Ts...>();
                
                auto move_ctor = move_ctor_trait<Ts...>();
                auto dtor = dtor_trait<Ts...>();
                
                if (move_assign == trait::unavailable || move_ctor == trait::unavailable)
                {
                    return trait::unavailable;
                }
                else if (move_ctor == trait::trivial && move_ctor == trait::trivial
                    && dtor == trait::trivial)
                {
                    return trait::trivial;
                }
                else
                {
                    return trait::normal;
                }
            }
        }
        
        // Visitation code.
        namespace vis
        {
            // Visitation callback that is similar to std::apply - this invokes a visitor with the
            // Is-th... alternatives of the variant storages named by Ss... as arguments.
            //
            // Note that this passes alt<T> (an internal wrapper for alternatives' values; defined
            // later) to the visitor, not the actual alternative's value - to pass values, wrap the
            // visitor with value_visitor (see below) before visiting.
            template <::ptrdiff_t... Is>
            struct callback
            {
                template <typename Visitor, typename... Ss>
                static constexpr auto apply_alts(Visitor&& v, Ss&&... ss) noexcept -> decltype(auto)
                {
                    return bml::invoke(bml::forward<Visitor>(v),
                        bml::forward<Ss>(ss).template get_alt<Is>()...);
                }
            };
            
            // Helper to invoke visitors with alternatives' values instead of their value wrappers.
            //
            // Note: Initialize this via list initialization.
            template <typename Visitor>
            struct value_visitor
            {
                Visitor&& m_visitor;
                
                template <typename... Alts>
                constexpr auto operator()(Alts&&... alts) const noexcept -> decltype(auto)
                {
                    return bml::invoke(bml::forward<Visitor>(m_visitor),
                        bml::forward<Alts>(alts).value()...);
                }
            };
            
            // Storage for visitation callbacks. Given a callback_array "c", c.at(i_1, i_2, ... ,
            // i_N) contains a callback which invokes a visitor with N variants: the first variant
            // at index i_1, and the second variant at index i_2, and so on (note that the variants
            // and visitor are fixed beforehand during instantiation of the callback).
            template <typename C, ::ptrdiff_t N>
            struct callback_array
            {
                C m_elems[N];
                
                template <typename T, typename... Ts>
                constexpr explicit callback_array(in_place_ty, T t, Ts... ts) noexcept
                    : m_elems{t, ts...} {}
                
                // Accessor which allows access via parameter pack expansion.
                constexpr auto at(::ptrdiff_t i) const noexcept -> auto&&
                {
                    return m_elems[i];
                }
                
                template <typename... Is>
                constexpr auto at(::ptrdiff_t i, ::ptrdiff_t j, Is... is) const noexcept -> auto&&
                {
                    return m_elems[i].at(j, is...);
                }
            };
            
            template <typename C>
            struct callback_array<C, 0>
            {
                // Specialization which handles visitation with no variants; this will only be used
                // to store callbacks that invokes visitors with no arguments.
                //
                // Technically this doesn't need to be a specialization; however, it feels nicer to
                // semantically separate this case from the default "visit-one-or-more-variants"
                // case.
                
                C m_callback;
                
                constexpr callback_array(C c) noexcept : m_callback(c) {}
                
                constexpr auto at() const noexcept -> auto&&
                {
                    return m_callback;
                }
            };
            
            template <typename... Cs>
            constexpr auto store_callbacks(Cs... callbacks) noexcept
            {
                using callback_type = common_type_ty<remove_cvref_ty<Cs>...>;
                
                return callback_array<callback_type, pack_size_v<Cs...>>(in_place, callbacks...);
            }
            
            // Constructs a matrix of visitation callbacks for the provided visitor. For each way to
            // index alternatives in the variant storages named by Ss..., the matrix contains a
            // callback to invoke the visitor with those alternatives' value wrappers. Note that the
            // visitor has to be well formed under invocation for all possible ways of indexing
            // alternatives. For example, if storage s0 has 2 alternatives and storage s1 has 3,
            // then the visitor has to be well formed for the following invocations (calls to 
            // forward() are omitted for brevity):
            // 
            //   invoke(visitor, s0.get_alt<0>(), s1.get_alt<0>())
            //   invoke(visitor, s0.get_alt<0>(), s1.get_alt<1>())
            //   invoke(visitor, s0.get_alt<0>(), s1.get_alt<2>())
            //   invoke(visitor, s0.get_alt<1>(), s1.get_alt<0>())
            //   invoke(visitor, s0.get_alt<1>(), s1.get_alt<1>())
            //   invoke(visitor, s0.get_alt<1>(), s1.get_alt<2>())
            // 
            template <typename Visitor, typename... Ss, ::ptrdiff_t... Is>
            constexpr auto make_callbacks(index_sequence<Is...>) noexcept
            {
                return &callback<Is...>::template apply_alts<Visitor, Ss...>;
            }
            
            template <typename Visitor>
            constexpr auto make_callbacks(index_sequence<>) noexcept
            {
                // Special case for visitation with no variants.
                auto c = &callback<>::template apply_alts<Visitor>;
                
                return callback_array<decltype(c), 0>(c);
            }
            
            template <typename Visitor, typename... Ss,
                ::ptrdiff_t... DoneIs, ::ptrdiff_t... CurrIs, typename... RemainingSeqs>
            constexpr auto make_callbacks(
                index_sequence<DoneIs...>, index_sequence<CurrIs...>, RemainingSeqs... Rs) noexcept
            {
                return vis::store_callbacks(
                    vis::make_callbacks<Visitor, Ss...>(
                        index_sequence<DoneIs..., CurrIs>(), Rs...
                    )...);
            }
            
            template <typename Visitor, typename... Ss>
            constexpr auto make_callbacks() noexcept
            {
                return vis::make_callbacks<Visitor, Ss...>(index_sequence<>(),
                    make_index_sequence<remove_cvref_ty<Ss>::num_alts>()...);
            }
            
            // Constructs an array of visitation callbacks for visiting variant storages at a fixed
            // index with the provided visitor. This requires at least one variant storage to visit,
            // and that all variant storages in Ss... have the same number of alternatives. Unlike
            // make_callbacks, the visitor only has to be well-formed under invocation for
            // alternatives at the same index. For example, if storage s0 and s1 each have 3
            // alternatives, then the visitor only has to be well formed for the following
            // invocations (calls to forward() are omitted for brevity):
            //
            //   invoke(visitor, s0.get_alt<0>(), s1.get_alt<0>())
            //   invoke(visitor, s0.get_alt<1>(), s1.get_alt<1>())
            //   invoke(visitor, s0.get_alt<2>(), s1.get_alt<2>())
            //
            template <::ptrdiff_t I, typename>
            constexpr auto repeat() noexcept -> ::ptrdiff_t { return I; }
            
            template <::ptrdiff_t I, typename Visitor, typename... Ss>
            constexpr auto make_fixed_index_callbacks() noexcept
            {
                return &callback<repeat<I, Ss>()...>::template apply_alts<Visitor, Ss...>;
            }
            
            template <typename Visitor, typename... Ss, ::ptrdiff_t... Is>
            constexpr auto make_fixed_index_callbacks(index_sequence<Is...>) noexcept
            {
                return vis::store_callbacks(
                    vis::make_fixed_index_callbacks<Is, Visitor, Ss...>()...);
            }
            
            template <typename Visitor, typename S0, typename... Ss>
            constexpr auto make_fixed_index_callbacks() noexcept
            {
                constexpr auto num_alts = remove_cvref_ty<S0>::num_alts;
                
                return vis::make_fixed_index_callbacks<Visitor, S0, Ss...>(
                    make_index_sequence<num_alts>());
            }
            
            // Storage for visitation callback matrices.
            template <typename Visitor, typename... Ss>
            inline constexpr auto vis_matrix = vis::make_callbacks<Visitor, Ss...>();
            
            template <typename Visitor, typename... Ss>
            inline constexpr auto vis_matrix_fixed_index =
                vis::make_fixed_index_callbacks<Visitor, Ss...>();
            
            // Functions for visiting alternatives in variant storages.
            template <typename Visitor, typename... Ss>
            constexpr auto visit_storage(Visitor&& v, Ss&&... ss) noexcept -> decltype(auto)
            {
                return (vis_matrix<Visitor, Ss...>.at(ss.index()...))(
                    bml::forward<Visitor>(v), bml::forward<Ss>(ss)...
                );
            }
            
            template <typename Visitor, typename... Ss>
            constexpr auto visit_storage_val(Visitor&& v, Ss&&... ss) noexcept -> decltype(auto)
            {
                return vis::visit_storage(value_visitor<Visitor>{bml::forward<Visitor>(v)},
                    bml::forward<Ss>(ss)...);
            }
            
            template <typename Visitor, typename... Ss>
            constexpr auto visit_storage_at(::ptrdiff_t i, Visitor&& v, Ss&&... ss) noexcept
                -> decltype(auto)
            {
                return (vis_matrix_fixed_index<Visitor, Ss...>.at(i))(
                    bml::forward<Visitor>(v), bml::forward<Ss>(ss)...
                );
            }
            
            template <typename Visitor, typename... Ss>
            constexpr auto visit_storage_val_at(::ptrdiff_t i, Visitor&& v, Ss&&... ss) noexcept
                -> decltype(auto)
            {
                return vis::visit_storage_at(i, value_visitor<Visitor>{bml::forward<Visitor>(v)},
                    bml::forward<Ss>(ss)...);
            }
            
            // Helper to visit values in top-level variant class using the provided visitor.
            //
            // Technically, this visitation can be done by making the main bml::variant class friend
            // visit_storage_val, and calling that from bml::visit(). However, some compilers (Clang
            // <= 8) have issues friending visit_storage_val as it is a template function with a
            // deduced return type. This is a workaround for such issues by defining a static member
            // function wrapper around visit_storage_val and making bml::variant friend the
            // containing class instead.
            //
            // TODO: Remove this once the compiler friending issue has been resolved.
            struct var_visitor
            {
                template <typename Visitor, typename... Variants>
                static constexpr auto visit(Visitor&& vis, Variants&&... vars) noexcept
                    -> decltype(auto)
                {
                    return vis::visit_storage_val(bml::forward<Visitor>(vis),
                        bml::forward<Variants>(vars).m_storage...);
                }
            };
        }
        
        // Helper dependent false type to fire static_asserts on bad instantiations/function
        // invocations.
        template <typename...> struct dependent_false : false_type {};
        
        // Wrapper to store a single alternative's value. This is needed to prevent compile errors
        // when calling placement new with addresses of cv-qualified alternatives.
        template <typename T>
        class alt
        {
            T m_value;
        
        public:
            
            template <typename... Args>
            constexpr explicit alt(in_place_ty, Args&&... args) noexcept
                : m_value(bml::forward<Args>(args)...) {}
            
            // Accessors for the alternative's value. As this class acts as storage for the
            // alternative, laundering is needed to prevent UB with const-qualified alternatives,
            // alternatives with const-qualified or reference members, etc (see clauses on re-using
            // storage in [basic.life]).
            constexpr auto value() & noexcept -> auto&&
            {
                return bml::launder(this)->m_value;
            }
            
            constexpr auto value() const & noexcept -> auto&&
            {
                return bml::launder(this)->m_value;
            }
            
            constexpr auto value() && noexcept -> auto&&
            {
                return bml::move(*bml::launder(this)).m_value;
            }
            
            constexpr auto value() const && noexcept -> auto&&
            {
                return bml::move(*bml::launder(this)).m_value;
            }
        };
        
        // Macro to mark special member functions as "do-not-declare". Used by codegen macros for
        // alt_union and storage.
        #define BML_VARIANT_FUNCTION_NOT_DECLARED
        
        // Union for alternatives.
        //
        // alt_union needs to ensure that the traits of its special member functions conform to the
        // output of the corresponding functions in the sp_mem namespace. For example, if sp_mem::
        // dtor_trait<Ts...>() yields trait::trivial, then alt_union's destructor should be trivial.
        //
        // To satisfy the requirement above, alt_union has a specialization for each combination of
        // special member function traits (i.e. it has 3^5 specializations).  Unfortunately, these
        // specializations are generated using macros. alt_union uses this approach instead of
        // adopting libc++'s approach (which is to create an inheritance hierarchy of classes that
        // each specialize on and define a single special member function based on the trait of that
        // function in the stored alternatives, while explicitly defaulting other special member
        // functions to prevent them from being unusable due to special member implicit declaration
        // rules) as the latter causes warnings to be emitted if explicitly defaulted special member
        // functions are deleted anywhere further up the inheritance hierarchy (e.g. due to an
        // alternative having that special member function deleted).
        template <sp_mem::trait DtorTrait,
            sp_mem::trait CopyCtorTrait, sp_mem::trait MoveCtorTrait,
            sp_mem::trait CopyAssignTrait, sp_mem::trait MoveAssignTrait,
            typename... Ts>
        union alt_union {};
        
        #define BML_VARIANT_ALT_UNION_SPEC(dtor_trait, dtor_def,                                  \
                copy_ctor_trait, copy_ctor_def, move_ctor_trait, move_ctor_def,                   \
                copy_assign_trait, copy_assign_def, move_assign_trait, move_assign_def)           \
            template <typename T, typename... Ts>                                                 \
            union alt_union<dtor_trait,                                                           \
                copy_ctor_trait, move_ctor_trait,                                                 \
                copy_assign_trait, move_assign_trait,                                             \
                T, Ts...>                                                                         \
            {                                                                                     \
                char m_dummy;                                                                     \
                alt<T> m_head;                                                                    \
                alt_union<dtor_trait,                                                             \
                    copy_ctor_trait, move_ctor_trait,                                             \
                    copy_assign_trait, move_assign_trait, Ts...> m_tail;                          \
                                                                                                  \
                dtor_def                                                                          \
                copy_ctor_def                                                                     \
                move_ctor_def                                                                     \
                copy_assign_def                                                                   \
                move_assign_def                                                                   \
                                                                                                  \
                /* Default constructs a dummy. This dummy allows alt_union to be default          \
                   constructed so that the actual value can be constructed via visitation in the  \
                   containing class' constructor body; the active member will be switched to the  \
                   real value once that constructor body is run. */                               \
                constexpr alt_union() noexcept : m_dummy() {}                                     \
                                                                                                  \
                /* Constructs the I-th alternative after current alternative, or the current      \
                   alternative if I == 0.*/                                                       \
                template <typename... Args>                                                       \
                constexpr explicit alt_union(in_place_index_ty<0>, Args&&... args) noexcept       \
                    : m_head(in_place, bml::forward<Args>(args)...) {}                            \
                                                                                                  \
                template <::ptrdiff_t I, typename... Args>                                        \
                constexpr explicit alt_union(in_place_index_ty<I>, Args&&... args) noexcept       \
                    : m_tail(in_place_index<I - 1>, bml::forward<Args>(args)...) {}               \
                                                                                                  \
                /* Accessor for the I-th alternative value wrapper after the current wrapper, or  \
                   the current wrapper if I == 0. */                                              \
                template <::ptrdiff_t I>                                                          \
                constexpr auto get_alt() & noexcept -> auto&&                                     \
                {                                                                                 \
                    if constexpr (I == 0) { return m_head; }                                      \
                    else                  { return m_tail.template get_alt<I - 1>(); }            \
                }                                                                                 \
                                                                                                  \
                template <::ptrdiff_t I>                                                          \
                constexpr auto get_alt() const & noexcept -> auto&&                               \
                {                                                                                 \
                    if constexpr (I == 0) { return m_head; }                                      \
                    else                  { return m_tail.template get_alt<I - 1>(); }            \
                }                                                                                 \
                                                                                                  \
                template <::ptrdiff_t I>                                                          \
                constexpr auto get_alt() && noexcept -> auto&&                                    \
                {                                                                                 \
                    if constexpr (I == 0) { return bml::move(m_head); }                           \
                    else                  { return bml::move(m_tail).template get_alt<I - 1>(); } \
                }                                                                                 \
                                                                                                  \
                template <::ptrdiff_t I>                                                          \
                constexpr auto get_alt() const && noexcept -> auto&&                              \
                {                                                                                 \
                    if constexpr (I == 0) { return bml::move(m_head); }                           \
                    else                  { return bml::move(m_tail).template get_alt<I - 1>(); } \
                }                                                                                 \
            };
        
        // Codegen macros to generate alt_union's specializations.
        #define BML_VARIANT_ALT_UNION_ADD_DTOR(...) \
            BML_VARIANT_ALT_UNION_SPEC(__VA_ARGS__)
        
        #define BML_VARIANT_ALT_UNION_ADD_COPY_CTOR(...)               \
            BML_VARIANT_ALT_UNION_ADD_DTOR(sp_mem::trait::trivial,     \
                ~alt_union() = default;,                               \
                __VA_ARGS__)                                           \
                                                                       \
            BML_VARIANT_ALT_UNION_ADD_DTOR(sp_mem::trait::unavailable, \
                ~alt_union() = delete;,                                \
                __VA_ARGS__)                                           \
                                                                       \
            BML_VARIANT_ALT_UNION_ADD_DTOR(sp_mem::trait::normal,      \
                ~alt_union() {},                                       \
                __VA_ARGS__)
        
        #define BML_VARIANT_ALT_UNION_ADD_MOVE_CTOR(...)                       \
            BML_VARIANT_ALT_UNION_ADD_COPY_CTOR(sp_mem::trait::trivial,        \
                constexpr alt_union(alt_union const&) noexcept = default;,     \
                __VA_ARGS__)                                                   \
                                                                               \
            BML_VARIANT_ALT_UNION_ADD_COPY_CTOR(sp_mem::trait::unavailable,    \
                alt_union(alt_union const&) = delete;,                         \
                __VA_ARGS__)                                                   \
                                                                               \
            BML_VARIANT_ALT_UNION_ADD_COPY_CTOR(sp_mem::trait::normal,         \
                constexpr alt_union(alt_union const&) noexcept : m_dummy() {}, \
                __VA_ARGS__)
        
        #define BML_VARIANT_ALT_UNION_ADD_COPY_ASSIGN(...)                  \
            BML_VARIANT_ALT_UNION_ADD_MOVE_CTOR(sp_mem::trait::trivial,     \
                constexpr alt_union(alt_union&&) noexcept = default;,       \
                __VA_ARGS__)                                                \
                                                                            \
            BML_VARIANT_ALT_UNION_ADD_MOVE_CTOR(sp_mem::trait::unavailable, \
                BML_VARIANT_FUNCTION_NOT_DECLARED,                          \
                __VA_ARGS__)                                                \
                                                                            \
            BML_VARIANT_ALT_UNION_ADD_MOVE_CTOR(sp_mem::trait::normal,      \
                constexpr alt_union(alt_union&&) noexcept : m_dummy() {},   \
                __VA_ARGS__)
        
        #define BML_VARIANT_ALT_UNION_ADD_MOVE_ASSIGN(...)                                    \
            BML_VARIANT_ALT_UNION_ADD_COPY_ASSIGN(sp_mem::trait::trivial,                     \
                constexpr auto operator=(alt_union const&) noexcept -> alt_union& = default;, \
                __VA_ARGS__)                                                                  \
                                                                                              \
            BML_VARIANT_ALT_UNION_ADD_COPY_ASSIGN(sp_mem::trait::unavailable,                 \
                auto operator=(alt_union const&) -> alt_union& = delete;,                     \
                __VA_ARGS__)                                                                  \
                                                                                              \
            BML_VARIANT_ALT_UNION_ADD_COPY_ASSIGN(sp_mem::trait::normal,                      \
                constexpr auto operator=(alt_union const&) noexcept -> alt_union&             \
                {                                                                             \
                    return *this;                                                             \
                },                                                                            \
                __VA_ARGS__)
        
        #define BML_VARIANT_ALT_UNION_DEFINE_SPECIALIZATIONS                                    \
            BML_VARIANT_ALT_UNION_ADD_MOVE_ASSIGN(sp_mem::trait::trivial,                       \
                constexpr auto operator=(alt_union&&) noexcept -> alt_union& = default;)        \
                                                                                                \
            BML_VARIANT_ALT_UNION_ADD_MOVE_ASSIGN(sp_mem::trait::unavailable,                   \
                BML_VARIANT_FUNCTION_NOT_DECLARED)                                              \
                                                                                                \
            BML_VARIANT_ALT_UNION_ADD_MOVE_ASSIGN(sp_mem::trait::normal,                        \
                constexpr auto operator=(alt_union&&) noexcept -> alt_union& { return *this; })
        
        BML_VARIANT_ALT_UNION_DEFINE_SPECIALIZATIONS
        
        #undef BML_VARIANT_ALT_UNION_DEFINE_SPECIALIZATIONS
        #undef BML_VARIANT_ALT_UNION_ADD_MOVE_ASSIGN
        #undef BML_VARIANT_ALT_UNION_ADD_COPY_ASSIGN
        #undef BML_VARIANT_ALT_UNION_ADD_MOVE_CTOR
        #undef BML_VARIANT_ALT_UNION_ADD_COPY_CTOR
        #undef BML_VARIANT_ALT_UNION_ADD_DTOR
        #undef BML_VARIANT_ALT_UNION_SPEC
        
        // Storage class to store and manage alternatives.
        //
        // Like alt_union, this needs to ensure that its special member functions conform to the
        // output of the corresponding functions in the sp_mem namespace, and it does this by
        // specializing on every combination of the special member function traits.
        template <sp_mem::trait DtorTrait,
            sp_mem::trait CopyCtorTrait, sp_mem::trait MoveCtorTrait,
            sp_mem::trait CopyAssignTrait, sp_mem::trait MoveAssignTrait,
            typename... Ts>
        struct storage;
        
        #define BML_VARIANT_STORAGE_SPEC(dtor_trait, destroy_alt_def, dtor_def,                    \
                copy_ctor_trait, copy_ctor_def, move_ctor_trait, move_ctor_def,                    \
                copy_assign_trait, copy_assign_def, move_assign_trait, move_assign_def)            \
            template <typename... Ts>                                                              \
            struct storage<dtor_trait, copy_ctor_trait, move_ctor_trait, copy_assign_trait,        \
                move_assign_trait, Ts...>                                                          \
            {                                                                                      \
                /* For visitation. */                                                              \
                static constexpr auto num_alts = pack_size_v<Ts...>;                               \
                                                                                                   \
                /* TODO: Optimize this to use smallest integral type that is needed to store       \
                   the number of alternatives. */                                                  \
                using index_type = ::ptrdiff_t;                                                    \
                                                                                                   \
                /* Use index() instead of this if there is a need for index to be returned as a    \
                   ptrdiff_t. */                                                                   \
                index_type m_index;                                                                \
                                                                                                   \
                alt_union<dtor_trait,                                                              \
                    copy_ctor_trait, move_ctor_trait,                                              \
                    copy_assign_trait, move_assign_trait,                                          \
                    Ts...> m_union;                                                                \
                                                                                                   \
                /* Helper function to destroy the current alternative. If the types in Ts... are   \
                not all destructible, invoking this is ill-formed. */                              \
                destroy_alt_def                                                                    \
                                                                                                   \
                dtor_def                                                                           \
                copy_ctor_def                                                                      \
                move_ctor_def                                                                      \
                copy_assign_def                                                                    \
                move_assign_def                                                                    \
                                                                                                   \
                /* In-place constructor - assumes that I is not out of bounds. */                  \
                template <::ptrdiff_t I, typename... Args>                                         \
                explicit constexpr storage(in_place_index_ty<I>, Args&&... args) noexcept          \
                    : m_index(static_cast<index_type>(I))                                          \
                    , m_union(in_place_index<I>, forward<Args>(args)...)                           \
                {}                                                                                 \
                                                                                                   \
                constexpr auto index() const noexcept -> ::ptrdiff_t                               \
                {                                                                                  \
                    return m_index;                                                                \
                }                                                                                  \
                                                                                                   \
                /* Helper function to construct an alternative into this storage, from another     \
                   storage of the same type.                                                       \
                                                                                                   \
                   Emphasis: Does not destroy the current alternative before constructing. */      \
                template <typename From>                                                           \
                auto construct_from_storage_no_destroy(From&& from) noexcept -> void               \
                {                                                                                  \
                    static_assert(is_same_v<storage, remove_cvref_ty<From>>);                      \
                                                                                                   \
                    vis::visit_storage_at(from.index(),                                            \
                        [](auto& my_alt, auto&& from_alt) noexcept                                 \
                        {                                                                          \
                            using alt_type = remove_cvref_ty<decltype(my_alt)>;                    \
                                                                                                   \
                            ::new (static_cast<void*>(&my_alt)) alt_type(in_place,                 \
                                bml::forward<decltype(from_alt)>(from_alt).value());               \
                        },                                                                         \
                        *this, bml::forward<From>(from));                                          \
                                                                                                   \
                    m_index = from.m_index;                                                        \
                }                                                                                  \
                                                                                                   \
                /* Accessor for the I-th alternative's value wrapper. */                           \
                template <::ptrdiff_t I>                                                           \
                constexpr auto get_alt() & noexcept -> auto&&                                      \
                {                                                                                  \
                    return m_union.template get_alt<I>();                                          \
                }                                                                                  \
                                                                                                   \
                template <::ptrdiff_t I>                                                           \
                constexpr auto get_alt() const & noexcept -> auto&&                                \
                {                                                                                  \
                    return m_union.template get_alt<I>();                                          \
                }                                                                                  \
                                                                                                   \
                template <::ptrdiff_t I>                                                           \
                constexpr auto get_alt() && noexcept -> auto&&                                     \
                {                                                                                  \
                    return bml::move(m_union).template get_alt<I>();                               \
                }                                                                                  \
                                                                                                   \
                template <::ptrdiff_t I>                                                           \
                constexpr auto get_alt() const && noexcept -> auto&&                               \
                {                                                                                  \
                    return bml::move(m_union).template get_alt<I>();                               \
                }                                                                                  \
                                                                                                   \
                /* Helper function to assign an alternative into this storage from another storage \
                   of the same type. If the other storage holds a different alternative, the       \
                   current alternative is destroyed and a new one constructed by copying or moving \
                   that storage's alternative. */                                                  \
                template <typename From>                                                           \
                auto assign_from_storage(From&& from) noexcept -> void                             \
                {                                                                                  \
                    static_assert(is_same_v<storage, remove_cvref_ty<From>>);                      \
                                                                                                   \
                    if (index() == from.index())                                                   \
                    {                                                                              \
                        vis::visit_storage_val_at(index(),                                         \
                            [](auto& my_val, auto&& from_val) constexpr noexcept                   \
                            {                                                                      \
                                my_val = bml::forward<decltype(from_val)>(from_val);               \
                            },                                                                     \
                            *this, bml::forward<From>(from));                                      \
                    }                                                                              \
                    else                                                                           \
                    {                                                                              \
                        destroy_alt();                                                             \
                        construct_from_storage_no_destroy(bml::forward<From>(from));               \
                    }                                                                              \
                }                                                                                  \
                                                                                                   \
                /* Assumes that I is not out of bounds. */                                         \
                template <::ptrdiff_t I, typename... Args>                                         \
                auto emplace(Args&&... args) noexcept -> auto&                                     \
                {                                                                                  \
                    destroy_alt();                                                                 \
                                                                                                   \
                    auto&& target_alt = get_alt<I>();                                              \
                    using alt_type = remove_cvref_ty<decltype(target_alt)>;                        \
                    auto result = ::new (static_cast<void*>(&target_alt)) alt_type(in_place,       \
                        bml::forward<Args>(args)...);                                              \
                                                                                                   \
                    m_index = static_cast<index_type>(I);                                          \
                                                                                                   \
                    return result->value();                                                        \
                }                                                                                  \
                                                                                                   \
                auto swap(storage& other) noexcept -> void                                         \
                {                                                                                  \
                    if (index() == other.index())                                                  \
                    {                                                                              \
                        vis::visit_storage_val_at(index(),                                         \
                            [](auto& lhs, auto& rhs) constexpr noexcept                            \
                            {                                                                      \
                                using bml::swap;                                                   \
                                swap(lhs, rhs);                                                    \
                            },                                                                     \
                            *this, other);                                                         \
                    }                                                                              \
                    else                                                                           \
                    {                                                                              \
                        auto temp = storage(bml::move(other));                                     \
                                                                                                   \
                        other.destroy_alt();                                                       \
                        other.construct_from_storage_no_destroy(bml::move(*this));                 \
                                                                                                   \
                        destroy_alt();                                                             \
                        construct_from_storage_no_destroy(bml::move(temp));                        \
                    }                                                                              \
                }                                                                                  \
            };
        
        // Codegen macros to generate storage's specializations.
        #define BML_VARIANT_STORAGE_ADD_DTOR(...) \
            BML_VARIANT_STORAGE_SPEC(__VA_ARGS__)
        
        #define BML_VARIANT_STORAGE_ADD_COPY_CTOR(...)                                           \
            BML_VARIANT_STORAGE_ADD_DTOR(sp_mem::trait::trivial,                                 \
                constexpr auto destroy_alt() noexcept -> void {},                                \
                ~storage() = default;,                                                           \
                __VA_ARGS__)                                                                     \
                                                                                                 \
            BML_VARIANT_STORAGE_ADD_DTOR(sp_mem::trait::unavailable,                             \
                constexpr auto destroy_alt() noexcept -> void                                    \
                {                                                                                \
                    static_assert(dependent_false<Ts...>::value,                                 \
                        "Cannot destroy variant with one or more indestructible alternatives."); \
                },                                                                               \
                ~storage() = delete;,                                                            \
                __VA_ARGS__)                                                                     \
                                                                                                 \
            BML_VARIANT_STORAGE_ADD_DTOR(sp_mem::trait::normal,                                  \
                constexpr auto destroy_alt() noexcept -> void                                    \
                {                                                                                \
                    vis::visit_storage([](auto& alt) constexpr noexcept                          \
                        {                                                                        \
                            using alt_type = remove_cvref_ty<decltype(alt)>;                     \
                            alt.~alt_type();                                                     \
                        },                                                                       \
                        *this);                                                                  \
                },                                                                               \
                ~storage() { destroy_alt(); },                                                   \
                __VA_ARGS__)
        
        #define BML_VARIANT_STORAGE_ADD_MOVE_CTOR(...)                    \
            BML_VARIANT_STORAGE_ADD_COPY_CTOR(sp_mem::trait::trivial,     \
                constexpr storage(storage const&) noexcept = default;,    \
                __VA_ARGS__)                                              \
                                                                          \
            BML_VARIANT_STORAGE_ADD_COPY_CTOR(sp_mem::trait::unavailable, \
                storage(storage const&) = delete;,                        \
                __VA_ARGS__)                                              \
                                                                          \
            BML_VARIANT_STORAGE_ADD_COPY_CTOR(sp_mem::trait::normal,      \
                constexpr storage(storage const& other) noexcept          \
                {                                                         \
                    construct_from_storage_no_destroy(other);             \
                },                                                        \
                __VA_ARGS__)
        
        #define BML_VARIANT_STORAGE_ADD_COPY_ASSIGN(...)                  \
            BML_VARIANT_STORAGE_ADD_MOVE_CTOR(sp_mem::trait::trivial,     \
                constexpr storage(storage&&) noexcept = default;,         \
                __VA_ARGS__)                                              \
                                                                          \
            BML_VARIANT_STORAGE_ADD_MOVE_CTOR(sp_mem::trait::unavailable, \
                BML_VARIANT_FUNCTION_NOT_DECLARED,                        \
                __VA_ARGS__)                                              \
                                                                          \
            BML_VARIANT_STORAGE_ADD_MOVE_CTOR(sp_mem::trait::normal,      \
                constexpr storage(storage&& other) noexcept               \
                {                                                         \
                    construct_from_storage_no_destroy(bml::move(other));  \
                },                                                        \
                __VA_ARGS__)
        
        #define BML_VARIANT_STORAGE_ADD_MOVE_ASSIGN(...)                                  \
            BML_VARIANT_STORAGE_ADD_COPY_ASSIGN(sp_mem::trait::trivial,                   \
                constexpr auto operator=(storage const&) noexcept -> storage& = default;, \
                __VA_ARGS__)                                                              \
                                                                                          \
            BML_VARIANT_STORAGE_ADD_COPY_ASSIGN(sp_mem::trait::unavailable,               \
                auto operator=(storage const&) -> storage& = delete;,                     \
                __VA_ARGS__)                                                              \
                                                                                          \
            BML_VARIANT_STORAGE_ADD_COPY_ASSIGN(sp_mem::trait::normal,                    \
                constexpr auto operator=(storage const& other) noexcept -> storage&       \
                {                                                                         \
                    assign_from_storage(other);                                           \
                    return *this;                                                         \
                },                                                                        \
                __VA_ARGS__)
        
        #define BML_VARIANT_STORAGE_DEFINE_SPECIALIZATIONS                           \
            BML_VARIANT_STORAGE_ADD_MOVE_ASSIGN(sp_mem::trait::trivial,              \
                constexpr auto operator=(storage&&) noexcept -> storage& = default;) \
                                                                                     \
            BML_VARIANT_STORAGE_ADD_MOVE_ASSIGN(sp_mem::trait::unavailable,          \
                BML_VARIANT_FUNCTION_NOT_DECLARED)                                   \
                                                                                     \
            BML_VARIANT_STORAGE_ADD_MOVE_ASSIGN(sp_mem::trait::normal,               \
                constexpr auto operator=(storage&& other) noexcept -> storage&       \
                {                                                                    \
                    assign_from_storage(bml::move(other));                           \
                    return *this;                                                    \
                })
        
        BML_VARIANT_STORAGE_DEFINE_SPECIALIZATIONS
        
        #undef BML_VARIANT_STORAGE_DEFINE_SPECIALIZATIONS
        #undef BML_VARIANT_STORAGE_ADD_MOVE_ASSIGN
        #undef BML_VARIANT_STORAGE_ADD_COPY_ASSIGN
        #undef BML_VARIANT_STORAGE_ADD_MOVE_CTOR
        #undef BML_VARIANT_STORAGE_ADD_COPY_CTOR
        #undef BML_VARIANT_STORAGE_ADD_DTOR
        #undef BML_VARIANT_STORAGE_SPEC
        
        #undef BML_VARIANT_FUNCTION_NOT_DECLARED
        
        // Type trait to check if a type is a variant.
        template <typename T>
        struct is_variant : false_type {};
        
        template <typename... Ts>
        struct is_variant<bml::variant<Ts...>> : true_type {};
    }
    
    //
    // See std::variant_size, except that this exposes the size as ptrdiff_t instead of size_t.
    //
    template <typename T>
    struct variant_size;
    
    template <typename T>
    struct variant_size<T const> : variant_size<T> {};
    
    template <typename T>
    struct variant_size<T volatile> : variant_size<T> {};
    
    template <typename T>
    struct variant_size<T const volatile> : variant_size<T> {};
    
    template <typename... Ts>
    struct variant_size<variant<Ts...>> : pack_size<Ts...> {};
    
    //
    // See std::variant_size_v, except that this exposes the size as ptrdiff_t instead of size_t.
    //
    template <typename T>
    inline constexpr auto variant_size_v = ::ptrdiff_t(variant_size<T>::value);
    
    //
    // See std::variant_alternative, except that this uses ptrdiff_t for the index.
    //
    template <::ptrdiff_t I, typename T>
    struct variant_alternative;
    
    template <::ptrdiff_t I, typename T>
    struct variant_alternative<I, T const>
        : add_const<typename variant_alternative<I, T>::type> {};
    
    template <::ptrdiff_t I, typename T>
    struct variant_alternative<I, T volatile>
        : add_volatile<typename variant_alternative<I, T>::type> {};
        
    template <::ptrdiff_t I, typename T>
    struct variant_alternative<I, T const volatile>
        : add_cv<typename variant_alternative<I, T>::type> {};
    
    template <::ptrdiff_t I, typename... Ts>
    struct variant_alternative<I, variant<Ts...>>
    {
        static_assert(0 <= I && I < pack_size_v<Ts...>, "variant index is out of bounds.");
        
        using type = type_pack_element_ty<I, Ts...>;
    };
    
    //
    // See std::variant_alternative_t, except that this uses ptrdiff_t for the index, and is named
    // variant_alternative_ty for POSIX compatibility.
    //
    template <::ptrdiff_t I, typename T>
    using variant_alternative_ty = typename variant_alternative<I, T>::type;
    
    //
    // A tagged union that is mostly similar to std::variant.
    //
    // This differs from std::variant in that:
    // 
    // 1. This does not support any member function overloads that take in std::initializer_list
    //    (since BML does not assume that the C++ standard library is available).
    // 2. This does not have a valueless_by_exception state, since BML is noexcept.
    //
    // There are also several features that are not yet supported, but in the pipeline to be done
    // soon (tm):
    // 
    // 1. Type-based instead of index-based construction/emplace.
    // 2. Default construction.
    // 3. Coverting constructors and assignment.
    // 4. Comparison operators.
    //
    template <typename... Ts>
    class variant
    {
    private:
    
        detail::variant_detail::storage<
            detail::variant_detail::sp_mem::dtor_trait<Ts...>(),
            detail::variant_detail::sp_mem::copy_ctor_trait<Ts...>(),
            detail::variant_detail::sp_mem::move_ctor_trait<Ts...>(),
            detail::variant_detail::sp_mem::copy_assign_trait<Ts...>(),
            detail::variant_detail::sp_mem::move_assign_trait<Ts...>(),
            Ts...> m_storage;
        
        friend struct detail::variant_detail::vis::var_visitor;
        
    public:
        
        static_assert(pack_size_v<Ts...> > 0, "variant should have at least 1 alternative.");
        static_assert(!disjunction_v<is_void<Ts>...>, "variant cannot hold void types.");
        static_assert(!disjunction_v<is_array<Ts>...>, "variant cannot hold array types.");
        static_assert(!disjunction_v<is_reference<Ts>...>, "variant cannot hold reference types.");
        
        //
        // Constructs the I-th alternative via direct-non-list-initialization with forward<Args>(
        // args).... This does not participate in overload resolution the I-th alternative is
        // constructible from Args....
        //
        template <::ptrdiff_t I, typename... Args, typename = enable_if_ty<
            (0 <= I && I < variant_size_v<variant>)
            && is_constructible_v<variant_alternative_ty<I, variant>, Args...>>>
        constexpr explicit variant(in_place_index_ty<I>, Args&&... args) noexcept
            : m_storage(in_place_index<I>, bml::forward<Args>(args)...)
        {}
        
        //
        // Destroys the currently contained value and constructs the I-th alternative via
        // direct-non-list initialization with forward<Args>(args).... This does not participate in
        // overload resolution unless the I-th alternative is constructible from Args....
        //
        template <::ptrdiff_t I, typename... Args, typename = enable_if_ty<
            is_constructible_v<variant_alternative_ty<I, variant>, Args...>>>
        auto emplace(Args&&... args) noexcept -> variant_alternative_ty<I, variant>&
        {
            return m_storage.template emplace<I>(bml::forward<Args>(args)...);
        }
        
        //
        // Gets the index of the currently stored alternative.
        //
        [[nodiscard]] constexpr auto index() const noexcept -> ::ptrdiff_t
        {
            return m_storage.index();
        }
        
        //
        // Swaps the currently contained value with the value held by the argument variant. This
        // does not participate in overload resolution unless all alternatives are swappable and
        // move-constructible.
        //
        template <bool AlwaysTrue = true, typename = enable_if_ty<AlwaysTrue
            && conjunction_v<is_swappable<Ts>...> && conjunction_v<is_move_constructible<Ts>...>>>
        auto swap(variant& other) noexcept -> void
        {
            m_storage.swap(other.m_storage);
        }
        
        //
        // Indexed accessor for the I-th alternative. Its behavior is undefined if the current index
        // is not I.
        //
        template <::ptrdiff_t I>
        [[nodiscard]] constexpr auto get() & noexcept -> variant_alternative_ty<I, variant>&
        {   
            return m_storage.template get_alt<I>().value();
        }
        
        template <::ptrdiff_t I>
        [[nodiscard]] constexpr auto get() const & noexcept
            -> variant_alternative_ty<I, variant> const&
        {
            return m_storage.template get_alt<I>().value();
        }
        
        template <::ptrdiff_t I>
        [[nodiscard]] constexpr auto get() && noexcept -> variant_alternative_ty<I, variant>&&
        {
            return bml::move(m_storage).template get_alt<I>().value();
        }
        
        template <::ptrdiff_t I>
        [[nodiscard]] constexpr auto get() const && noexcept
            -> variant_alternative_ty<I, variant> const&&
        {
            return bml::move(m_storage).template get_alt<I>().value();
        }
    };
    
    //
    // See std::visit, except that this does not participate in overload resolution unless all the
    // types in Variants... are variants.
    //
    template <typename Visitor, typename... Variants, typename = enable_if_ty<
        conjunction_v<detail::variant_detail::is_variant<remove_cvref_ty<Variants>>...>>>
    constexpr auto visit(Visitor&& vis, Variants&&... vars) noexcept -> decltype(auto)
    {
        return detail::variant_detail::vis::var_visitor::visit(bml::forward<Visitor>(vis),
            bml::forward<Variants>(vars)...);
    }
    
    //
    // See indexed std::get for variants, except that this uses ptrdiff_t for the index, and
    // behavior is undefined if v.index() is not I (since BML is noexcept).
    //
    template <::ptrdiff_t I, typename... Ts>
    constexpr auto get(variant<Ts...>& v) noexcept -> variant_alternative_ty<I, variant<Ts...>>&
    {
        return v.template get<I>();
    }
    
    template <::ptrdiff_t I, typename... Ts>
    constexpr auto get(variant<Ts...> const& v) noexcept
        -> variant_alternative_ty<I, variant<Ts...>> const&
    {
        return v.template get<I>();
    }
    
    template <::ptrdiff_t I, typename... Ts>
    constexpr auto get(variant<Ts...>&& v) noexcept -> variant_alternative_ty<I, variant<Ts...>>&&
    {
        return bml::move(v).template get<I>();
    }
    
    template <::ptrdiff_t I, typename... Ts>
    constexpr auto get(variant<Ts...> const&& v) noexcept
        -> variant_alternative_ty<I, variant<Ts...>> const&&
    {
        return bml::move(v).template get<I>();
    }
    
    //
    // See std::swap for variants.
    //
    template <typename... Ts>
    inline auto swap(variant<Ts...>& lhs, variant<Ts...> & rhs) noexcept -> decltype(lhs.swap(rhs))
    {
        lhs.swap(rhs);
    }
}
