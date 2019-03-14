# BareMetalLib
[![Build Status](
    https://travis-ci.org/kuanweeloong/BareMetalLib.svg?branch=master)](
    https://travis-ci.org/kuanweeloong/BareMetalLib)

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
- Static objects
- Dynamic allocation via global `operator new` or `operator new[]`
- Floating point operations

Due to these constraints, BML is **not** a drop-in replacement for the C++ standard library.
However, other than being exception-free, user code is not expected to conform to the same
constraints.

BML is based on [libc++](https://libcxx.llvm.org/). This is a learning project, so please be
patient!

## Requirements
BML requires a C++17 conforming compiler. It is tested on the following platforms:

| OS                 | Architecture | Compiler    | Remarks       |
| ------------------ | ------------ | ----------- | ------------- |
| Ubuntu 18.04.1 LTS | x64          | GCC 8.2.0   |               |
| Ubuntu 18.04.1 LTS | x64          | Clang 6.0.0 |               |
| Ubuntu 16.04.5 LTS | x64          | GCC 8.1.0   | Via Travis CI |
| Ubuntu 16.04.5 LTS | x64          | Clang 6.0.1 | Via Travis CI |

## License
BML is licensed under the MIT license. For more details, see [LICENSE.md](LICENSE.md).
