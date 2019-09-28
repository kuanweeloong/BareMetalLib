# `<bml/utilities/addressof.hpp>`
#### Table of Contents
- [`addressof`](#addressof)

## `addressof`
```c++
// Overload (1)
template <typename T>
[[nodiscard]] constexpr auto addressof(T& arg) noexcept -> T*;

// Overload (2)
template <typename T>
auto addressof(T const&&) noexcept -> T const* = delete;
```
Returns the actual address of `arg` even if `T` has an overloaded `operator&`.

If overload (2) is invoked, the program is ill-formed.

This is similar to `std::addressof`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
