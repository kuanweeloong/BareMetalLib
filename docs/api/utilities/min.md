# `<bml/utilities/min.hpp>`
#### Table of Contents
- [`min`](#min)

## `min`
```c++
// Overload (1)
template <typename T>
[[nodiscard]] constexpr auto min(T const& a) noexcept -> T const&;

// Overload (2)
template <typename T, typename... Ts>
[[nodiscard]] constexpr auto min(T const& a1, T const& a2, Ts const&... an) noexcept -> T const&
```
Returns a const reference to the minimum of of all its arguments.

- Overload (1) returns a const reference to `a`, which is vacuously the minimum argument.
- Overload (2) returns a const reference to the minimum of `a1, a2, ..., an`. If several arguments
  are equivalent to the minimum, this returns the leftmost of these arguments.

Overload (2) does not participate in overload resolution unless all types in `Ts...` name the same
type as `T`. If overload (2) is invoked, and `T` cannot be compared via the less-than operator, the
program is ill-formed.

This is similar to `std::min`, except that it does not require `std::initializer_list` to compare
more than 2 arguments, and does not support a comparison function object.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
