# `<bml/utilities/declval.hpp>`
#### Table of Contents
- [`declval`](#declval)

## `declval`
```c++
template <typename T>
auto declval() noexcept -> bml::add_rvalue_reference_ty<T>;
```
Returns a reference for use in an unevaluated context.

- If `T` is not a reference type, this returns `T&&`.
- If `T` is a lvalue reference to `U`, this returns `U&`.
- If `T` is a rvalue reference to `U`, this returns `U&&`.

If this is odr-used, the program is ill-formed.

This is similar to `std::declval`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
