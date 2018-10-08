//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>

//
// A bare-bones _start() which only invokes test_main() and exits with its return value.
//
auto test_main() noexcept -> int;
extern "C" [[noreturn]] auto _start() noexcept -> void
{
    constexpr auto EXIT_SYSCALL_NUM = 60;
    
    auto ret = test_main();
    __asm__ ("syscall"
        :
        : "a" (EXIT_SYSCALL_NUM), "D" (ret)
        : "rcx", "r11", "cc");
    
    __builtin_unreachable();
}

namespace bmltb
{
    //
    // Implementation of display_ascii() that punts the input string to standard out via the write
    // syscall. Errors are swallowed.
    //
    auto display_ascii(char const* buf, ::size_t size) noexcept -> void
    {
        constexpr auto WRITE_SYSCALL_NUM = 1;
        constexpr auto STDOUT_NUM = 1;
        
        __asm__ ("syscall"
            :
            : "a" (WRITE_SYSCALL_NUM), "D" (STDOUT_NUM), "S" (buf), "d" (size)
            : "rcx", "r11", "cc", "memory");
    }
}
