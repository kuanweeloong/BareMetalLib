# `<bml/type_traits/is_arithmetic.hpp>`
#### Table of Contents
- [`is_arithmetic`](#is_arithmetic)

## `is_arithmetic`
```c++
template <typename T>
struct is_arithmetic;

template <typename T>
constexpr auto is_arithmetic_v = bool(is_arithmetic<T>::value);
```
Checks if `T` is an arithmetic type (i.e integral or floating-point type). This has a base
characteristic of `bml::true_type` if `T` is an arithmetic type, and `bml::false_type` otherwise.

Both `is_arithmetic` and `is_arithmetic_v` are similar to `std::is_arithmetic` and
`std::is_arithmetic_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is an arithmetic type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
