//
// Copyright (c) 2019 Wee Loong Kuan
//
// BareMetalLib is based on libc++ (https://libcxx.llvm.org/).
// 
// This file is licensed under under the Apache License v2.0 with LLVM Exceptions. For more details,
// see the LICENSE.md file in the top-level directory of this distribution, or copy at 
// https://llvm.org/LICENSE.txt.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
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
// Placement new definitions.
//
// The testbench is compiled without libc++, so these definitions are intended to stand-in for those
// typically provided by libc++'s <new>.
//
// Note: Hopefully, this is not UB - technically, this is not displacing the standard library's
// placement new since the testbench does not bring in libc++.
//
[[nodiscard]] auto operator new(::size_t, void* ptr) noexcept -> void*
{
    return ptr;
}

[[nodiscard]] auto operator new[](::size_t, void* ptr) noexcept -> void*
{
    return ptr;
}

//
// A bare-bones _start() which only invokes test_main() and exits with its return value.
//
auto test_main() noexcept -> int;
extern "C" [[noreturn]] auto _start() noexcept -> void
{
    constexpr auto EXIT_SYSCALL_NUM = 1;
    
    auto ret = test_main();
    __asm__ ("int $0x80"
        :
        : "a" (EXIT_SYSCALL_NUM), "b" (ret)
        :);
    
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
        constexpr auto WRITE_SYSCALL_NUM = 4;
        constexpr auto STDOUT_NUM = 1;
        
        __asm__ ("int $0x80"
            :
            : "a" (WRITE_SYSCALL_NUM), "b" (STDOUT_NUM), "c" (buf), "d" (size)
            : "memory");
    }
}
