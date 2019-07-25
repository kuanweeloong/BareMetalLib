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

#include <bml_testbench.hpp>
#include <bml/type_traits.hpp>

template <typename... Ts>
using ToInt = int;

auto test_main() noexcept -> int
{
    // Check that add_const is available.
    {
        static_assert(sizeof(bml::add_const<int>) > 0);
        static_assert(sizeof(bml::add_const_ty<int>) > 0);
    }
    
    // Check that add_cv is available.
    {
        static_assert(sizeof(bml::add_cv<int>) > 0);
        static_assert(sizeof(bml::add_cv_ty<int>) > 0);
    }
    
    // Check that add_lvalue_reference is available.
    {
        static_assert(sizeof(bml::add_lvalue_reference<int>) > 0);
        static_assert(sizeof(bml::add_lvalue_reference_ty<int>) > 0);
    }
    
    // Check that add_pointer is available.
    {
        static_assert(sizeof(bml::add_pointer<int>) > 0);
        static_assert(sizeof(bml::add_pointer_ty<int>) > 0);
    }
    
    // Check that add_rvalue_reference is available.
    {
        static_assert(sizeof(bml::add_rvalue_reference<int>) > 0);
        static_assert(sizeof(bml::add_rvalue_reference_ty<int>) > 0);
    }
    
    // Check that add_volatile is available.
    {
        static_assert(sizeof(bml::add_volatile<int>) > 0);
        static_assert(sizeof(bml::add_volatile_ty<int>) > 0);
    }
    
    // Check that aligned_storage is available.
    {
        static_assert(sizeof(bml::aligned_storage<8>) > 0);
        static_assert(sizeof(bml::aligned_storage_ty<8>) > 0);
    }
    
    // Check that aligned_union is available.
    {
        static_assert(sizeof(bml::aligned_union<4, int, char>) > 0);
        static_assert(sizeof(bml::aligned_union_ty<4, int, char>) > 0);
    }
    
    // Check that alignment_of is available.
    {
        static_assert(sizeof(bml::alignment_of<int>) > 0);
        static_cast<void>(bml::alignment_of_v<int>);
    }
    
    // Check that bool_constant is available.
    {
        static_assert(sizeof(bml::bool_constant<true>) > 0);
    }
    
    // Check that common_type is available.
    {
        static_assert(sizeof(bml::common_type<int, int>) > 0);
        static_assert(sizeof(bml::common_type_ty<int, int>) > 0);
    }
    
    // Check that conditional is available.
    {
        static_assert(sizeof(bml::conditional<true, int, char>) > 0);
        static_assert(sizeof(bml::conditional_ty<true, int, char>) > 0);
    }
    
    // Check that conjunction is available.
    {
        static_assert(sizeof(bml::conjunction<bml::bool_constant<true>>) > 0);
        static_cast<void>(bml::conjunction_v<bml::bool_constant<true>>);
    }
    
    // Check that decay is available.
    {
        static_assert(sizeof(bml::decay<int>) > 0);
        static_assert(sizeof(bml::decay_ty<int>) > 0);
    }
    
    // Check that detected_or is available.
    {
        static_assert(sizeof(bml::detected_or<void, ToInt, char>) > 0);
        static_assert(sizeof(bml::detected_or_ty<void, ToInt, char>) > 0);
    }
    
    // Check that detected_ty is available.
    {
        static_assert(sizeof(bml::detected_ty<ToInt, char>) > 0);
    }
    
    // Check that disjunction is available.
    {
        static_assert(sizeof(bml::disjunction<bml::bool_constant<false>>) > 0);
        static_cast<void>(bml::disjunction_v<bml::bool_constant<false>>);
    }
    
    // Check that enable_if is available.
    {
        static_assert(sizeof(bml::enable_if<true, int>) > 0);
        static_assert(sizeof(bml::enable_if_ty<true, int>) > 0);
    }
    
    // Check that extent is available.
    {
        static_assert(sizeof(bml::extent<int>) > 0);
        static_cast<void>(bml::extent_v<int>);
    }
    
    // Check that false_type is available.
    {
        static_assert(sizeof(bml::false_type) > 0);
    }
    
    // Check that has_unique_object_representations is available.
    {
        static_assert(sizeof(bml::has_unique_object_representations<int>) > 0);
        static_cast<void>(bml::has_unique_object_representations_v<int>);
    }
    
    // Check that has_virtual_destructor is available.
    {
        static_assert(sizeof(bml::has_virtual_destructor<int>) > 0);
        static_cast<void>(bml::has_virtual_destructor_v<int>);
    }
    
    // Check that integral_constant is available.
    {
        static_assert(sizeof(bml::integral_constant<int, 2>) > 0);
    }
    
    // Check that invoke_result is available.
    {
        static_assert(sizeof(bml::invoke_result<auto () -> int>) > 0);
        static_assert(sizeof(bml::invoke_result_ty<auto () -> int>) > 0);
    }
    
    // Check that is_abstract is available.
    {
        static_assert(sizeof(bml::is_abstract<int>) > 0);
        static_cast<void>(bml::is_abstract_v<int>);
    }
    
    // Check that is_aggregate is available.
    {
        static_assert(sizeof(bml::is_aggregate<int>) > 0);
        static_cast<void>(bml::is_aggregate_v<int>);
    }
    
    // Check that is_arithmetic is available.
    {
        static_assert(sizeof(bml::is_arithmetic<int>) > 0);
        static_cast<void>(bml::is_arithmetic_v<int>);
    }
    
    // Check that is_array is available.
    {
        static_assert(sizeof(bml::is_array<int>) > 0);
        static_cast<void>(bml::is_array_v<int>);
    }
    
    // Check that is_assignable is available.
    {
        static_assert(sizeof(bml::is_assignable<int, int>) > 0);
        static_cast<void>(bml::is_assignable_v<int, int>);
    }
    
    // Check that is_base_of is available.
    {
        static_assert(sizeof(bml::is_base_of<int, int>) > 0);
        static_cast<void>(bml::is_base_of_v<int, int>);
    }
    
    // Check that is_class is available.
    {
        static_assert(sizeof(bml::is_class<int>) > 0);
        static_cast<void>(bml::is_class_v<int>);
    }
    
    // Check that is_compound is available.
    {
        static_assert(sizeof(bml::is_compound<int>) > 0);
        static_cast<void>(bml::is_compound_v<int>);
    }
    
    // Check that is_const is available.
    {
        static_assert(sizeof(bml::is_const<int>) > 0);
        static_cast<void>(bml::is_const_v<int>);
    }
    
    // Check that is_constructible is available.
    {
        static_assert(sizeof(bml::is_constructible<int>) > 0);
        static_cast<void>(bml::is_constructible_v<int>);
    }
    
    // Check that is_convertible is available.
    {
        static_assert(sizeof(bml::is_convertible<int, int>) > 0);
        static_cast<void>(bml::is_convertible_v<int, int>);
    }
    
    // Check that is_copy_assignable is available.
    {
        static_assert(sizeof(bml::is_copy_assignable<int>) > 0);
        static_cast<void>(bml::is_copy_assignable_v<int>);
    }
    
    // Check that is_copy_constructible is available.
    {
        static_assert(sizeof(bml::is_copy_constructible<int>) > 0);
        static_cast<void>(bml::is_copy_constructible_v<int>);
    }
    
    // Check that is_default_constructible is available.
    {
        static_assert(sizeof(bml::is_default_constructible<int>) > 0);
        static_cast<void>(bml::is_default_constructible_v<int>);
    }
    
    // Check that is_destructible is available.
    {
        static_assert(sizeof(bml::is_destructible<int>) > 0);
        static_cast<void>(bml::is_destructible_v<int>);
    }
    
    // Check that is_detected is available.
    {
        static_assert(sizeof(bml::is_detected<ToInt, char>) > 0);
        static_cast<void>(bml::is_detected_v<ToInt, char>);
    }
    
    // Check that is_empty is available.
    {
        static_assert(sizeof(bml::is_empty<int>) > 0);
        static_cast<void>(bml::is_empty_v<int>);
    }
    
    // Check that is_enum is available.
    {
        static_assert(sizeof(bml::is_enum<int>) > 0);
        static_cast<void>(bml::is_enum_v<int>);
    }
    
    // Check that is_explicitly_constructible is available.
    {
        static_assert(sizeof(bml::is_explicitly_constructible<int>) > 0);
        static_cast<void>(bml::is_explicitly_constructible_v<int>);
    }
    
    // Check that is_final is available.
    {
        static_assert(sizeof(bml::is_final<int>) > 0);
        static_cast<void>(bml::is_final_v<int>);
    }
    
    // Check that is_floating_point is available.
    {
        static_assert(sizeof(bml::is_floating_point<int>) > 0);
        static_cast<void>(bml::is_floating_point_v<int>);
    }
    
    // Check that is_function is available.
    {
        static_assert(sizeof(bml::is_function<int>) > 0);
        static_cast<void>(bml::is_function_v<int>);
    }
    
    // Check that is_fundamental is available.
    {
        static_assert(sizeof(bml::is_fundamental<int>) > 0);
        static_cast<void>(bml::is_fundamental_v<int>);
    }
    
    // Check that is_integral is available.
    {
        static_assert(sizeof(bml::is_integral<int>) > 0);
        static_cast<void>(bml::is_integral_v<int>);
    }
    
    // Check that is_invocable is available.
    {
        static_assert(sizeof(bml::is_invocable<int>) > 0);
        static_cast<void>(bml::is_invocable_v<int>);
    }
    
    // Check that is_list_convertible is available.
    {
        static_assert(sizeof(bml::is_list_convertible<int>) > 0);
        static_cast<void>(bml::is_list_convertible_v<int>);
    }
    
    // Check that is_lvalue_reference is available.
    {
        static_assert(sizeof(bml::is_lvalue_reference<int>) > 0);
        static_cast<void>(bml::is_lvalue_reference_v<int>);
    }
    
    // Check that is_member_function_pointer is available.
    {
        static_assert(sizeof(bml::is_member_function_pointer<int>) > 0);
        static_cast<void>(bml::is_member_function_pointer_v<int>);
    }
    
    // Check that is_member_object_pointer is available.
    {
        static_assert(sizeof(bml::is_member_object_pointer<int>) > 0);
        static_cast<void>(bml::is_member_object_pointer_v<int>);
    }
    
    // Check that is_member_pointer is available.
    {
        static_assert(sizeof(bml::is_member_pointer<int>) > 0);
        static_cast<void>(bml::is_member_pointer_v<int>);
    }
    
    // Check that is_move_assignable is available.
    {
        static_assert(sizeof(bml::is_move_assignable<int>) > 0);
        static_cast<void>(bml::is_move_assignable_v<int>);
    }
    
    // Check that is_move_constructible is available.
    {
        static_assert(sizeof(bml::is_move_constructible<int>) > 0);
        static_cast<void>(bml::is_move_constructible_v<int>);
    }
    
    // Check that is_null_pointer is available.
    {
        static_assert(sizeof(bml::is_null_pointer<int>) > 0);
        static_cast<void>(bml::is_null_pointer_v<int>);
    }
    
    // Check that is_object is available.
    {
        static_assert(sizeof(bml::is_object<int>) > 0);
        static_cast<void>(bml::is_object_v<int>);
    }
    
    // Check that is_pod is available.
    {
        static_assert(sizeof(bml::is_pod<int>) > 0);
        static_cast<void>(bml::is_pod_v<int>);
    }
    
    // Check that is_pointer is available.
    {
        static_assert(sizeof(bml::is_pointer<int>) > 0);
        static_cast<void>(bml::is_pointer_v<int>);
    }
    
    // Check that is_polymorphic is available.
    {
        static_assert(sizeof(bml::is_polymorphic<int>) > 0);
        static_cast<void>(bml::is_polymorphic_v<int>);
    }
    
    // Check that is_reference is available.
    {
        static_assert(sizeof(bml::is_reference<int>) > 0);
        static_cast<void>(bml::is_reference_v<int>);
    }
    
    // Check that is_referenceable is available.
    {
        static_assert(sizeof(bml::is_referenceable<int>) > 0);
        static_cast<void>(bml::is_referenceable_v<int>);
    }
    
    // Check that is_reference_wrapper is available.
    {
        static_assert(sizeof(bml::is_reference_wrapper<int>) > 0);
        static_cast<void>(bml::is_reference_wrapper_v<int>);
    }
    
    // Check that is_rvalue_reference is available.
    {
        static_assert(sizeof(bml::is_rvalue_reference<int>) > 0);
        static_cast<void>(bml::is_rvalue_reference_v<int>);
    }
    
    // Check that is_same is available.
    {
        static_assert(sizeof(bml::is_same<int, int>) > 0);
        static_cast<void>(bml::is_same_v<int, int>);
    }
    
    // Check that is_scalar is available.
    {
        static_assert(sizeof(bml::is_scalar<int>) > 0);
        static_cast<void>(bml::is_scalar_v<int>);
    }
    
    // Check that is_signed is available.
    {
        static_assert(sizeof(bml::is_signed<int>) > 0);
        static_cast<void>(bml::is_signed_v<int>);
    }
    
    // Check that is_standard_layout is available.
    {
        static_assert(sizeof(bml::is_standard_layout<int>) > 0);
        static_cast<void>(bml::is_standard_layout_v<int>);
    }
    
    // Check that is_swappable is available.
    {
        static_assert(sizeof(bml::is_swappable<int>) > 0);
        static_cast<void>(bml::is_swappable_v<int>);
    }
    
    // Check that is_swappable_with is available.
    {
        static_assert(sizeof(bml::is_swappable_with<int, int>) > 0);
        static_cast<void>(bml::is_swappable_with_v<int, int>);
    }
    
    // Check that is_trivial is available.
    {
        static_assert(sizeof(bml::is_trivial<int>) > 0);
        static_cast<void>(bml::is_trivial_v<int>);
    }
    
    // Check that is_trivially_assignable is available.
    {
        static_assert(sizeof(bml::is_trivially_assignable<int, int>) > 0);
        static_cast<void>(bml::is_trivially_assignable_v<int, int>);
    }
    
    // Check that is_trivially_constructible is available.
    {
        static_assert(sizeof(bml::is_trivially_constructible<int>) > 0);
        static_cast<void>(bml::is_trivially_constructible_v<int>);
    }
    
    // Check that is_trivially_copyable is available.
    {
        static_assert(sizeof(bml::is_trivially_copyable<int>) > 0);
        static_cast<void>(bml::is_trivially_copyable_v<int>);
    }
    
    // Check that is_trivially_copy_assignable is available.
    {
        static_assert(sizeof(bml::is_trivially_copy_assignable<int>) > 0);
        static_cast<void>(bml::is_trivially_copy_assignable_v<int>);
    }
    
    // Check that is_trivially_copy_constructible is available.
    {
        static_assert(sizeof(bml::is_trivially_copy_constructible<int>) > 0);
        static_cast<void>(bml::is_trivially_copy_constructible_v<int>);
    }
    
    // Check that is_trivially_default_constructible is available.
    {
        static_assert(sizeof(bml::is_trivially_default_constructible<int>) > 0);
        static_cast<void>(bml::is_trivially_default_constructible_v<int>);
    }
    
    // Check that is_trivially_destructible is available.
    {
        static_assert(sizeof(bml::is_trivially_destructible<int>) > 0);
        static_cast<void>(bml::is_trivially_destructible_v<int>);
    }
    
    // Check that is_trivially_move_assignable is available.
    {
        static_assert(sizeof(bml::is_trivially_move_assignable<int>) > 0);
        static_cast<void>(bml::is_trivially_move_assignable_v<int>);
    }
    
    // Check that is_trivially_move_constructible is available.
    {
        static_assert(sizeof(bml::is_trivially_move_constructible<int>) > 0);
        static_cast<void>(bml::is_trivially_move_constructible_v<int>);
    }
    
    // Check that is_unbounded_array is available.
    {
        static_assert(sizeof(bml::is_unbounded_array<int>) > 0);
        static_cast<void>(bml::is_unbounded_array_v<int>);
    }
    
    // Check that is_union is available.
    {
        static_assert(sizeof(bml::is_union<int>) > 0);
        static_cast<void>(bml::is_union_v<int>);
    }
    
    // Check that is_unsigned is available.
    {
        static_assert(sizeof(bml::is_unsigned<int>) > 0);
        static_cast<void>(bml::is_unsigned_v<int>);
    }
    
    // Check that is_void is available.
    {
        static_assert(sizeof(bml::is_void<int>) > 0);
        static_cast<void>(bml::is_void_v<int>);
    }
    
    // Check that is_volatile is available.
    {
        static_assert(sizeof(bml::is_volatile<int>) > 0);
        static_cast<void>(bml::is_volatile_v<int>);
    }
    
    // Check that member_pointer_class is available.
    {
        static_assert(sizeof(bml::member_pointer_class<int bmltb::class_type::*>) > 0);
        static_assert(sizeof(bml::member_pointer_class_ty<int bmltb::class_type::*>) > 0);
    }
    
    // Check that negation is available.
    {
        static_assert(sizeof(bml::negation<bml::bool_constant<false>>) > 0);
        static_cast<void>(bml::negation_v<bml::bool_constant<false>>);
    }
    
    // Check that nonesuch is available.
    {
        static_assert(sizeof(bml::nonesuch) > 0);
    }
    
    // Check that pack_size is available.
    {
        static_assert(sizeof(bml::pack_size<int>) > 0);
        static_cast<void>(bml::pack_size_v<int>);
    }
    
    // Check that rank is available.
    {
        static_assert(sizeof(bml::rank<int>) > 0);
        static_cast<void>(bml::rank_v<int>);
    }
    
    // Check that remove_all_extents is available.
    {
        static_assert(sizeof(bml::remove_all_extents<int>) > 0);
        static_assert(sizeof(bml::remove_all_extents_ty<int>) > 0);
    }
    
    // Check that remove_const is available.
    {
        static_assert(sizeof(bml::remove_const<int>) > 0);
        static_assert(sizeof(bml::remove_const_ty<int>) > 0);
    }
    
    // Check that remove_cv is available.
    {
        static_assert(sizeof(bml::remove_cv<int>) > 0);
        static_assert(sizeof(bml::remove_cv_ty<int>) > 0);
    }
    
    // Check that remove_cvref is available.
    {
        static_assert(sizeof(bml::remove_cvref<int>) > 0);
        static_assert(sizeof(bml::remove_cvref_ty<int>) > 0);
    }
    
    // Check that remove_extent is available.
    {
        static_assert(sizeof(bml::remove_extent<int>) > 0);
        static_assert(sizeof(bml::remove_extent_ty<int>) > 0);
    }
    
    // Check that remove_pointer is available.
    {
        static_assert(sizeof(bml::remove_pointer<int>) > 0);
        static_assert(sizeof(bml::remove_pointer_ty<int>) > 0);
    }
    
    // Check that remove_reference is available.
    {
        static_assert(sizeof(bml::remove_reference<int>) > 0);
        static_assert(sizeof(bml::remove_reference_ty<int>) > 0);
    }
    
    // Check that remove_volatile is available.
    {
        static_assert(sizeof(bml::remove_volatile<int>) > 0);
        static_assert(sizeof(bml::remove_volatile_ty<int>) > 0);
    }
    
    // Check that size_of is available.
    {
        static_assert(sizeof(bml::size_of<int>) > 0);
        static_cast<void>(bml::size_of_v<int>);
    }
    
    // Check that true_type is available.
    {
        static_assert(sizeof(bml::true_type) > 0);
    }
    
    // Check that type_identity is available.
    {
        static_assert(sizeof(bml::type_identity<int>) > 0);
        static_assert(sizeof(bml::type_identity_ty<int>) > 0);
    }
    
    // Check that type_pack_element is available.
    {
        static_assert(sizeof(bml::type_pack_element<0, int>) > 0);
        static_assert(sizeof(bml::type_pack_element_ty<0, int>) > 0);
    }
    
    // Check that void_ty is available.
    {
        static_assert(bml::is_void_v<bml::void_ty<int>>);
    }
    
    return 0;
}
