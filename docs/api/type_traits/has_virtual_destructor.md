# `<bml/type_traits/has_virtual_destructor.hpp>`
#### Table of Contents
- [`has_virtual_destructor`](#has_virtual_destructor)

## `has_virtual_destructor`
```c++
template <typename T>
struct has_virtual_destructor;

template <typename T>
constexpr auto has_virtual_destructor_v = bool(has_virtual_destructor<T>::value);
```
Checks if `T` has a virtual destructor. This has a base characteristic of `bml::true_type` if `T`
has a virtual destructor, and `bml::false_type` otherwise.

If `T` an incomplete non-union class type, program behaviour is undefined.

Both `has_virtual_destructor` and `has_virtual_destructor_v` are similar to
`std::has_virtual_destructor` and `std::has_virtual_destructor_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` has a virtual destructor.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
