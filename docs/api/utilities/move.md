# `<bml/utilities/move.hpp>`
#### Table of Contents
- [`move`](#move)

## `move`
```c++
template <typename T>
[[nodiscard]] constexpr auto move(T&& t) noexcept -> bml::remove_reference_ty<T>&&;
```
Returns an rvalue reference to the object referred to by `t`. Effectively, this produces an xvalue
expression that identifies `t`.

This is similar to `std::move`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
