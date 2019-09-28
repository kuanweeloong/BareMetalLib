# `<bml/type_traits/is_class.hpp>`
#### Table of Contents
- [`is_class`](#is_class)

## `is_class`
```c++
template <typename T>
struct is_class;

template <typename T>
constexpr auto is_class_v = bool(is_class<T>::value);
```
Checks if `T` is a non-union class type. This has a base characteristic of `bml::true_type` if `T`
is a non-union class type, and `bml::false_type` otherwise.

Both `is_class` and `is_class_v` are similar to `std::is_class` and `std::is_class_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a non-union class type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
