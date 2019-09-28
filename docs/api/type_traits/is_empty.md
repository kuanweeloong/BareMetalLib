# `<bml/type_traits/is_empty.hpp>`
#### Table of Contents
- [`is_empty`](#is_empty)

## `is_empty`
```c++
template <typename T>
struct is_empty;

template <typename T>
constexpr auto is_empty_v = bool(is_empty<T>::value);
```
Checks if `T` is an empty type. This has a base characteristic of `bml::true_type` if `T` is an
empty type, and `bml::false_type` otherwise.

An empty type is a non-union class type with:

- No non-static data members other than bit-fields of size 0
- No virtual functions
- No virtual base classes
- No non-empty base classes

If `T` is an incomplete non-union class type, program behaviour is undefined.

Both `is_empty` and `is_empty_v` are similar to `std::is_empty` and `std::is_empty_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is an empty type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
