# `<bml/type_traits/is_integral.hpp>`
#### Table of Contents
- [`is_integral`](#is_integral)

## `is_integral`
```c++
template <typename T>
struct is_integral;

template <typename T>
constexpr auto is_integral_v = bool(is_integral<T>::value);
```
Checks if `T` is an integral type. This has a base characteristic of `bml::true_type` if `T` is an
integral type, and `bml::false_type` otherwise.

The following types, and their cv-qualified variants, are integral types:

- `bool`
- `char` / `signed char` / `unsigned char` / `wchar_t` / `char16_t` / `char32_t`
- `short` / `unsigned short`
- `int` / `unsigned int`
- `long` / `unsigned long`
- `long long` / `unsigned long long`
- Platform-defined extended integer types.

Both `is_integral` and `is_integral_v` are similar to `std::is_integral` and `std::is_integral_v`,
respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is an integral type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
