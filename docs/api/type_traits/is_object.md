# `<bml/type_traits/is_object.hpp>`
#### Table of Contents
- [`is_object`](#is_object)

## `is_object`
```c++
template <typename T>
struct is_object;

template <typename T>
constexpr auto is_object_v = bool(is_object<T>::value);
```
Checks if `T` is an object type. This has a base characteristic of `bml::true_type` if `T` is an
object type, and `bml::false_type` otherwise.

An object type is any type other than the following:

- Function types
- Reference types
- (Possibly cv-qualified) `void`

Both `is_object` and `is_object_v` are similar to `std::is_object` and `std::is_object_v`,
respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is an object type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
