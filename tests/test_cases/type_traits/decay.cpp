//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/decay.hpp>
#include <bml/type_traits/is_same.hpp>

template <typename T, typename U>
auto check_result() noexcept -> void
{
    static_assert(bml::is_same_v<typename bml::decay<T>::type, U>);
    static_assert(bml::is_same_v<bml::decay_ty<T>, U>);
}

auto test_main() noexcept -> int
{
    // Check that the result names a pointer to the underlying array type if the input is an array.
    {
        check_result<int[3], int*>();
        check_result<int const[3], int const*>();
        check_result<int volatile[3], int volatile*>();
        check_result<int const volatile[3], int const volatile*>();
        
        check_result<int[], int*>();
        check_result<int const[], int const*>();
        check_result<int volatile[], int volatile*>();
        check_result<int const volatile[], int const volatile*>();
        
        using arr_int_2 = int[2];
        using arr_int_2_c = int const[2];
        using arr_int_2_v = int volatile[2];
        using arr_int_2_cv = int const volatile[2];
        
        check_result<int[3][2], arr_int_2*>();
        check_result<int const[3][2], arr_int_2_c*>();
        check_result<int volatile[3][2], arr_int_2_v*>();
        check_result<int const volatile[3][2], arr_int_2_cv*>();
        
        check_result<bmltb::class_type[3], bmltb::class_type*>();
        check_result<bmltb::class_type const[3], bmltb::class_type const*>();
        check_result<bmltb::class_type[], bmltb::class_type*>();
        check_result<bmltb::class_type volatile[], bmltb::class_type volatile*>();
        
        check_result<bmltb::incomplete_class[3], bmltb::incomplete_class*>();
        check_result<bmltb::incomplete_class const[3], bmltb::incomplete_class const*>();
        check_result<bmltb::incomplete_class[], bmltb::incomplete_class*>();
        check_result<bmltb::incomplete_class volatile[], bmltb::incomplete_class volatile*>();
    }
    
    // Check that the result names a pointer to the underlying type of the array being referred to
    // if the input is a reference to an array.
    {
        check_result<int(&)[3], int*>();
        check_result<int const(&)[3], int const*>();
        check_result<int volatile(&)[3], int volatile*>();
        check_result<int const volatile(&)[3], int const volatile*>();
        
        check_result<int(&&)[3], int*>();
        check_result<int const(&&)[3], int const*>();
        check_result<int volatile(&&)[3], int volatile*>();
        check_result<int const volatile(&&)[3], int const volatile*>();
        
        check_result<int(&)[], int*>();
        check_result<int const(&)[], int const*>();
        check_result<int volatile(&)[], int volatile*>();
        check_result<int const volatile(&)[], int const volatile*>();
        
        check_result<int(&&)[], int*>();
        check_result<int const(&&)[], int const*>();
        check_result<int volatile(&&)[], int volatile*>();
        check_result<int const volatile(&&)[], int const volatile*>();
        
        using arr_int_2 = int[2];
        using arr_int_2_c = int const[2];
        using arr_int_2_v = int volatile[2];
        using arr_int_2_cv = int const volatile[2];
        
        check_result<int(&)[3][2], arr_int_2*>();
        check_result<int const(&)[3][2], arr_int_2_c*>();
        check_result<int volatile(&)[3][2], arr_int_2_v*>();
        check_result<int const volatile(&)[3][2], arr_int_2_cv*>();
        
        check_result<int(&&)[3][2], arr_int_2*>();
        check_result<int const(&&)[3][2], arr_int_2_c*>();
        check_result<int volatile(&&)[3][2], arr_int_2_v*>();
        check_result<int const volatile(&&)[3][2], arr_int_2_cv*>();
        
        check_result<bmltb::class_type(&)[3], bmltb::class_type*>();
        check_result<bmltb::class_type const(&)[3], bmltb::class_type const*>();
        check_result<bmltb::class_type(&&)[], bmltb::class_type*>();
        check_result<bmltb::class_type volatile(&&)[], bmltb::class_type volatile*>();
        
        check_result<bmltb::incomplete_class(&)[3], bmltb::incomplete_class*>();
        check_result<bmltb::incomplete_class const(&)[3], bmltb::incomplete_class const*>();
        check_result<bmltb::incomplete_class(&&)[], bmltb::incomplete_class*>();
        check_result<bmltb::incomplete_class volatile(&&)[], bmltb::incomplete_class volatile*>();
    }
    
    // Check that the result names a pointer to the input type if the input is a non cv-qualified
    // function type.
    {
        check_result<auto (int) -> void, auto (*)(int) -> void>();
        check_result<auto (int, ...) noexcept -> void, auto (*)(int, ...) noexcept -> void>();
    }
    
    // Check that the result names a pointer to the type being referred to if the input is a
    // reference to a non cv-qualified function type.
    {
        check_result<auto (&)(int) -> void, auto (*)(int) -> void>();
        check_result<auto (&)(int, ...) noexcept -> void, auto (*)(int, ...) noexcept -> void>();
        
        check_result<auto (&&)(int) -> void, auto (*)(int) -> void>();
        check_result<auto (&&)(int, ...) noexcept -> void, auto (*)(int, ...) noexcept -> void>();
    }
    
    // Check that the result names the unqualified version of the input type if the input is not 
    // a reference, an array or a non-cv qualified function type.
    {
        check_result<void, void>();
        check_result<void const, void>();
        check_result<void volatile, void>();
        check_result<void const volatile, void>();
        
        check_result<int, int>();
        check_result<int const volatile, int>();
        check_result<int*, int*>();
        check_result<int* const, int*>();
        check_result<int volatile*, int volatile*>();
        check_result<int volatile* const, int volatile*>();
        
        check_result<bmltb::class_type, bmltb::class_type>();
        check_result<bmltb::class_type*, bmltb::class_type*>();
        check_result<bmltb::enum_class, bmltb::enum_class>();
        check_result<bmltb::union_type const, bmltb::union_type>();
        check_result<bmltb::incomplete_class, bmltb::incomplete_class>();
        check_result<int bmltb::class_type::*, int bmltb::class_type::*>();
        check_result<int const bmltb::class_type::*, int const bmltb::class_type::*>();
        
        check_result<auto (*)(int) -> void, auto (*)(int) -> void>();
        check_result<auto (* const)(int) -> void, auto (*)(int) -> void>();
        check_result<auto (*)(int, ...) noexcept -> void, auto (*)(int, ...) noexcept -> void>();
        
        check_result<auto (bmltb::class_type::*)() -> void,
            auto (bmltb::class_type::*)() -> void>();
        check_result<auto (bmltb::class_type::*)() volatile && noexcept -> void,
            auto (bmltb::class_type::*)() volatile && noexcept -> void>();
        
        check_result<auto (int) & -> void, auto (int) & -> void>();        
        check_result<auto (int) const && -> void, auto (int) const && -> void>();
        check_result<auto () const && noexcept -> void, auto () const && noexcept -> void>();
    }
    
    // Check that the result names the unqualified version of the type being referred to if the
    // input is a reference to a type that is not an array or a non-cv qualified function type.
    {
        check_result<int&, int>();
        check_result<int&&, int>();
        check_result<int const volatile&&, int>();
        check_result<int*&, int*>();
        check_result<int* const&, int*>();
        check_result<int volatile*&&, int volatile*>();
        check_result<int volatile* const&, int volatile*>();
        
        check_result<bmltb::class_type&, bmltb::class_type>();
        check_result<bmltb::class_type const volatile&&, bmltb::class_type>();
        check_result<bmltb::union_type&&, bmltb::union_type>();
        
        check_result<auto (*&&)(int) -> void, auto (*)(int) -> void>();
        check_result<auto (* const&)(int) -> void, auto (*)(int) -> void>();
    }
    
    return 0;
}
