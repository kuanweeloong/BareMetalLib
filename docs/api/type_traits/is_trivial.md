# `<bml/type_traits/is_trivial.hpp>`
#### Table of Contents
- [`is_trivial`](#is_trivial)

## `is_trivial`
```c++
template <typename T>
struct is_trivial;

template <typename T>
constexpr auto is_trivial_v = bool(is_trivial<T>::value);
```
Checks if `T` is a trivial type. This has a base characteristic of `bml::true_type` if `T` is a
trivial type, and `bml::false_type` otherwise.

The following types, and arrays of such types, are trivial types:

- Scalar types
- Trivially copyable class types with a trivial default constructor

If `bml::remove_all_extents_ty<T>` is an incomplete type other than (possibly cv-qualified) `void`,
program behaviour is undefined.

Both `is_trivial` and `is_trivial_v` are similar to `std::is_trivial` and `std::is_trivial_v`,
respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a trivial type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
