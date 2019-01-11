//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/detected_ty.hpp>
#include <bml/type_traits/is_same.hpp>

template <typename T>
using foo_type = typename T::foo;

struct has_foo
{
    using foo = int;
};

struct no_foo {};

auto test_main() noexcept -> int
{
    // Check that detected_ty is the type named by Op when detection succeeds.
    {
        static_assert(bml::is_same_v<bml::detected_ty<foo_type, has_foo>, typename has_foo::foo>);
    }
    
    // Check that detected_ty names nonesuch when detection fails.
    {
        static_assert(bml::is_same_v<bml::detected_ty<foo_type, no_foo>, bml::nonesuch>);
    }

    return 0;
}
