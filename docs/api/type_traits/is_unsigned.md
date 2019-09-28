# `<bml/type_traits/is_unsigned.hpp>`
#### Table of Contents
- [`is_unsigned`](#is_unsigned)

## `is_unsigned`
```c++
template <typename T>
struct is_unsigned;

template <typename T>
constexpr auto is_unsigned_v = bool(is_unsigned<T>::value);
```
Checks if `T` is an unsigned type. This has a base characteristic of `bml::true_type` if `T` is an
arithmetic type and the expression below is true:

> `T(0) < T(-1)`

Otherwise, this has a base characteristic of `bml::false_type`.

Both `is_unsigned` and `is_unsigned_v` are similar to `std::is_unsigned` and `std::is_unsigned_v`,
respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is an unsigned type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
