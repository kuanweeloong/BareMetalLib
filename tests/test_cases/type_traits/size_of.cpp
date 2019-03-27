//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/size_of.hpp>

template <typename T>
auto check_size() noexcept -> void
{
    static_assert(bml::size_of<T>::value == sizeof(T));
    static_assert(bml::size_of_v<T> == sizeof(T));
    
    static_assert(bml::size_of<T const>::value == sizeof(T));
    static_assert(bml::size_of_v<T const> == sizeof(T));
    
    static_assert(bml::size_of<T volatile>::value == sizeof(T));
    static_assert(bml::size_of_v<T volatile> == sizeof(T));
    
    static_assert(bml::size_of<T const volatile>::value == sizeof(T));
    static_assert(bml::size_of_v<T const volatile> == sizeof(T));
}

struct size64 { char c[64]; };

auto test_main() noexcept -> int
{
    // Check that the result is the same as the output of the sizeof operator.
    {
        check_size<bool>();
        check_size<int>();
        check_size<int*>();
        check_size<int const*>();
        check_size<int&>();
        check_size<int const&>();
        check_size<int&&>();
        check_size<int[3]>();
        check_size<int(*)[]>();
        check_size<double>();
        check_size<char>();
        
        check_size<size64>();
        
        check_size<bmltb::enum_class>();
        check_size<bmltb::class_type>();
        check_size<bmltb::union_type>();
        check_size<bmltb::union_type[2]>();
        check_size<int bmltb::class_type::*>();
        check_size<bmltb::incomplete_class*>();
        check_size<bmltb::incomplete_class*[1][2]>();
        
        check_size<auto (*)(int) noexcept -> void>();
        check_size<auto (bmltb::class_type::*)() -> void>();
        check_size<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
        check_size<auto (*&&)(int) noexcept -> void>();
    }

    return 0;
}
