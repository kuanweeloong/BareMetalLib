# `<bml/type_traits/rank.hpp>`
#### Table of Contents
- [`rank`](#rank)

## `rank`
```c++
template <typename T>
struct rank;

template <typename T>
constexpr auto rank_v = ptrdiff_t(rank<T>::value);
```
Obtains the number of dimensions of an array type `T`. This has a base characteristic of
`bml::integral_constant<ptrdiff_t, N>`, where `N` is:

- The number of dimensions of `T` if `T` is an array type.
- `0` otherwise.

Both `rank` and `rank_v` are similar to `std::rank` and `std::rank_v`, respectively, except that
they expose the rank as as `ptrdiff_t` instead of `size_t`.

#### Public base classes
```c++
bml::integral_constant<ptrdiff_t, N>
```
`N` is:

- The number of dimensions of `T` if `T` is an array type.
- `0` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
