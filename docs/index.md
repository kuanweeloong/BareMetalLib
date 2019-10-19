# BareMetalLib Documentation
#### Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [API Reference](#api-reference)

## Installation
BareMetalLib (BML) offers two installation methods: direct-copying and CMake.

#### Direct-copy
BML is a header-only library, so you can just copy the `include/bml` directory into your project's
include path(s) to start using it.

#### CMake
BML is available as a CMake `INTERFACE` library - just reference `BareMetalLib::bml` in your CMake
file. You can make CMake aware of BML by:

- Installing BML as a system-wide CMake package (via `cmake $BML_SRC_PATH && make install`, where
  `$BML_SRC_PATH` contains the path to BML's source tree on your system) and then using
  `find_package` in your CMake file(s).

  > ```cmake
  > find_package(BareMetalLib 0.1.0 REQUIRED)
  > target_link_libraries(my_project BareMetalLib::bml)
  > ```

- Embedding the entire BML source tree into your project's source tree (e.g. via git submodules) and
  then using `add_subdirectory` in your CMake file(s).

  > ```cmake
  > add_subdirectory(BareMetalLib)
  > target_link_libraries(my_project BareMetalLib::bml)
  > ```

## Usage
BML's API is very similar (although *not* identical) to that of the C++ Standard Library. It is
comprised of several smaller libraries, which are described below:
                        
| Library       | Description                                                      |
| ------------- | ---------------------------------------------------------------- |
| `basic_types` | Basic non-keyword types (e.g. types similar to `std::nullptr_t`) |
| `containers`  | Object containers                                                |
| `type_traits` | Type traits for metaprogramming                                  |
| `utilities`   | Utility functions and classes                                    |

BML is structured as follows:

- Each library has an associated `.hpp` header and directory named after itself in the root of the
  BML include directory. For instance, the `containers` library has a `containers.hpp` header and a
  `containers` directory located at `include/bml`.
- Every component of each library has a dedicated `.hpp` header inside the library's associated
  directory. For instance, `tuple`, a component of the `containers` library, has a header located at
  `include/bml/containers/tuple.hpp`.

Thus, to use a component from a library, you can either include the library's header or the
component's header (e.g. to use `tuple`, you can either `#include <bml/containers.hpp>` or
`#include <bml/containers/tuple.hpp>`).

Here are some usage examples:

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

## API Reference
BML's API reference is available [here](api/index.md).

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
