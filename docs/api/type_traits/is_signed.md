# `<bml/type_traits/is_signed.hpp>`
#### Table of Contents
- [`is_signed`](#is_signed)

## `is_signed`
```c++
template <typename T>
struct is_signed;

template <typename T>
constexpr auto is_signed_v = bool(is_signed<T>::value);
```
Checks if `T` is a signed type. This has a base characteristic of `bml::true_type` if `T` is an
arithmetic type and the expression below is true:

> `T(-1) < T(0)`

Otherwise, this has a base characteristic of `bml::false_type`.

Both `is_signed` and `is_signed_v` are similar to `std::is_signed` and `std::is_signed_v`,
respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a signed type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
