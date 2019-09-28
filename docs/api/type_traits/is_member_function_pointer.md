# `<bml/type_traits/is_member_function_pointer.hpp>`
#### Table of Contents
- [`is_member_function_pointer`](#is_member_function_pointer)

## `is_member_function_pointer`
```c++
template <typename T>
struct is_member_function_pointer;

template <typename T>
constexpr auto is_member_function_pointer_v = bool(is_member_function_pointer<T>::value);
```
Checks if `T` is a pointer to a non-static member function. This has a base characteristic of
`bml::true_type` if `T` is a pointer to a non-static member function, and `bml::false_type`
otherwise.

Both `is_member_function_pointer` and `is_member_function_pointer_v` are similar to
`std::is_member_function_pointer` and `std::is_member_function_pointer_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a pointer to a non-static member function.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
