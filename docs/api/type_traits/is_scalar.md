# `<bml/type_traits/is_scalar.hpp>`
#### Table of Contents
- [`is_scalar`](#is_scalar)

## `is_scalar`
```c++
template <typename T>
struct is_scalar;

template <typename T>
constexpr auto is_scalar_v = bool(is_scalar<T>::value);
```
Checks if `T` is a scalar type. This has a base characteristic of `bml::true_type` if `T` is a
scalar type, and `bml::false_type` otherwise.

The following types are scalar types:

- (Possibly cv-qualified) arithmetic types
- Pointers
- Pointers to member
- Enumeration types
- (Possibly cv-qualified) `bml::nullptr_ty`

Both `is_scalar` and `is_scalar_v` are similar to `std::is_scalar` and `std::is_scalar_v`,
respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a scalar type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
