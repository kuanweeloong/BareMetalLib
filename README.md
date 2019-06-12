# BareMetalLib
[![Build Status](https://travis-ci.org/kuanweeloong/BareMetalLib.svg?branch=master)][1]

## Introduction
BareMetalLib (BML) is an experimental, modern C++, header-only support library for bare-metal
programming (e.g. OS kernels, embedded software). It is intended for use in environments where
exceptions are disabled and the C++ standard library cannot be used - BML aims to provide
functionality similar to that of the C++ standard library, but in a form more suited to bare-metal
programming. Namely, it eschews the use of:

- Headers from the C and C++ standard libraries, except for C11 freestanding headers
- Exceptions (BML is `noexcept` throughout)
- RTTI
- Thread-local storage
- Non-`constexpr` static objects (BML does not require any initialization at runtime)
- Dynamic allocation via global `operator new` or `operator new[]`
- Floating point operations

Apart from these bare-metal-related constraints, the following additional constraints are imposed on
BML code:

- Unsigned types cannot be used, except for bitfields. For example, sizes and indices are
  represented using `ptrdiff_t` (instead of `size_t`, which is what the C++ standard library does).
  This brings BML more in line with the [arithmetic section][2] of the C++ core guidelines.

Due to these constraints, BML is **not** a drop-in replacement for the C++ standard library.
However, other than being exception-free, user code is not expected to conform to the same
constraints.

BML is based on [libc++][3]. This is a learning project, so please be patient!

## Requirements
BML requires a C++17 conforming compiler. It is tested on the following platforms:

| Architecture | OS                      | Compiler    |
| ------------ | ----------------------- | ----------- |
| x86_64       | Debian Buster (*amd64*) | Clang 6.0.1 |
| x86_64       | Debian Buster (*amd64*) | GCC 8.3.0   |
| i386         | Debian Buster (*i386*)  | Clang 6.0.1 |
| i386         | Debian Buster (*i386*)  | GCC 8.3.0   |
| aarch64      | Debian Buster (*arm64*) | Clang 6.0.1 |
| aarch64      | Debian Buster (*arm64*) | GCC 8.3.0   |

## License
BML is licensed under the Apache 2.0 License with LLVM exceptions. For more details, see
[LICENSE.md](LICENSE.md).

[1]: https://travis-ci.org/kuanweeloong/BareMetalLib
[2]: https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Res-mix
[3]: https://libcxx.llvm.org/
