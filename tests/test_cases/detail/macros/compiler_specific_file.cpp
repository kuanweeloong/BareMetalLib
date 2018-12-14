//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/detail/macros/compiler_specific_file.hpp>
#include BML_COMPILER_SPECIFIC_FILE(compiler, compiler_specific.hpp)

auto test_main() noexcept -> int
{
    // Check that compiler_specific.hpp was successfully included.
    {
        static_assert(BMLTB_COMPILER_SPECIFIC_FILE_INCLUDED);
    }
    
    return 0;
}
