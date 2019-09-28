# `<bml/type_traits/is_compound.hpp>`
#### Table of Contents
- [`is_compound`](#is_compound)

## `is_compound`
```c++
template <typename T>
struct is_compound;

template <typename T>
constexpr auto is_compound_v = bool(is_compound<T>::value);
```
Checks if `T` is a compound type. This has a base characteristic of `bml::true_type` if `T` is a
compound type, and `bml::false_type` otherwise.

The following types are compound types:

- Array types
- Function types
- Class types
- Union types
- Enumeration types
- Pointers
- Pointers to member
- References

Both `is_compound` and `is_compound_v` are similar to `std::is_compound` and `std::is_compound_v`,
respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a compound type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
