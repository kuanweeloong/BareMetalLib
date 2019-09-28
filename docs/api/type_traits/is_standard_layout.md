# `<bml/type_traits/is_standard_layout.hpp>`
#### Table of Contents
- [`is_standard_layout`](#is_standard_layout)

## `is_standard_layout`
```c++
template <typename T>
struct is_standard_layout;

template <typename T>
constexpr auto is_standard_layout_v = bool(is_standard_layout<T>::value);
```
Checks if `T` is a standard layout type. This has a base characteristic of `bml::true_type` if `T`
is a standard layout type, and `bml::false_type` otherwise.

The following types, and arrays of such types, are standard layout types:

- Scalar types
- Standard layout class types

If `bml::remove_all_extents_ty<T>` is an incomplete type other than (possibly cv-qualified) `void`,
program behaviour is undefined.

Both `is_standard_layout` and `is_standard_layout_v` are similar to `std::is_standard_layout` and
`std::is_standard_layout_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a standard layout type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
