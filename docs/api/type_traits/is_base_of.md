# `<bml/type_traits/is_base_of.hpp>`
#### Table of Contents
- [`is_base_of`](#is_base_of)

## `is_base_of`
```c++
template <typename Base, typename Derived>
struct is_base_of;

template <typename Base, typename Derived>
constexpr auto is_base_of_v = bool(is_base_of<Base, Derived>::value);
```
Checks if `Derived` is derived from `Base`. This has a base characteristic of `bml::true_type` if
either `Derived` is derived from `Base`, or both are the same non-union class type (in both cases
ignoring any top-level cv-qualifiers). Otherwise, this has a base characteristic of
`bml::false_type`.

If `Base` and `Derived` are different non-union class types (ignoring top-level cv-qualifiers), and
`Derived` is an incomplete type, program behavior is undefined.

Both `is_base_of` and `is_base_of_v` are similar to `std::is_base_of` and `std::is_base_of_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if either `Derived` is derived from `Base`, or both are the same non-union class
  type (in both cases ignoring any top-level cv-qualifiers).
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
