# `<bml/type_traits/is_abstract.hpp>`
#### Table of Contents
- [`is_abstract`](#is_abstract)

## `is_abstract`
```c++
template <typename T>
struct is_abstract;

template <typename T>
constexpr auto is_abstract_v = bool(is_abstract<T>::value);
```
Checks if `T` is an abstract class (i.e. a non-union class that declares or inherits at least one
pure virtual function). This has a base characteristic of `bml::true_type` if `T` is an abstract
class, and `bml::false_type` otherwise.

If `T` an incomplete non-union class type, program behaviour is undefined.

Both `is_abstract` and `is_abstract_v` are similar to `std::is_abstract` and `std::is_abstract_v`,
respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is an abstract class.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
