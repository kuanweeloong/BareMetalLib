# `<bml/type_traits/size_of.hpp>`
#### Table of Contents
- [`size_of`](#size_of)

## `size_of`
```c++
template <typename T>
struct size_of;

template <typename T>
constexpr auto size_of_v = ptrdiff_t(size_of<T>::value);
```
Obtains the size of `T` in bytes. This has a base characteristic of
`bml::integral_constant<ptrdiff_t, N>`, where `N` is the size of the object representation of `T` in
bytes.

If `T` is a type that is incompatible with the `sizeof` operator (e.g. incomplete types), or
`sizeof(T)` is larger than the maximum value that `ptrdiff_t` can hold, the program is ill-formed.

This serves the same purpose as the `sizeof` operator, except that this exposes the result as a
`ptrdiff_t` instead of `size_t`.

#### Public base classes
```c++
bml::integral_constant<ptrdiff_t, N>
```
`N` is the size of `T` in bytes.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
