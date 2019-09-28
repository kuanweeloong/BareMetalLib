# `<bml/type_traits/pack_size.hpp>`
#### Table of Contents
- [`pack_size`](#pack_size)

## `pack_size`
```c++
template <typename... Ts>
struct pack_size;

template <typename... Ts>
constexpr auto pack_size_v = ptrdiff_t(pack_size<Ts...>::value);
```
Obtains the number of types in `Ts...`. This has a base characteristic of
`bml::integral_constant<ptrdiff_t, N>`, where `N` is the number of types in `Ts...`.

If `N` is negative or larger than the maximum value that `ptrdiff_t` can hold, the program is
ill-formed.

This serves the same purpose as the `sizeof...` operator, except that this exposes the result as a
`ptrdiff_t` instead of `size_t`.

#### Public base classes
```c++
bml::integral_constant<ptrdiff_t, N>
```
`N` is the number of types in `Ts...`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
