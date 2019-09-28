# `<bml/type_traits/is_void.hpp>`
#### Table of Contents
- [`is_void`](#is_void)

## `is_void`
```c++
template <typename T>
struct is_void;

template <typename T>
constexpr auto is_void_v = bool(is_void<T>::value);
```
Checks if `T` is a void type. This has a base characteristic of `bml::true_type` if `T` names `void`
or any of its cv-qualified variants, and `bml::false_type` otherwise.

Both `is_void` and `is_void_v` are similar to `std::is_void` and `std::is_void_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a void type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
