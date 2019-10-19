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
| armv7l       | Debian Buster (*armhf*) | Clang 6.0.1 |
| armv7l       | Debian Buster (*armhf*) | GCC 8.3.0   |
| armv5l       | Debian Buster (*armel*) | Clang 6.0.1 |
| armv5l       | Debian Buster (*armel*) | GCC 8.3.0   |

## Quickstart
Copy `include/bml` into your project's include path and include a BML header to get started. Some
usage examples:

#### Finding the minimum and maximum of several integers
This example find the minimum and maximum of 4 integers and returns them in a tuple.

> ```c++
> #include <bml/containers.hpp>
> #include <bml/utilities.hpp>
> 
> auto find_minmax(int i1, int i2, int i3, int i4) noexcept -> bml::tuple<int, int>
> {
>     auto min = bml::min(i1, i2, i3, i4);
>     auto max = bml::max(i1, i2, i3, i4);
> 
>     return bml::tuple(min, max);
> }
> ```

#### Selecting an appropriate overload using the detection idiom
This example defines a `do_foo` function which calls its argument's member `foo` function if that
argument's type defines such a function. Otherwise, it performs a generic `foo` action on its
argument.

> ```c++
> #include <bml/type_traits/is_detected.hpp>
> #include <bml/type_traits/enable_if.hpp>
> #include <bml/utilities/declval.hpp>
> 
> template <typename T>
> using has_foo = decltype(bml::declval<T>().foo());
> 
> template <typename T>
> auto do_foo(T&& arg) noexcept -> bml::enable_if_ty<bml::is_detected_v<has_foo, T>>
> {
>     arg.foo();
> }
> 
> template <typename T>
> auto do_foo(T&& arg) noexcept -> bml::enable_if_ty<!bml::is_detected_v<has_foo, T>>
> {
>     // Do some generic foo action on arg. This is called for argument types that do not have a
>     // custom foo() member function.
> }
> ```

## Documentation
BML's documentation can be found in the [`docs/`](docs/) directory, or [online][4].

## License
BML's code is licensed under the [Apache 2.0 License with LLVM exceptions][5]. BML's documentation,
which encompasses all content in the `docs/` directory, is licensed under [CC BY-SA 4.0][6].

For more details, see [LICENSE.md](LICENSE.md).

[1]: https://travis-ci.org/kuanweeloong/BareMetalLib
[2]: https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Res-mix
[3]: https://libcxx.llvm.org
[4]: https://kuanweeloong.github.io/BareMetalLib
[5]: https://llvm.org/foundation/relicensing/LICENSE.txt
[6]: https://creativecommons.org/licenses/by-sa/4.0
