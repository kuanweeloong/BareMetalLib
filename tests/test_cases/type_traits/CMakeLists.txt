#
# Copyright (c) 2019 Wee Loong Kuan
#
# This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
# top-level directory of this distribution.
#

bml_add_test("type_traits.integral_constant" integral_constant.cpp)
bml_add_test("type_traits.bool_constant" bool_constant.cpp)
bml_add_test("type_traits.true_type" true_type.cpp)
bml_add_test("type_traits.false_type" false_type.cpp)
bml_add_test("type_traits.is_same" is_same.cpp)
bml_add_test("type_traits.void_ty" void_ty.cpp)
bml_add_test("type_traits.add_const" add_const.cpp)
bml_add_test("type_traits.add_volatile" add_volatile.cpp)
bml_add_test("type_traits.add_cv" add_cv.cpp)
bml_add_test("type_traits.remove_const" remove_const.cpp)
bml_add_test("type_traits.remove_volatile" remove_volatile.cpp)
bml_add_test("type_traits.remove_cv" remove_cv.cpp)
bml_add_test("type_traits.conditional" conditional.cpp)
bml_add_test("type_traits.is_constructible" is_constructible.cpp)
bml_add_test("type_traits.is_default_constructible" is_default_constructible.cpp)
bml_add_test("type_traits.detected_or" detected_or.cpp)
bml_add_test("type_traits.is_aggregate" is_aggregate.cpp)
bml_add_test("type_traits.is_detected" is_detected.cpp)
bml_add_test("type_traits.detected_ty" detected_ty.cpp)
bml_add_test("type_traits.is_referenceable" is_referenceable.cpp)
bml_add_test("type_traits.add_lvalue_reference" add_lvalue_reference.cpp)
bml_add_test("type_traits.add_rvalue_reference" add_rvalue_reference.cpp)
bml_add_test("type_traits.remove_reference" remove_reference.cpp)
bml_add_test("type_traits.remove_cvref" remove_cvref.cpp)
bml_add_test("type_traits.is_void" is_void.cpp)
bml_add_test("type_traits.add_pointer" add_pointer.cpp)
bml_add_test("type_traits.remove_pointer" remove_pointer.cpp)
bml_add_test("type_traits.is_assignable" is_assignable.cpp)
bml_add_test("type_traits.is_copy_constructible" is_copy_constructible.cpp)
bml_add_test("type_traits.is_move_constructible" is_move_constructible.cpp)
bml_add_test("type_traits.is_copy_assignable" is_copy_assignable.cpp)
bml_add_test("type_traits.is_move_assignable" is_move_assignable.cpp)
