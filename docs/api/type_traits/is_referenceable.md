# `<bml/type_traits/is_referenceable.hpp>`
#### Table of Contents
- [`is_referenceable`](#is_referenceable)

## `is_referenceable`
```c++
template <typename T>
struct is_referenceable;

template <typename T>
constexpr auto is_referenceable_v = bool(is_referenceable<T>::value);
```
Checks if `T` is a referenceable type (i.e a type to which a reference can be created). This has a
base characteristic of `bml::true_type` if `T` is a reference type, and `bml::false_type` otherwise.

The following types are referenceable types:

- Object types
- Function types that do not have cv-qualifiers or a ref-qualifier
- Reference types

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a referenceable type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
