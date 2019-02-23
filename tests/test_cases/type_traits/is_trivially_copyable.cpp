//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_trivially_copyable.hpp>

template <typename T>
auto check_trivially_copyable() noexcept -> void
{
    static_assert(bml::is_trivially_copyable<T>::value);
    static_assert(bml::is_trivially_copyable_v<T>);
    
    static_assert(bml::is_trivially_copyable<T const>::value);
    static_assert(bml::is_trivially_copyable_v<T const>);
}

template <typename T>
auto check_not_trivially_copyable() noexcept -> void
{
    static_assert(!bml::is_trivially_copyable<T>::value);
    static_assert(!bml::is_trivially_copyable_v<T>);
    
    static_assert(!bml::is_trivially_copyable<T const>::value);
    static_assert(!bml::is_trivially_copyable_v<T const>);
}

struct trivially_copyable
{
    int i;
};

struct trivially_copyable_2
{
    trivially_copyable_2(trivially_copyable_2 const&) = default;
    
    int i;
};

struct not_trivially_copyable
{
    not_trivially_copyable(not_trivially_copyable const&);
    
    int i;
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input type is trivially copyable.
    // TODO: Test volatile/cv-qualified types when Defect #2094 ("Trivial copy/move constructor for
    // class with volatile member") is implemented in all supported compilers.
    {
        check_trivially_copyable<int>();
        check_trivially_copyable<int[2]>();
        check_trivially_copyable<int*>();
        check_trivially_copyable<int*[2]>();
        
        check_trivially_copyable<double>();
        check_trivially_copyable<double[2]>();;
        check_trivially_copyable<double*>();
        check_trivially_copyable<double*[2]>();
        
        check_trivially_copyable<bmltb::enum_class>();
        check_trivially_copyable<trivially_copyable>();
        check_trivially_copyable<trivially_copyable_2>();
    }
    
    // Check that the result is true when the input type is not trivially copyable.
    {
        check_not_trivially_copyable<not_trivially_copyable>();
        
        check_not_trivially_copyable<void>();
        check_not_trivially_copyable<int&>();
        check_not_trivially_copyable<int const&>();
        check_not_trivially_copyable<int&&>();
        check_not_trivially_copyable<int(&)[2]>();
        
        check_not_trivially_copyable<auto (int) -> void>();
        check_not_trivially_copyable<auto (int) const && noexcept -> void>();
        check_not_trivially_copyable<auto (&)(int) -> void>();
        check_not_trivially_copyable<auto (*&&)(int) noexcept -> void>();
    }
    
    return 0;
}
