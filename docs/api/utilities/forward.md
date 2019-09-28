# `<bml/utilities/forward.hpp>`
#### Table of Contents
- [`forward`](#forward)

## `forward`
```c++
// Overload (1)
template <typename T>
[[nodiscard]] constexpr auto forward(bml::remove_reference_ty<T>& t) noexcept -> T&&;

// Overload (2)
template <typename T>
[[nodiscard]] constexpr auto forward(bml::remove_reference_ty<T>&& t) noexcept -> T&&;
```
Passes forwarding references to another function while preserving their original value category.
Note that `T` is in a non-deduced context, so it must be explicitly specified.

If overload (2) is instantiated when `T` names an lvalue reference type, the program is ill-formed.

This is similar to `std::forward`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
