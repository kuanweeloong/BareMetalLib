# `<bml/type_traits/is_reference_wrapper.hpp>`
#### Table of Contents
- [`is_reference_wrapper`](#is_reference_wrapper)

## `is_reference_wrapper`
```c++
template <typename T>
struct is_reference_wrapper;

template <typename T>
constexpr auto is_reference_wrapper_v = bool(is_reference_wrapper<T>::value);
```
Checks if `T` names `bml::reference_wrapper` or its cv-qualified variants. This has a base
characteristic of `bml::true_type` if `T` names `bml::reference_wrapper` or its cv-qualified
variants, and `bml::false_type` otherwise.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` names `bml::reference_wrapper` or its cv-qualified variants.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
