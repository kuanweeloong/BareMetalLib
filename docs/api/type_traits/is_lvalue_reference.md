# `<bml/type_traits/is_lvalue_reference.hpp>`
#### Table of Contents
- [`is_lvalue_reference`](#is_lvalue_reference)

## `is_lvalue_reference`
```c++
template <typename T>
struct is_lvalue_reference;

template <typename T>
constexpr auto is_lvalue_reference_v = bool(is_lvalue_reference<T>::value);
```
Checks if `T` is a lvalue reference type. This has a base characteristic of `bml::true_type` if `T`
is a lvalue reference type, and `bml::false_type` otherwise.

Both `is_lvalue_reference` and `is_lvalue_reference_v` are similar to `std::is_lvalue_reference` and
`std::is_lvalue_reference_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a lvalue reference type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
