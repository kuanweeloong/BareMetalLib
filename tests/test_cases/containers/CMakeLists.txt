#
# Copyright (c) 2019 Wee Loong Kuan
#
# Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
# https://llvm.org/LICENSE.txt for license information.
#
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#

bml_add_test("containers.variant" variant.cpp)
bml_add_compile_failure_test("containers.variant.fail.ctor_invalid_index"
    variant.fail.ctor_invalid_index.cpp "variant index is out of bounds.")
bml_add_compile_failure_test("containers.variant.fail.emplace_invalid_index"
    variant.fail.emplace_invalid_index.cpp "variant index is out of bounds.")
bml_add_compile_failure_test("containers.variant.fail.mem_get_invalid_index"
    variant.fail.mem_get_invalid_index.cpp "variant index is out of bounds.")
bml_add_compile_failure_test("containers.variant.fail.free_get_invalid_index"
    variant.fail.free_get_invalid_index.cpp "variant index is out of bounds.")
bml_add_compile_failure_test("containers.variant.fail.no_alts"
    variant.fail.no_alts.cpp "variant should have at least 1 alternative.")
bml_add_compile_failure_test("containers.variant.fail.void_alt"
    variant.fail.void_alt.cpp "variant cannot hold void types.")
bml_add_compile_failure_test("containers.variant.fail.array_alt"
    variant.fail.array_alt.cpp "variant cannot hold array types.")
bml_add_compile_failure_test("containers.variant.fail.ref_alt"
    variant.fail.ref_alt.cpp "variant cannot hold reference types.")
bml_add_compile_failure_test("containers.variant.fail.variant_size_non_variant"
    variant.fail.variant_size_non_variant.cpp)
bml_add_compile_failure_test("containers.variant.fail.variant_alternative_non_variant"
    variant.fail.variant_alternative_non_variant.cpp)
bml_add_test("containers.optional" optional.cpp)
bml_add_compile_failure_test("containers.optional.fail.in_place_ty"
    optional.fail.in_place_ty.cpp "optional cannot hold in_place_ty.")
bml_add_compile_failure_test("containers.optional.fail.nullopt_ty"
    optional.fail.nullopt_ty.cpp "optional cannot hold nullopt_ty.")
bml_add_compile_failure_test("containers.optional.fail.void"
    optional.fail.void.cpp "optional cannot hold void.")
bml_add_compile_failure_test("containers.optional.fail.array"
    optional.fail.array.cpp "optional cannot hold array types.")
bml_add_compile_failure_test("containers.optional.fail.reference"
    optional.fail.reference.cpp "optional cannot hold reference types.")
bml_add_test("containers.tuple" tuple.cpp)
bml_add_compile_failure_test("containers.tuple.fail.mem_get_invalid_index"
    tuple.fail.mem_get_invalid_index.cpp "tuple index is out of bounds.")
bml_add_compile_failure_test("containers.tuple.fail.free_get_invalid_index"
    tuple.fail.free_get_invalid_index.cpp "tuple index is out of bounds.")
bml_add_compile_failure_test("containers.tuple.fail.tuple_size_non_tuple"
    tuple.fail.tuple_size_non_tuple.cpp)
bml_add_compile_failure_test("containers.tuple.fail.tuple_element_non_tuple"
    tuple.fail.tuple_element_non_tuple.cpp)
