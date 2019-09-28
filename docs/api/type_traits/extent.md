# `<bml/type_traits/extent.hpp>`
#### Table of Contents
- [`extent`](#extent)

## `extent`
```c++
template <typename T, int N = 0>
struct extent;

template <typename T, int N = 0>
constexpr auto extent_v = ptrdiff_t(extent<T, N>::value);
```
Obtains the number of elements along the `N`-th dimension of an array type `T`. This has a base
characteristic of `bml::integral_constant<ptrdiff_t, E>`, where `E` is:

- The number of elements along the `N`-th dimension of `T` if `T` is an array type, `N` is in the
  range `[0, bml::rank_v<T>)`, and the `N`-th dimension of `T` is not of unknown bound (e.g. `int[]`
  for `N == 0`).
- `0` otherwise.

If `N` is negative, the program is ill-formed.

Both `extent` and `extent_v` are similar to `std::extent` and `std::extent_v`, respectively, except
that they expose the extent as as `ptrdiff_t` instead of `size_t`, and `N`'s type is `int` instead
of `unsigned`.

#### Public base classes
```c++
bml::integral_constant<ptrdiff_t, E>
```
`E` is:

- The number of elements along the `N`-th dimension of `T` if `T` is an array type, `N` is in the
  range `[0, bml::rank_v<T>)`, and the `N`-th dimension of `T` is not of unknown bound.
- `0` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
