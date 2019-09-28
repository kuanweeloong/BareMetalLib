# `<bml/utilities/swap.hpp>`
#### Table of Contents
- [`swap`](#swap)

## `swap`
```c++
// Overload (1)
template <typename T>
constexpr auto swap(T& x, T& y) noexcept -> void;

// Overload (2)
template <typename T, ptrdiff_t N>
constexpr auto swap(T (&x)[N], T (&y)[N]) noexcept -> void;
```
Exchanges the values of the objects referred to by `x` and `y`.

- Overload (1) performs swapping via:
  > ```c++
  > auto temp = T(bml::move(x));
  > x = bml::move(y);
  > y = bml::move(temp);
  > ```
- Overload (2) performs swapping via `bml::swap_ranges(x, x + N, y)`.

Note that:
- Overload (1) does not participate in overload resolution unless both
  `bml::is_move_constructible_v<T>` and `bml::is_move_assignable_v<>` are `true`.
- Overload (2) does not participate in overload resolution unless `bml::is_swappable_v<T>` is
  `true`.

This is similar to `std::swap`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
