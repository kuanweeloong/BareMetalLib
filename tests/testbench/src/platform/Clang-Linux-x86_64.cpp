//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <stddef.h>
#include <bml_testbench.hpp>

//
// Clang requires the freestanding environment to provide memcpy, memmove, memset and memcmp.
//
// Note: Each function's implementation is based on their corresponding public domain code in
// libgcc.
//
extern "C" auto memcpy(void* dest, void const* src, ::size_t len) noexcept -> void*
{
    auto d = static_cast<char*>(dest);
    auto s = static_cast<char const*>(src);
    
    while (len--)
    {
        *d++ = *s++;
    }
    
    return dest;
}

extern "C" auto memmove(void* dest, void const* src, ::size_t len) noexcept -> void*
{
    auto d = static_cast<char*>(dest);
    auto s = static_cast<char const*>(src);
    
    if (d < s)
    {
        while (len--)
        {
            *d++ = *s++;
        }
    }
    else
    {
        auto last_s = s + (len - 1);
        auto last_d = d + (len - 1);
        
        while (len--)
        {
            *last_d-- = *last_s--;
        }
    }
    
    return dest;
}

extern "C" auto memset(void* dest, int val, ::size_t len) noexcept -> void*
{
    auto ptr = static_cast<unsigned char*>(dest);
    
    while (len-- > 0)
    {
        *ptr++ = val;
    }
    
    return dest;
}

extern "C" auto memcmp(void const* str1, void const* str2, ::size_t count) noexcept -> int
{
    auto s1 = static_cast<unsigned char const*>(str1);
    auto s2 = static_cast<unsigned char const*>(str2);
    
    while (count-- > 0)
    {
        if (*s1++ != *s2++)
        {
            return s1[-1] < s2[-1] ? -1 : 1;
        }
    }
    
    return 0;
}

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
