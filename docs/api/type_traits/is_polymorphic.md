# `<bml/type_traits/is_polymorphic.hpp>`
#### Table of Contents
- [`is_polymorphic`](#is_polymorphic)

## `is_polymorphic`
```c++
template <typename T>
struct is_polymorphic;

template <typename T>
constexpr auto is_polymorphic_v = bool(is_polymorphic<T>::value);
```
Checks if `T` is a polymorphic class type (i.e. a non-union class that declares or inherits at least
one virtual function). This has a base characteristic of `bml::true_type` if `T` is a polymorphic
class type, and `bml::false_type` otherwise.

If `T` is an incomplete non-union class type, program behaviour is undefined.

Both `is_polymorphic` and `is_polymorphic_v` are similar to `std::is_polymorphic` and
`std::is_polymorphic_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a polymorphic class type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
