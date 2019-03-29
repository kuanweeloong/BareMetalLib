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

#include <bml_testbench.hpp>

extern "C" auto memcpy(void* dest, void const* src, ::size_t len) noexcept -> void*;
extern "C" auto memmove(void* dest, void const* src, ::size_t len) noexcept -> void*;
extern "C" auto memset(void* dest, int val, ::size_t len) noexcept -> void*;
extern "C" auto memcmp(void const* str1, void const* str2, ::size_t count) noexcept -> int;

auto test_main() noexcept -> int
{
    // Check that memcpy correctly copies the specified number of bytes from source to destination.
    {
        char src[]  = {'a', 'b', 'c', 'd'};
        char dest[] = {'z', 'z', 'z', 'z'};
        
        auto result = memcpy(dest, src, 2);
        
        bmltb_assert(src[0] == 'a');
        bmltb_assert(src[1] == 'b');
        bmltb_assert(src[2] == 'c');
        bmltb_assert(src[3] == 'd');
        
        bmltb_assert(dest[0] == 'a');
        bmltb_assert(dest[1] == 'b');
        bmltb_assert(dest[2] == 'z');
        bmltb_assert(dest[3] == 'z');
        
        bmltb_assert(result == dest);
    }
    
    // Check that memmove correctly copies the specified number of bytes from source to destination
    // when the buffers don't overlap.
    {
        char src[]  = {'a', 'b', 'c', 'd'};
        char dest[] = {'z', 'z', 'z', 'z'};
        
        auto result = memmove(dest, src, 2);
        
        bmltb_assert(src[0] == 'a');
        bmltb_assert(src[1] == 'b');
        bmltb_assert(src[2] == 'c');
        bmltb_assert(src[3] == 'd');
        
        bmltb_assert(dest[0] == 'a');
        bmltb_assert(dest[1] == 'b');
        bmltb_assert(dest[2] == 'z');
        bmltb_assert(dest[3] == 'z');
        
        bmltb_assert(result == dest);
    }
    
    // Check that memmove correctly copies the specified number of bytes from source to destination
    // when the buffers overlap.
    {
        // Destination at higher address than source.
        char buf[] = {'a', 'b', 'c', 'd', 'e', 'f'};
        auto src = buf;
        auto dest = buf + 2;
        
        auto result = memmove(dest, src, 3);
        
        bmltb_assert(buf[0] == 'a');
        bmltb_assert(buf[1] == 'b');
        bmltb_assert(buf[2] == 'a');
        bmltb_assert(buf[3] == 'b');
        bmltb_assert(buf[4] == 'c');
        bmltb_assert(buf[5] == 'f');
        
        bmltb_assert(result == dest);
        
        // Destination at lower address than source.
        char buf2[] = {'a', 'b', 'c', 'd', 'e', 'f'};
        src = buf2 + 2;
        dest = buf2;
        
        result = memmove(dest, src, 3);
        
        bmltb_assert(buf2[0] == 'c');
        bmltb_assert(buf2[1] == 'd');
        bmltb_assert(buf2[2] == 'e');
        bmltb_assert(buf2[3] == 'd');
        bmltb_assert(buf2[4] == 'e');
        bmltb_assert(buf2[5] == 'f');
        
        bmltb_assert(result == dest);
    }
    
    // Check that memset sets the specified number of bytes from the start of the input buffer to
    // the specified value.
    {
        char buf[] = {'a', 'b', 'c'};
        
        auto result = memset(buf, 'z', 2);
        
        bmltb_assert(buf[0] == 'z');
        bmltb_assert(buf[1] == 'z');
        bmltb_assert(buf[2] == 'c');
        
        bmltb_assert(result == buf);
    }
    
    // Check that memcmp correctly compares the specified number of bytes in both buffers.
    {
        char buf[] = {'a', 'b', 'c'};
        char buf_lt[] = {'a', 'b', 'z'};
        char buf_gt[] = {'a', 'b', 'a'};
        
        bmltb_assert(memcmp(buf, buf_lt, 2) == 0);
        bmltb_assert(memcmp(buf, buf_lt, 3) == -1);
        bmltb_assert(memcmp(buf, buf_gt, 3) == 1);
    }
    
    return 0;
}
