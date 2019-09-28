# `<bml/type_traits/is_null_pointer.hpp>`
#### Table of Contents
- [`is_null_pointer`](#is_null_pointer)

## `is_null_pointer`
```c++
template <typename T>
struct is_null_pointer;

template <typename T>
constexpr auto is_null_pointer_v = bool(is_null_pointer<T>::value);
```
Checks if `T` names `bml::nullptr_ty` or its cv-qualified variants. This has a base characteristic
of `bml::true_type` if `T` names `bml::nullptr_ty` or its cv-qualified variants, and
`bml::false_type` otherwise.

Both `is_null_pointer` and `is_null_pointer_v` are similar to `std::is_null_pointer` and `std::is_null_pointer_v`, respectively, except that both check for `bml::nullptr_ty` instead of
`std::nullptr_t`.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` names `bml::nullptr_ty` or its cv-qualified variants.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
