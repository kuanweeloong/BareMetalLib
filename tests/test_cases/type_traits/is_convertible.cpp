//
// Copyright (c) 2019 Wee Loong Kuan
//
// Fromhis file is licensed under the MIFrom license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_convertible.hpp>

template <typename From, typename To>
auto check_convertible() noexcept -> void
{
    static_assert(bml::is_convertible<From, To>::value);
    static_assert(bml::is_convertible_v<From, To>);
}

template <typename From, typename To>
auto check_not_convertible() noexcept -> void
{
    static_assert(!bml::is_convertible<From, To>::value);
    static_assert(!bml::is_convertible_v<From, To>);
}

template <typename From, typename To>
auto check_convertible_cv() noexcept -> void
{
    check_convertible<From, To>();
    
    check_convertible<From const, To>();
    check_convertible<From, To const>();
    check_convertible<From const, To const>();
    
    check_convertible<From volatile, To>();
    check_convertible<From, To volatile>();
    check_convertible<From volatile, To volatile>();
    
    check_convertible<From const volatile, To>();
    check_convertible<From, To const volatile>();
    check_convertible<From const volatile, To const volatile>();
}

template <typename From, typename To>
auto check_not_convertible_cv() noexcept -> void
{
    check_not_convertible<From, To>();
    
    check_not_convertible<From const, To>();
    check_not_convertible<From, To const>();
    check_not_convertible<From const, To const>();
    
    check_not_convertible<From volatile, To>();
    check_not_convertible<From, To volatile>();
    check_not_convertible<From volatile, To volatile>();
    
    check_not_convertible<From const volatile, To>();
    check_not_convertible<From, To const volatile>();
    check_not_convertible<From const volatile, To const volatile>(); 
}

struct implicit_conv
{
    implicit_conv(int) {}
    implicit_conv(int*) {}
};

struct explicit_conv
{
    explicit explicit_conv(int) {}
    explicit explicit_conv(int*) {}
};

struct access_check
{
private:
    access_check(int) {}
    
    access_check(access_check const&) = delete;
    auto operator=(access_check const&) -> access_check& = delete;
};

template <typename NoFoo>
struct do_not_instantiate
{
    static constexpr auto x = NoFoo::foo;
};

auto test_main() noexcept -> int
{
    // Check that void is not convertible to any type other than void.
    {
        check_convertible_cv<void, void>();
        
        check_not_convertible_cv<void, int>();
        check_not_convertible_cv<void, int&>();
        check_not_convertible_cv<void, int&&>();
        check_not_convertible_cv<void, int*>();
        
        check_not_convertible_cv<void, int[]>();
        check_not_convertible_cv<void, int[3]>();
        check_not_convertible_cv<void, int(&)[3]>();
        check_not_convertible_cv<void, int(*)[3]>();
        
        check_not_convertible_cv<void, bmltb::class_type>();
        check_not_convertible_cv<void, bmltb::enum_class>();
        check_not_convertible_cv<void, bmltb::union_type>();
        check_not_convertible_cv<void, int bmltb::class_type::*>();
        
        check_not_convertible_cv<void, auto () -> void>();
        check_not_convertible_cv<void, auto (*)() -> void>();
        check_not_convertible_cv<void, auto (&)() -> void>();
        check_not_convertible_cv<void, auto (int) const && noexcept -> void>();
        check_not_convertible_cv<void, auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that non-cv/ref-qualified function types are not convertible to any other type except
    // pointers or references to itself.
    {
        check_convertible_cv<auto () -> void, auto (*)() -> void>();
        check_convertible_cv<auto () -> void, auto (&)() -> void>();
        check_convertible_cv<auto () -> void, auto (&&)() -> void>();
        
        check_not_convertible_cv<auto () -> void, void>();
        
        check_not_convertible_cv<auto () -> void, int>();
        check_not_convertible_cv<auto () -> void, int&>();
        check_not_convertible_cv<auto () -> void, int&&>();
        check_not_convertible_cv<auto () -> void, int*>();
        
        check_not_convertible_cv<auto () -> void, int[]>();
        check_not_convertible_cv<auto () -> void, int[3]>();
        check_not_convertible_cv<auto () -> void, int(&)[3]>();
        check_not_convertible_cv<auto () -> void, int(*)[3]>();
        
        check_not_convertible_cv<auto () -> void, bmltb::class_type>();
        check_not_convertible_cv<auto () -> void, bmltb::enum_class>();
        check_not_convertible_cv<auto () -> void, bmltb::union_type>();
        check_not_convertible_cv<auto () -> void, int bmltb::class_type::*>();
        
        check_not_convertible_cv<auto () -> void, auto () -> void>();
        check_not_convertible_cv<auto () -> void, auto (char) -> int>();
        check_not_convertible_cv<auto () -> void, auto (int) const && noexcept -> void>();
        check_not_convertible_cv<auto () -> void, auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that references to non-cv/ref-qualified function types are not convertible to any other
    // type except references or pointers to the same function type.
    {
        // Lvalue reference
        check_convertible_cv<auto (&)() -> void, auto (*)() -> void>();
        check_convertible_cv<auto (&)() -> void, auto (&)() -> void>();
        check_convertible_cv<auto (&)() -> void, auto (&&)() -> void>();
        
        check_not_convertible_cv<auto (&)() -> void, void>();
        
        check_not_convertible_cv<auto (&)() -> void, int>();
        check_not_convertible_cv<auto (&)() -> void, int&>();
        check_not_convertible_cv<auto (&)() -> void, int&&>();
        check_not_convertible_cv<auto (&)() -> void, int*>();
        
        check_not_convertible_cv<auto (&)() -> void, int[]>();
        check_not_convertible_cv<auto (&)() -> void, int[3]>();
        check_not_convertible_cv<auto (&)() -> void, int(&)[3]>();
        check_not_convertible_cv<auto (&)() -> void, int(*)[3]>();
        
        check_not_convertible_cv<auto (&)() -> void, bmltb::class_type>();
        check_not_convertible_cv<auto (&)() -> void, bmltb::enum_class>();
        check_not_convertible_cv<auto (&)() -> void, bmltb::union_type>();
        check_not_convertible_cv<auto (&)() -> void, int bmltb::class_type::*>();
        
        check_not_convertible_cv<auto (&)() -> void, auto () -> void>();
        check_not_convertible_cv<auto (&)() -> void, auto (char) -> int>();
        check_not_convertible_cv<auto (&)() -> void, auto (int) const && noexcept -> void>();
        check_not_convertible_cv<auto (&)() -> void, auto (bmltb::class_type::*)() -> void>();
        
        // Rvalue reference
        check_convertible_cv<auto (&&)() -> void, auto (*)() -> void>();
        check_convertible_cv<auto (&&)() -> void, auto (&)() -> void>();
        check_convertible_cv<auto (&&)() -> void, auto (&&)() -> void>();
        
        check_not_convertible_cv<auto (&&)() -> void, void>();
        
        check_not_convertible_cv<auto (&&)() -> void, int>();
        check_not_convertible_cv<auto (&&)() -> void, int&>();
        check_not_convertible_cv<auto (&&)() -> void, int&&>();
        check_not_convertible_cv<auto (&&)() -> void, int*>();
        
        check_not_convertible_cv<auto (&&)() -> void, int[]>();
        check_not_convertible_cv<auto (&&)() -> void, int[3]>();
        check_not_convertible_cv<auto (&&)() -> void, int(&)[3]>();
        check_not_convertible_cv<auto (&&)() -> void, int(*)[3]>();
        
        check_not_convertible_cv<auto (&&)() -> void, bmltb::class_type>();
        check_not_convertible_cv<auto (&&)() -> void, bmltb::enum_class>();
        check_not_convertible_cv<auto (&&)() -> void, bmltb::union_type>();
        check_not_convertible_cv<auto (&&)() -> void, int bmltb::class_type::*>();
        
        check_not_convertible_cv<auto (&&)() -> void, auto () -> void>();
        check_not_convertible_cv<auto (&&)() -> void, auto (char) -> int>();
        check_not_convertible_cv<auto (&&)() -> void, auto (int) const && noexcept -> void>();
        check_not_convertible_cv<auto (&&)() -> void, auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that pointers to non-cv/ref-qualified functions are not convertible to any other type
    // except itself.
    {
        check_convertible_cv<auto (*)() -> void, auto (*)() -> void>();
        
        check_not_convertible_cv<auto (*)() -> void, void>();
        
        check_not_convertible_cv<auto (*)() -> void, int>();
        check_not_convertible_cv<auto (*)() -> void, int&>();
        check_not_convertible_cv<auto (*)() -> void, int&&>();
        check_not_convertible_cv<auto (*)() -> void, int*>();
        
        check_not_convertible_cv<auto (*)() -> void, int[]>();
        check_not_convertible_cv<auto (*)() -> void, int[3]>();
        check_not_convertible_cv<auto (*)() -> void, int(&)[3]>();
        check_not_convertible_cv<auto (*)() -> void, int(*)[3]>();
        
        check_not_convertible_cv<auto (*)() -> void, bmltb::class_type>();
        check_not_convertible_cv<auto (*)() -> void, bmltb::enum_class>();
        check_not_convertible_cv<auto (*)() -> void, bmltb::union_type>();
        check_not_convertible_cv<auto (*)() -> void, int bmltb::class_type::*>();
        
        check_not_convertible_cv<auto (*)() -> void, auto () -> void>();
        check_not_convertible_cv<auto (*)() -> void, auto (&)() -> void>();
        check_not_convertible_cv<auto (*)() -> void, auto (&&)() -> void>();
        check_not_convertible_cv<auto (*)() -> void, auto (char) -> int>();
        check_not_convertible_cv<auto (*)() -> void, auto (int) const && noexcept -> void>();
        check_not_convertible_cv<auto (*)() -> void, auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that cv/ref-qualified function types are not convertible to any type.
    {
        check_not_convertible_cv<auto () const && -> void, void>();
        
        check_not_convertible_cv<auto () const && -> void, int>();
        check_not_convertible_cv<auto () const && -> void, int&>();
        check_not_convertible_cv<auto () const && -> void, int&&>();
        check_not_convertible_cv<auto () const && -> void, int*>();
        
        check_not_convertible_cv<auto () const && -> void, int[]>();
        check_not_convertible_cv<auto () const && -> void, int[3]>();
        check_not_convertible_cv<auto () const && -> void, int(&)[3]>();
        check_not_convertible_cv<auto () const && -> void, int(*)[3]>();
        
        check_not_convertible_cv<auto () const && -> void, bmltb::class_type>();
        check_not_convertible_cv<auto () const && -> void, bmltb::enum_class>();
        check_not_convertible_cv<auto () const && -> void, bmltb::union_type>();
        check_not_convertible_cv<auto () const && -> void, int bmltb::class_type::*>();
        
        check_not_convertible_cv<auto () const && -> void, auto () -> void>();
        check_not_convertible_cv<auto () const && -> void, auto (*)() -> void>();
        check_not_convertible_cv<auto () const && -> void, auto (&)() -> void>();
        check_not_convertible_cv<auto () const && -> void, auto () const && -> void>();
        check_not_convertible_cv<auto () const && -> void, auto (int) const && -> void>();
        check_not_convertible_cv<auto () const && -> void, auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that arrays are not convertible to any type except:
    //   1. Lvalue references to themselves, except with a const-qualified version of the underlying
    //      array type (e.g. int[3] --> int const(&)[3], but not int[3] --> int(&)[3])
    //   2. Rvalue references to themselves, and possibly with a more cv-qualified version of the
    //      underlying array type (e.g. int[3] --> int volatile(&&)[3]).
    //   3. Pointers to more cv-qualified version of the underlying type.
    {
        // Complete array
        check_convertible<int[3], int const(&)[3]>();
        check_convertible<int const[3], int const(&)[3]>();
        
        check_convertible<int[3], int(&&)[3]>();
        check_convertible<int[3], int const(&&)[3]>();
        check_convertible<int[3], int volatile(&&)[3]>();
        check_convertible<int[3], int const volatile(&&)[3]>();
        check_convertible<int const[3], int const(&&)[3]>();
        check_convertible<int const[3], int const volatile(&&)[3]>();
        
        check_convertible<int[3], int*>();
        check_convertible<int[3], int const*>();
        check_convertible<int[3], int volatile*>();
        check_convertible<int[3], int const volatile*>();
        check_convertible<int const[3], int const*>();
        check_convertible<int const[3], int const volatile*>();
        
        check_not_convertible_cv<int[3], void>();
        
        check_not_convertible_cv<int[3], int>();
        check_not_convertible_cv<int[3], int&>();
        check_not_convertible_cv<int[3], int&&>();
        
        check_not_convertible_cv<int const[3], int*>();
        check_not_convertible_cv<int const[3], int volatile*>();
        check_not_convertible_cv<int[3][2], int*>();
        
        check_not_convertible_cv<int[3], int[]>();
        check_not_convertible_cv<int[3], int[2]>();
        check_not_convertible_cv<int[3], int[3]>();
        check_not_convertible_cv<int[3], int(&)[3]>();
        check_not_convertible_cv<int[3], int volatile(&)[3]>();
        check_not_convertible_cv<int[3], int const volatile(&)[3]>();
        check_not_convertible_cv<int const[3], int const[3]>();
        check_not_convertible_cv<int const[3], int(&)[3]>();
        check_not_convertible_cv<int const[3], int volatile(&)[3]>();
        check_not_convertible_cv<int const[3], int const volatile(&)[3]>();
        check_not_convertible_cv<int const[3], int(&&)[3]>();
        check_not_convertible_cv<int const[3], int volatile(&&)[3]>();
        
        check_not_convertible_cv<int[3], bmltb::class_type>();
        check_not_convertible_cv<int[3], bmltb::enum_class>();
        check_not_convertible_cv<int[3], bmltb::union_type>();
        check_not_convertible_cv<int[3], int bmltb::class_type::*>();
        
        check_not_convertible_cv<int[3], auto () -> void>();
        check_not_convertible_cv<int[3], auto (*)() -> void>();
        check_not_convertible_cv<int[3], auto (&)() -> void>();
        check_not_convertible_cv<int[3], auto (int) const && noexcept -> void>();
        check_not_convertible_cv<int[3], auto (bmltb::class_type::*)() -> void>();
        
        // Incomplete array
        check_convertible<int[], int const(&)[]>();
        check_convertible<int const[], int const(&)[]>();
        
        check_convertible<int[], int(&&)[]>();
        check_convertible<int[], int const(&&)[]>();
        check_convertible<int[], int volatile(&&)[]>();
        check_convertible<int[], int const volatile(&&)[]>();
        check_convertible<int const[], int const(&&)[]>();
        check_convertible<int const[], int const volatile(&&)[]>();
        
        check_convertible<int[], int*>();
        check_convertible<int[], int const*>();
        check_convertible<int[], int volatile*>();
        check_convertible<int[], int const volatile*>();
        check_convertible<int const[], int const*>();
        check_convertible<int const[], int const volatile*>();
        
        check_not_convertible_cv<int[], void>();
        
        check_not_convertible_cv<int[], int>();
        check_not_convertible_cv<int[], int&>();
        check_not_convertible_cv<int[], int&&>();
        
        check_not_convertible_cv<int const[], int*>();
        check_not_convertible_cv<int const[], int volatile*>();
        check_not_convertible_cv<int[][2], int*>();
        
        check_not_convertible_cv<int[], int[]>();
        check_not_convertible_cv<int[], int[2]>();
        check_not_convertible_cv<int[], int(&)[]>();
        check_not_convertible_cv<int[], int volatile(&)[]>();
        check_not_convertible_cv<int[], int const volatile(&)[]>();
        check_not_convertible_cv<int const[], int const[]>();
        check_not_convertible_cv<int const[], int(&)[]>();
        check_not_convertible_cv<int const[], int volatile(&)[]>();
        check_not_convertible_cv<int const[], int const volatile(&)[]>();
        check_not_convertible_cv<int const[], int(&&)[]>();
        check_not_convertible_cv<int const[], int volatile(&&)[]>();
        
        check_not_convertible_cv<int[], bmltb::class_type>();
        check_not_convertible_cv<int[], bmltb::enum_class>();
        check_not_convertible_cv<int[], bmltb::union_type>();
        check_not_convertible_cv<int[], int bmltb::class_type::*>();
        
        check_not_convertible_cv<int[], auto () -> void>();
        check_not_convertible_cv<int[], auto (*)() -> void>();
        check_not_convertible_cv<int[], auto (&)() -> void>();
        check_not_convertible_cv<int[], auto (int) const && noexcept -> void>();
        check_not_convertible_cv<int[], auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that lvalue references to arrays are not convertible to any type except:
    //   1. The same type, possibly with a more const-qualified version of the underlying array type
    //      (e.g. int(&)[3] --> int const(&)[3], but not int const(&)[3] --> int(&)[3]).
    //   2. Pointers to more cv-qualified version of the underlying type.
    {
        check_convertible<int(&)[3], int(&)[3]>();
        check_convertible<int(&)[3], int const(&)[3]>();
        check_convertible<int(&)[3], int volatile(&)[3]>();
        check_convertible<int(&)[3], int const volatile(&)[3]>();
        check_convertible<int const(&)[3], int const(&)[3]>();
        check_convertible<int const(&)[3], int const volatile(&)[3]>();
        
        check_convertible<int(&)[3], int*>();
        check_convertible<int(&)[3], int const*>();
        check_convertible<int(&)[3], int volatile*>();
        check_convertible<int(&)[3], int const volatile*>();
        check_convertible<int const(&)[3], int const*>();
        check_convertible<int const(&)[3], int const volatile*>();
        
        check_not_convertible_cv<int(&)[3], void>();
        
        check_not_convertible_cv<int(&)[3], int>();
        check_not_convertible_cv<int(&)[3], int&>();
        check_not_convertible_cv<int(&)[3], int const&>();
        check_not_convertible_cv<int(&)[3], int&&>();
        check_not_convertible_cv<int(&)[3], int const&&>();
        check_not_convertible_cv<int const(&)[3], int const&>();
        check_not_convertible_cv<int const(&)[3], int const&&>();
        
        check_not_convertible_cv<int const(&)[3], int*>();
        check_not_convertible_cv<int const(&)[3], int volatile*>();
        check_not_convertible_cv<int(&)[3][2], int*>();
        
        check_not_convertible_cv<int(&)[3], int[]>();
        check_not_convertible_cv<int(&)[3], int[2]>();
        check_not_convertible_cv<int(&)[3], int[3]>();
        check_not_convertible_cv<int(&)[3], int(&)[2]>();
        check_not_convertible_cv<int const(&)[3], int const[3]>();
        check_not_convertible_cv<int const(&)[3], int(&)[3]>();
        check_not_convertible_cv<int const(&)[3], int volatile(&)[3]>();
        
        check_not_convertible_cv<int(&)[3], int(&&)[3]>();
        check_not_convertible_cv<int const(&)[3], int(&&)[3]>();
        check_not_convertible_cv<int const(&)[3], int const(&&)[3]>();
        
        check_not_convertible_cv<int(&)[3], bmltb::class_type>();
        check_not_convertible_cv<int(&)[3], bmltb::enum_class>();
        check_not_convertible_cv<int(&)[3], bmltb::union_type>();
        check_not_convertible_cv<int(&)[3], int bmltb::class_type::*>();
        
        check_not_convertible_cv<int(&)[3], auto () -> void>();
        check_not_convertible_cv<int(&)[3], auto (*)() -> void>();
        check_not_convertible_cv<int(&)[3], auto (&)() -> void>();
        check_not_convertible_cv<int(&)[3], auto (int) const && noexcept -> void>();
        check_not_convertible_cv<int(&)[3], auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that rvalue references to arrays are not convertible to any type except:
    //   1. The same type, possibly with a more const-qualified version of the underlying array type
    //      (e.g. int(&&)[3] --> int const(&&)[3], but not int const(&&)[3] --> int(&&)[3]).
    //   2. Lvalue references of the same array type, except with a const-qualified version of the
    //      underlying type (e.g. int(&&)[3] --> int const(&)[3]).
    //   3. Pointers to more cv-qualified version of the underlying type.
    {
        check_convertible<int(&&)[3], int(&&)[3]>();
        check_convertible<int(&&)[3], int const(&&)[3]>();
        check_convertible<int(&&)[3], int volatile(&&)[3]>();
        check_convertible<int(&&)[3], int const volatile(&&)[3]>();
        check_convertible<int const(&&)[3], int const(&&)[3]>();
        check_convertible<int const(&&)[3], int const volatile(&&)[3]>();
        
        check_convertible<int(&&)[3], int*>();
        check_convertible<int(&&)[3], int const*>();
        check_convertible<int(&&)[3], int volatile*>();
        check_convertible<int(&&)[3], int const volatile*>();
        check_convertible<int const(&&)[3], int const*>();
        check_convertible<int const(&&)[3], int const volatile*>();
        
        check_convertible<int(&&)[3], int const(&)[3]>();
        check_convertible<int const(&&)[3], int const(&)[3]>();
        
        check_not_convertible_cv<int(&&)[3], void>();
        
        check_not_convertible_cv<int(&&)[3], int>();
        check_not_convertible_cv<int(&&)[3], int&>();
        check_not_convertible_cv<int(&&)[3], int const&>();
        check_not_convertible_cv<int(&&)[3], int const&&>();
        check_not_convertible_cv<int const(&&)[3], int const&>();
        check_not_convertible_cv<int const(&&)[3], int const&&>();
        
        check_not_convertible_cv<int const(&)[3], int*>();
        check_not_convertible_cv<int const(&)[3], int volatile*>();
        check_not_convertible_cv<int(&&)[3][2], int*>();
        
        check_not_convertible_cv<int(&&)[3], int[]>();
        check_not_convertible_cv<int(&&)[3], int[2]>();
        check_not_convertible_cv<int(&&)[3], int[3]>();
        check_not_convertible_cv<int(&&)[3], int(&&)[2]>();
        check_not_convertible_cv<int const(&&)[3], int const[3]>();
        check_not_convertible_cv<int const(&&)[3], int(&&)[3]>();
        check_not_convertible_cv<int const(&&)[3], int volatile(&&)[3]>();
        
        check_not_convertible_cv<int(&&)[3], int(&)[3]>();
        check_not_convertible_cv<int(&&)[3], int volatile(&)[3]>();
        check_not_convertible_cv<int(&&)[3], int const volatile(&)[3]>();
        check_not_convertible_cv<int const(&&)[3], int(&)[3]>();
        check_not_convertible_cv<int const(&&)[3], int volatile(&)[3]>();
        check_not_convertible_cv<int const(&&)[3], int const volatile(&)[3]>();
        
        check_not_convertible_cv<int(&&)[3], bmltb::class_type>();
        check_not_convertible_cv<int(&&)[3], bmltb::enum_class>();
        check_not_convertible_cv<int(&&)[3], bmltb::union_type>();
        check_not_convertible_cv<int(&&)[3], int bmltb::class_type::*>();
        
        check_not_convertible_cv<int(&&)[3], auto () -> void>();
        check_not_convertible_cv<int(&&)[3], auto (*)() -> void>();
        check_not_convertible_cv<int(&&)[3], auto (&)() -> void>();
        check_not_convertible_cv<int(&&)[3], auto (int) const && noexcept -> void>();
        check_not_convertible_cv<int(&&)[3], auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that fundamental types that are not array, function or voids are convertible to:
    //   1. Any cv-qualified versions of themselves (e.g. int const --> int or
    //      int volatile --> int const).
    //   2. Lvalue references to a const-qualified (but not volatile-qualified) version of
    //      themslves.
    //   3. Rvalue references to (possibly more cv-qualified versions of) themselves.
    {
        check_convertible_cv<int, int>();
        
        check_convertible<int, int const&>();
        check_convertible<int const, int const&>();
        
        check_convertible<int, int&&>();
        check_convertible<int, int const&&>();
        check_convertible<int, int const volatile&&>();
        check_convertible<int const, int const&&>();
        check_convertible<int const, int const volatile&&>();
        check_convertible<int volatile, int const volatile&&>();
        
        check_not_convertible_cv<int, void>();
        
        check_not_convertible_cv<int, int*>();
        check_not_convertible_cv<int, int const volatile*>();
        check_not_convertible_cv<int, int[]>();
        check_not_convertible_cv<int, int[3]>();
        check_not_convertible_cv<int, int(&)[3]>();
        check_not_convertible_cv<int, int(*)[3]>();
        
        check_not_convertible<int, int&>();
        check_not_convertible<int, int volatile&>();
        check_not_convertible<int, int const volatile&>();
        check_not_convertible<int const, int&>();
        check_not_convertible<int const, int volatile&>();
        check_not_convertible<int const, int const volatile&>();
        check_not_convertible<int volatile, int&>();
        check_not_convertible<int volatile, int const&>();
        check_not_convertible<int volatile, int volatile&>();
        check_not_convertible<int volatile, int const volatile&>();
        
        check_not_convertible<int const, int&&>();
        check_not_convertible<int volatile, int const&&>();
        check_not_convertible<int const volatile, int const&&>();
        
        check_not_convertible_cv<int, bmltb::class_type>();
        check_not_convertible_cv<int, bmltb::enum_class>();
        check_not_convertible_cv<int, bmltb::union_type>();
        check_not_convertible_cv<int, int bmltb::class_type::*>();
        
        check_not_convertible_cv<int, auto () -> void>();
        check_not_convertible_cv<int, auto (*)() -> void>();
        check_not_convertible_cv<int, auto (&)() -> void>();
        check_not_convertible_cv<int, auto (int) const && noexcept -> void>();
        check_not_convertible_cv<int, auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that compound types are convertible to:
    //   1. Any (possibly more cv-qualified versions of) themselves, unless the type is already
    //      volatile-qualified - a volatile type cannot be converted to any other type.
    //   2. Lvalue references to a const-qualified (but not volatile-qualified) version of
    //      themslves.
    //   3. Rvalue references to (possibly more cv-qualified versions of) themselves.
    {
        check_convertible<bmltb::class_type, bmltb::class_type>();
        check_convertible<bmltb::class_type, bmltb::class_type const>();
        check_convertible<bmltb::class_type, bmltb::class_type volatile>();
        check_convertible<bmltb::class_type, bmltb::class_type const volatile>();
        check_convertible<bmltb::class_type const, bmltb::class_type const>();
        check_convertible<bmltb::class_type const, bmltb::class_type volatile>();
        check_convertible<bmltb::class_type const, bmltb::class_type const volatile>();
        
        check_convertible<bmltb::class_type, bmltb::class_type const&>();
        check_convertible<bmltb::class_type const, bmltb::class_type const&>();
        
        check_convertible<bmltb::class_type, bmltb::class_type&&>();
        check_convertible<bmltb::class_type, bmltb::class_type const&&>();
        check_convertible<bmltb::class_type, bmltb::class_type const volatile&&>();
        check_convertible<bmltb::class_type const, bmltb::class_type const&&>();
        check_convertible<bmltb::class_type const, bmltb::class_type const volatile&&>();
        check_convertible<bmltb::class_type volatile, bmltb::class_type const volatile&&>();
        
        check_not_convertible_cv<bmltb::class_type, void>();
        check_not_convertible_cv<bmltb::class_type, int>();
        
        check_not_convertible<bmltb::class_type volatile, bmltb::class_type>();
        check_not_convertible<bmltb::class_type volatile, bmltb::class_type const>();
        check_not_convertible<bmltb::class_type volatile, bmltb::class_type volatile>();
        check_not_convertible<bmltb::class_type volatile, bmltb::class_type const volatile>();
        check_not_convertible<bmltb::class_type const volatile, bmltb::class_type>();
        check_not_convertible<bmltb::class_type const volatile, bmltb::class_type const>();
        check_not_convertible<bmltb::class_type const volatile, bmltb::class_type volatile>();
        check_not_convertible<bmltb::class_type const volatile, bmltb::class_type const volatile>();
        
        check_not_convertible_cv<bmltb::class_type, bmltb::class_type*>();
        check_not_convertible_cv<bmltb::class_type, bmltb::class_type const volatile*>();
        check_not_convertible_cv<bmltb::class_type, bmltb::class_type[]>();
        check_not_convertible_cv<bmltb::class_type, bmltb::class_type[3]>();
        check_not_convertible_cv<bmltb::class_type, bmltb::class_type(&)[3]>();
        check_not_convertible_cv<bmltb::class_type, bmltb::class_type(*)[3]>();
        
        check_not_convertible<bmltb::class_type, bmltb::class_type&>();
        check_not_convertible<bmltb::class_type, bmltb::class_type volatile&>();
        check_not_convertible<bmltb::class_type, bmltb::class_type const volatile&>();
        check_not_convertible<bmltb::class_type const, bmltb::class_type&>();
        check_not_convertible<bmltb::class_type const, bmltb::class_type volatile&>();
        check_not_convertible<bmltb::class_type const, bmltb::class_type const volatile&>();
        check_not_convertible<bmltb::class_type volatile, bmltb::class_type&>();
        check_not_convertible<bmltb::class_type volatile, bmltb::class_type const&>();
        check_not_convertible<bmltb::class_type volatile, bmltb::class_type volatile&>();
        check_not_convertible<bmltb::class_type volatile, bmltb::class_type const volatile&>();
        
        check_not_convertible<bmltb::class_type const, bmltb::class_type&&>();
        check_not_convertible<bmltb::class_type volatile, bmltb::class_type const&&>();
        check_not_convertible<bmltb::class_type const volatile, bmltb::class_type const&&>();
        
        check_not_convertible_cv<bmltb::class_type, bmltb::enum_class>();
        check_not_convertible_cv<bmltb::class_type, bmltb::union_type>();
        check_not_convertible_cv<bmltb::class_type, bmltb::class_type bmltb::class_type::*>();
        
        check_not_convertible_cv<bmltb::class_type, auto () -> void>();
        check_not_convertible_cv<bmltb::class_type, auto (*)() -> void>();
        check_not_convertible_cv<bmltb::class_type, auto (&)() -> void>();
        check_not_convertible_cv<bmltb::class_type,
            auto (bmltb::class_type) const && noexcept -> void>();
        check_not_convertible_cv<bmltb::class_type, auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that lvalue references to fundamental types are not convertible to any type except:
    //   1. Any cv-qualified or unqualified version of type being referenced.
    //   2. A lvalue reference to the (possibly more cv-qualified version of) type being referenced.
    {
        check_convertible_cv<int&, int>();
        check_convertible_cv<int const&, int>();
        check_convertible_cv<int volatile&, int>();
        check_convertible_cv<int const volatile&, int>();
        
        check_convertible<int&, int&>();
        check_convertible<int&, int const&>();
        check_convertible<int&, int volatile&>();
        check_convertible<int&, int const volatile&>();
        check_convertible<int const&, int const&>();
        check_convertible<int const&, int const volatile&>();
        
        check_not_convertible_cv<int&, void>();
        check_not_convertible_cv<int const&, void>();
        check_not_convertible_cv<int volatile&, void>();
        check_not_convertible_cv<int const volatile&, void>();
        
        check_not_convertible<int const&, int&>();
        check_not_convertible<int const&, int volatile&>();
        check_not_convertible<int volatile&, int&>();
        check_not_convertible<int volatile&, int const&>();
        check_not_convertible<int const volatile&, int&>();
        
        check_not_convertible<int&, int&&>();
        check_not_convertible<int&, int const&&>();
        check_not_convertible<int&, int const volatile&&>();
        check_not_convertible<int const&, int&&>();
        check_not_convertible<int const&, int const&&>();
        check_not_convertible<int const&, int const volatile&&>();
        check_not_convertible<int volatile&, int const&&>();
        check_not_convertible<int volatile&, int const volatile&&>();
        check_not_convertible<int const volatile&, int const volatile&&>();
        
        check_not_convertible_cv<int&, int*>();
        check_not_convertible_cv<int const&, int*>();
        check_not_convertible_cv<int const&, int const*>();
        check_not_convertible_cv<int volatile&, int*>();
        check_not_convertible_cv<int volatile&, int volatile*>();
        check_not_convertible_cv<int const volatile&, int*>();
        check_not_convertible_cv<int const volatile&, int const volatile*>();
        
        check_not_convertible_cv<int&, int[]>();
        check_not_convertible_cv<int&, int[3]>();
        check_not_convertible_cv<int&, int(&)[3]>();
        check_not_convertible_cv<int&, int(*)[3]>();
        
        check_not_convertible_cv<int&, bmltb::class_type>();
        check_not_convertible_cv<int&, bmltb::enum_class>();
        check_not_convertible_cv<int&, bmltb::union_type>();
        check_not_convertible_cv<int&, int bmltb::class_type::*>();
        
        check_not_convertible_cv<int&, auto () -> void>();
        check_not_convertible_cv<int&, auto (*)() -> void>();
        check_not_convertible_cv<int&, auto (&)() -> void>();
        check_not_convertible_cv<int&, auto (int) const && noexcept -> void>();
        check_not_convertible_cv<int&, auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that lvalue references to compound types are not convertible to any type except:
    //   1. Any cv-qualified or unqualified version of type being referenced, unless the type being
    //      referred to is already volatile-qualified. References to volatile-qualified types cannot
    //      be converted to the type being referred to, regardless of the cv-qualifiation of the
    //      target type.
    //   2. A lvalue reference to the (possibly more cv-qualified version of) type being referenced.
    {
        check_convertible_cv<bmltb::class_type&, bmltb::class_type>();
        check_convertible_cv<bmltb::class_type const&, bmltb::class_type>();
        
        check_convertible<bmltb::class_type&, bmltb::class_type&>();
        check_convertible<bmltb::class_type&, bmltb::class_type const&>();
        check_convertible<bmltb::class_type&, bmltb::class_type volatile&>();
        check_convertible<bmltb::class_type&, bmltb::class_type const volatile&>();
        check_convertible<bmltb::class_type const&, bmltb::class_type const&>();
        check_convertible<bmltb::class_type const&, bmltb::class_type const volatile&>();
        check_convertible<bmltb::class_type volatile&, bmltb::class_type volatile&>();
        check_convertible<bmltb::class_type volatile&, bmltb::class_type const volatile&>();
        
        check_not_convertible_cv<bmltb::class_type&, void>();
        check_not_convertible_cv<bmltb::class_type const&, void>();
        check_not_convertible_cv<bmltb::class_type volatile&, void>();
        check_not_convertible_cv<bmltb::class_type const volatile&, void>();
        
        check_not_convertible_cv<bmltb::class_type&, int>();
        check_not_convertible_cv<bmltb::class_type&, double>();
        
        check_not_convertible_cv<bmltb::class_type volatile&, bmltb::class_type>();
        check_not_convertible_cv<bmltb::class_type const volatile&, bmltb::class_type>();
        
        check_not_convertible<bmltb::class_type const&, bmltb::class_type&>();
        check_not_convertible<bmltb::class_type const&, bmltb::class_type volatile&>();
        check_not_convertible<bmltb::class_type volatile&, bmltb::class_type&>();
        check_not_convertible<bmltb::class_type volatile&, bmltb::class_type const&>();
        
        check_not_convertible<bmltb::class_type&, bmltb::class_type&&>();
        check_not_convertible<bmltb::class_type&, bmltb::class_type const&&>();
        check_not_convertible<bmltb::class_type&, bmltb::class_type const volatile&&>();
        check_not_convertible<bmltb::class_type const&, bmltb::class_type&&>();
        check_not_convertible<bmltb::class_type const&, bmltb::class_type const&&>();
        check_not_convertible<bmltb::class_type const&, bmltb::class_type const volatile&&>();
        check_not_convertible<bmltb::class_type volatile&, bmltb::class_type&&>();
        check_not_convertible<bmltb::class_type volatile&, bmltb::class_type const&&>();
        check_not_convertible<bmltb::class_type volatile&, bmltb::class_type const volatile&&>();
        check_not_convertible<bmltb::class_type const volatile&, bmltb::class_type&&>();
        check_not_convertible<bmltb::class_type const volatile&, bmltb::class_type const&&>();
        check_not_convertible<bmltb::class_type const volatile&,
            bmltb::class_type const volatile&&>();
        
        check_not_convertible_cv<bmltb::class_type&, bmltb::class_type*>();
        check_not_convertible_cv<bmltb::class_type&, bmltb::class_type[]>();
        check_not_convertible_cv<bmltb::class_type&, bmltb::class_type[3]>();
        check_not_convertible_cv<bmltb::class_type&, bmltb::class_type(&)[3]>();
        check_not_convertible_cv<bmltb::class_type&, bmltb::class_type(*)[3]>();
        
        check_not_convertible_cv<bmltb::class_type&, bmltb::enum_class>();
        check_not_convertible_cv<bmltb::class_type&, bmltb::union_type>();
        check_not_convertible_cv<bmltb::class_type&, bmltb::class_type bmltb::class_type::*>();
        
        check_not_convertible_cv<bmltb::class_type&, auto () -> void>();
        check_not_convertible_cv<bmltb::class_type&, auto (*)() -> void>();
        check_not_convertible_cv<bmltb::class_type&, auto (&)() -> void>();
        check_not_convertible_cv<bmltb::class_type&,
            auto (bmltb::class_type) const && noexcept -> void>();
        check_not_convertible_cv<bmltb::class_type&, auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that rvalue references to fundamental types are not convertible to any type except:
    //   1. Any cv-qualified or unqualified version of type being referenced.
    //   2. Lvalue references to a const-qualified (but not volatile-qualified) version of the type
    //      being referenced.
    //   3. Rvalue references to more cv-qualified versions of the type being referenced.
    {
        check_convertible_cv<int&&, int>();
        check_convertible_cv<int const&&, int>();
        check_convertible_cv<int volatile&&, int>();
        check_convertible_cv<int const volatile&&, int>();
        
        check_convertible<int&&, int const&>();
        check_convertible<int const&&, int const&>();
        
        check_convertible<int&&, int&&>();
        check_convertible<int&&, int const&&>();
        check_convertible<int&&, int volatile&&>();
        check_convertible<int&&, int const volatile&&>();
        check_convertible<int const&&, int const&&>();
        check_convertible<int const&&, int const volatile&&>();
        check_convertible<int volatile&&, int volatile&&>();
        check_convertible<int volatile&&, int const volatile&&>();
        check_convertible<int const volatile&&, int const volatile&&>();
        
        check_not_convertible_cv<int&&, void>();
        check_not_convertible_cv<int const&&, void>();
        check_not_convertible_cv<int volatile&&, void>();
        check_not_convertible_cv<int const volatile&&, void>();
        
        check_not_convertible<int const&&, int&&>();
        check_not_convertible<int const&&, int volatile&&>();
        check_not_convertible<int volatile&&, int&&>();
        check_not_convertible<int volatile&&, int const&&>();
        check_not_convertible<int const volatile&&, int&&>();
        check_not_convertible<int const volatile&&, int const&&>();
        check_not_convertible<int const volatile&&, int volatile&&>();
        
        check_not_convertible<int&&, int&>();
        check_not_convertible<int&&, int volatile&>();
        check_not_convertible<int&&, int const volatile&>();
        check_not_convertible<int const&&, int&>();
        check_not_convertible<int const&&, int volatile&>();
        check_not_convertible<int const&&, int const volatile&>();
        check_not_convertible<int volatile&&, int&>();
        check_not_convertible<int volatile&&, int const&>();
        check_not_convertible<int volatile&&, int volatile&>();
        check_not_convertible<int volatile&&, int const volatile&>();
        check_not_convertible<int const volatile&&, int&>();
        check_not_convertible<int const volatile&&, int const&>();
        check_not_convertible<int const volatile&&, int volatile&>();
        check_not_convertible<int const volatile&&, int const volatile&>();
        
        check_not_convertible_cv<int&&, int*>();
        check_not_convertible_cv<int&&, int const*>();
        check_not_convertible_cv<int const&&, int*>();
        check_not_convertible_cv<int const&&, int const*>();
        check_not_convertible_cv<int volatile&&, int*>();
        check_not_convertible_cv<int volatile&&, int volatile*>();
        check_not_convertible_cv<int const volatile&&, int*>();
        check_not_convertible_cv<int const volatile&&, int const volatile*>();
        
        check_not_convertible_cv<int&&, int[]>();
        check_not_convertible_cv<int&&, int[3]>();
        check_not_convertible_cv<int&&, int(&)[3]>();
        check_not_convertible_cv<int&&, int(*)[3]>();
        
        check_not_convertible_cv<int&&, bmltb::class_type>();
        check_not_convertible_cv<int&&, bmltb::enum_class>();
        check_not_convertible_cv<int&&, bmltb::union_type>();
        check_not_convertible_cv<int&&, int bmltb::class_type::*>();
        
        check_not_convertible_cv<int&&, auto () -> void>();
        check_not_convertible_cv<int&&, auto (*)() -> void>();
        check_not_convertible_cv<int&&, auto (&)() -> void>();
        check_not_convertible_cv<int&&, auto (int) const && noexcept -> void>();
        check_not_convertible_cv<int&&, auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that rvalue references to compound types are not convertible to any type except:
    //   1. Any cv-qualified or unqualified version of type being referenced, unless the type being
    //      referred to is already volatile-qualified. References to volatile-qualified types cannot
    //      be converted to the type being referred to, regardless of the cv-qualifiation of the
    //      target type.
    //   2. Lvalue references to a const-qualified (but not volatile-qualified) version of the type
    //      being referenced.
    //   3. Rvalue references to more cv-qualified versions of the type being referenced.
    {
        check_convertible_cv<bmltb::class_type&&, bmltb::class_type>();
        check_convertible_cv<bmltb::class_type const&&, bmltb::class_type>();
        
        check_convertible<bmltb::class_type&&, bmltb::class_type const&>();
        check_convertible<bmltb::class_type const&&, bmltb::class_type const&>();
        
        check_convertible<bmltb::class_type&&, bmltb::class_type&&>();
        check_convertible<bmltb::class_type&&, bmltb::class_type const&&>();
        check_convertible<bmltb::class_type&&, bmltb::class_type volatile&&>();
        check_convertible<bmltb::class_type&&, bmltb::class_type const volatile&&>();
        check_convertible<bmltb::class_type const&&, bmltb::class_type const&&>();
        check_convertible<bmltb::class_type const&&, bmltb::class_type const volatile&&>();
        check_convertible<bmltb::class_type volatile&&, bmltb::class_type volatile&&>();
        check_convertible<bmltb::class_type volatile&&, bmltb::class_type const volatile&&>();
        check_convertible<bmltb::class_type const volatile&&, bmltb::class_type const volatile&&>();
        
        check_not_convertible_cv<bmltb::class_type&&, void>();
        check_not_convertible_cv<bmltb::class_type const&&, void>();
        check_not_convertible_cv<bmltb::class_type volatile&&, void>();
        check_not_convertible_cv<bmltb::class_type const volatile&&, void>();
        
        check_not_convertible_cv<bmltb::class_type&&, int>();
        check_not_convertible_cv<bmltb::class_type&&, double>();
        
        check_not_convertible_cv<bmltb::class_type volatile&&, bmltb::class_type>();
        check_not_convertible_cv<bmltb::class_type const volatile&&, bmltb::class_type>();
        
        check_not_convertible<bmltb::class_type const&&, bmltb::class_type&&>();
        check_not_convertible<bmltb::class_type const&&, bmltb::class_type volatile&&>();
        check_not_convertible<bmltb::class_type volatile&&, bmltb::class_type&&>();
        check_not_convertible<bmltb::class_type volatile&&, bmltb::class_type const&&>();
        check_not_convertible<bmltb::class_type const volatile&&, bmltb::class_type&&>();
        check_not_convertible<bmltb::class_type const volatile&&, bmltb::class_type const&&>();
        check_not_convertible<bmltb::class_type const volatile&&, bmltb::class_type volatile&&>();
        
        check_not_convertible<bmltb::class_type&&, bmltb::class_type&>();
        check_not_convertible<bmltb::class_type&&, bmltb::class_type volatile&>();
        check_not_convertible<bmltb::class_type&&, bmltb::class_type const volatile&>();
        check_not_convertible<bmltb::class_type const&&, bmltb::class_type&>();
        check_not_convertible<bmltb::class_type const&&, bmltb::class_type volatile&>();
        check_not_convertible<bmltb::class_type const&&, bmltb::class_type const volatile&>();
        check_not_convertible<bmltb::class_type volatile&&, bmltb::class_type&>();
        check_not_convertible<bmltb::class_type volatile&&, bmltb::class_type const&>();
        check_not_convertible<bmltb::class_type volatile&&, bmltb::class_type volatile&>();
        check_not_convertible<bmltb::class_type volatile&&, bmltb::class_type const volatile&>();
        check_not_convertible<bmltb::class_type const volatile&&, bmltb::class_type&>();
        check_not_convertible<bmltb::class_type const volatile&&, bmltb::class_type const&>();
        check_not_convertible<bmltb::class_type const volatile&&, bmltb::class_type volatile&>();
        check_not_convertible<bmltb::class_type const volatile&&,
            bmltb::class_type const volatile&>();
        
        check_not_convertible_cv<bmltb::class_type&&, bmltb::class_type*>();
        check_not_convertible_cv<bmltb::class_type&&, bmltb::class_type const*>();
        check_not_convertible_cv<bmltb::class_type const&&, bmltb::class_type*>();
        check_not_convertible_cv<bmltb::class_type const&&, bmltb::class_type const*>();
        check_not_convertible_cv<bmltb::class_type volatile&&, bmltb::class_type*>();
        check_not_convertible_cv<bmltb::class_type volatile&&, bmltb::class_type volatile*>();
        check_not_convertible_cv<bmltb::class_type const volatile&&, bmltb::class_type*>();
        check_not_convertible_cv<bmltb::class_type const volatile&&,
            bmltb::class_type const volatile*>();
        
        check_not_convertible_cv<bmltb::class_type&&, bmltb::class_type[]>();
        check_not_convertible_cv<bmltb::class_type&&, bmltb::class_type[3]>();
        check_not_convertible_cv<bmltb::class_type&&, bmltb::class_type(&)[3]>();
        check_not_convertible_cv<bmltb::class_type&&, bmltb::class_type(*)[3]>();
        
        check_not_convertible_cv<bmltb::class_type&&, bmltb::enum_class>();
        check_not_convertible_cv<bmltb::class_type&&, bmltb::union_type>();
        check_not_convertible_cv<bmltb::class_type&&, bmltb::class_type bmltb::class_type::*>();
        
        check_not_convertible_cv<bmltb::class_type&&, auto () -> void>();
        check_not_convertible_cv<bmltb::class_type&&, auto (*)() -> void>();
        check_not_convertible_cv<bmltb::class_type&&, auto (&)() -> void>();
        check_not_convertible_cv<bmltb::class_type&&,
            auto (bmltb::class_type) const && noexcept -> void>();
        check_not_convertible_cv<bmltb::class_type&&, auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that pointers are not convertible to any type except pointers to equally or more
    // cv-qualified versions of the type being pointed to.
    {
        // Fundamental types
        check_convertible_cv<int*, int*>();
        check_convertible_cv<int*, int const*>();
        check_convertible_cv<int*, int volatile*>();
        check_convertible_cv<int*, int const volatile*>();
        check_convertible_cv<int const*, int const*>();
        check_convertible_cv<int const*, int const volatile*>();
        check_convertible_cv<int volatile*, int volatile*>();
        check_convertible_cv<int volatile*, int const volatile*>();
        check_convertible_cv<int const volatile*, int const volatile*>();
        
        check_not_convertible_cv<int*, void>();
        check_not_convertible_cv<int const*, void>();
        check_not_convertible_cv<int volatile*, void>();
        check_not_convertible_cv<int const volatile*, void>();
        
        check_not_convertible_cv<int const*, int*>();
        check_not_convertible_cv<int const*, int volatile*>();
        check_not_convertible_cv<int volatile*, int*>();
        check_not_convertible_cv<int volatile*, int const*>();
        check_not_convertible_cv<int const volatile*, int*>();
        check_not_convertible_cv<int const volatile*, int const*>();
        check_not_convertible_cv<int const volatile*, int volatile*>();
        
        check_not_convertible_cv<int*, int>();
        check_not_convertible_cv<int*, int[]>();
        check_not_convertible_cv<int*, int[3]>();
        check_not_convertible_cv<int*, int(&)[3]>();
        check_not_convertible_cv<int*, int(*)[3]>();
        
        check_not_convertible_cv<int*, bmltb::class_type>();
        check_not_convertible_cv<int*, bmltb::enum_class>();
        check_not_convertible_cv<int*, bmltb::union_type>();
        check_not_convertible_cv<int*, int bmltb::class_type::*>();
        
        check_not_convertible_cv<int*, auto () -> void>();
        check_not_convertible_cv<int*, auto (*)() -> void>();
        check_not_convertible_cv<int*, auto (&)() -> void>();
        check_not_convertible_cv<int*, auto (int) const && noexcept -> void>();
        check_not_convertible_cv<int*, auto (bmltb::class_type::*)() -> void>();
        
        // Compound types
        check_convertible_cv<bmltb::class_type*, bmltb::class_type*>();
        check_convertible_cv<bmltb::class_type*, bmltb::class_type const*>();
        check_convertible_cv<bmltb::class_type*, bmltb::class_type volatile*>();
        check_convertible_cv<bmltb::class_type*, bmltb::class_type const volatile*>();
        check_convertible_cv<bmltb::class_type const*, bmltb::class_type const*>();
        check_convertible_cv<bmltb::class_type const*, bmltb::class_type const volatile*>();
        check_convertible_cv<bmltb::class_type volatile*, bmltb::class_type volatile*>();
        check_convertible_cv<bmltb::class_type volatile*, bmltb::class_type const volatile*>();
        check_convertible_cv<bmltb::class_type const volatile*,
            bmltb::class_type const volatile*>();
        
        check_not_convertible_cv<bmltb::class_type*, void>();
        check_not_convertible_cv<bmltb::class_type const*, void>();
        check_not_convertible_cv<bmltb::class_type volatile*, void>();
        check_not_convertible_cv<bmltb::class_type const volatile*, void>();
        
        check_not_convertible_cv<bmltb::class_type*, int>();
        check_not_convertible_cv<bmltb::class_type*, double>();
        
        check_not_convertible_cv<bmltb::class_type const*, bmltb::class_type*>();
        check_not_convertible_cv<bmltb::class_type const*, bmltb::class_type volatile*>();
        check_not_convertible_cv<bmltb::class_type volatile*, bmltb::class_type*>();
        check_not_convertible_cv<bmltb::class_type volatile*, bmltb::class_type const*>();
        check_not_convertible_cv<bmltb::class_type const volatile*, bmltb::class_type*>();
        check_not_convertible_cv<bmltb::class_type const volatile*, bmltb::class_type const*>();
        check_not_convertible_cv<bmltb::class_type const volatile*, bmltb::class_type volatile*>();
        
        check_not_convertible_cv<bmltb::class_type*, bmltb::class_type>();
        check_not_convertible_cv<bmltb::class_type*, bmltb::class_type[]>();
        check_not_convertible_cv<bmltb::class_type*, bmltb::class_type[3]>();
        check_not_convertible_cv<bmltb::class_type*, bmltb::class_type(&)[3]>();
        check_not_convertible_cv<bmltb::class_type*, bmltb::class_type(*)[3]>();
        
        check_not_convertible_cv<bmltb::class_type*, bmltb::enum_class>();
        check_not_convertible_cv<bmltb::class_type*, bmltb::union_type>();
        check_not_convertible_cv<bmltb::class_type*, bmltb::class_type bmltb::class_type::*>();
        
        check_not_convertible_cv<bmltb::class_type*, auto () -> void>();
        check_not_convertible_cv<bmltb::class_type*, auto (*)() -> void>();
        check_not_convertible_cv<bmltb::class_type*, auto (&)() -> void>();
        check_not_convertible_cv<bmltb::class_type*,
            auto (bmltb::class_type) const && noexcept -> void>();
        check_not_convertible_cv<bmltb::class_type*, auto (bmltb::class_type::*)() -> void>();
    }
    
    // Check that is_convertible considers user-defined implicit conversions.
    {
        check_convertible_cv<int, implicit_conv>();
        check_convertible_cv<int&, implicit_conv>();
        check_convertible_cv<int&&, implicit_conv>();
        
        check_convertible_cv<int*, implicit_conv>();
        check_convertible_cv<int*&, implicit_conv>();
        check_convertible_cv<int*&&, implicit_conv>();
        
        check_convertible<int[3], implicit_conv>();
        check_convertible<int[3], implicit_conv const>();
        check_convertible<int[3], implicit_conv volatile>();
        check_convertible<int[3], implicit_conv const volatile>();
        check_convertible<int(&)[3], implicit_conv>();
        check_convertible<int(&)[3], implicit_conv const>();
        check_convertible<int(&)[3], implicit_conv volatile>();
        check_convertible<int(&)[3], implicit_conv const volatile>();
        check_convertible<int(&&)[3], implicit_conv>();
        check_convertible<int(&&)[3], implicit_conv const>();
        check_convertible<int(&&)[3], implicit_conv volatile>();
        check_convertible<int(&&)[3], implicit_conv const volatile>();
    }
    
    // Check that is_convertible ignores explicit conversions.
    {
        check_not_convertible_cv<int, explicit_conv>();
        check_not_convertible_cv<int&, explicit_conv>();
        check_not_convertible_cv<int&&, explicit_conv>();
        
        check_not_convertible_cv<int*, explicit_conv>();
        check_not_convertible_cv<int*&, explicit_conv>();
        check_not_convertible_cv<int*&&, explicit_conv>();
        
        check_not_convertible_cv<int[3], explicit_conv>();
        check_not_convertible_cv<int(&)[3], explicit_conv>();
        check_not_convertible_cv<int(&&)[3], explicit_conv>();
    }
    
    // Check that is_convertible considers access control.
    {
        check_not_convertible_cv<int, access_check>();
        
        check_not_convertible_cv<access_check&, access_check>();
        check_not_convertible_cv<access_check const&, access_check>();
    }
    
    // Check that is_convertible does not do any unnecessary instantiations.
    {
        check_convertible_cv<do_not_instantiate<int>*, do_not_instantiate<int>*>();
    }
    
    return 0;
}
