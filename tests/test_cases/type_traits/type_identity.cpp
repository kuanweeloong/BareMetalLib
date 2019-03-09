//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/type_identity.hpp>
#include <bml/type_traits/is_same.hpp>

template <typename T>
auto check_result() noexcept -> void
{
    static_assert(bml::is_same_v<typename bml::type_identity<T>::type, T>);
    static_assert(bml::is_same_v<bml::type_identity_ty<T>, T>);
    
    static_assert(bml::is_same_v<typename bml::type_identity<T const>::type, T const>);
    static_assert(bml::is_same_v<bml::type_identity_ty<T const>, T const>);
    
    static_assert(bml::is_same_v<typename bml::type_identity<T volatile>::type, T volatile>);
    static_assert(bml::is_same_v<bml::type_identity_ty<T volatile>, T volatile>);
    
    static_assert(bml::is_same_v<typename bml::type_identity<T const volatile>::type,
        T const volatile>);
    static_assert(bml::is_same_v<bml::type_identity_ty<T const volatile>, T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the "type" member type alias is the same as the input type.
    {
        check_result<void>();
        check_result<int>();
        check_result<int*>();
        check_result<int const*>();
        check_result<int&>();
        check_result<int const&>();
        check_result<int&&>();
        check_result<int(&)[]>();
        check_result<int[]>();
        check_result<int[3]>();
        check_result<int(*)[]>();
        check_result<double>();
        check_result<char>();
        
        check_result<bmltb::enum_class>();
        check_result<bmltb::class_type>();
        check_result<bmltb::union_type>();
        check_result<bmltb::union_type[2]>();
        check_result<int bmltb::class_type::*>();
        check_result<bmltb::incomplete_class>();
        check_result<bmltb::incomplete_class*>();
        check_result<bmltb::incomplete_class*[1][2]>();
        
        check_result<auto (*)(int) noexcept -> void>();
        check_result<auto (bmltb::class_type::*)() -> void>();
        check_result<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
        
        check_result<auto (int) -> void>();
        check_result<auto (int) const && noexcept -> void>();
        check_result<auto (&)(int) -> void>();
        check_result<auto (*&&)(int) noexcept -> void>();
    }
    
    return 0;
}
