# `<bml/type_traits/is_function.hpp>`
#### Table of Contents
- [`is_function`](#is_function)

## `is_function`
```c++
template <typename T>
struct is_function;

template <typename T>
constexpr auto is_function_v = bool(is_function<T>::value);
```
Checks if `T` is a function type. This has a base characteristic of `bml::true_type` if `T` is a
function class type, and `bml::false_type` otherwise.

Note that types such as lambdas, classes with overloaded `operator()` and pointers to functions are
not function types.

Both `is_function` and `is_function_v` are similar to `std::is_function` and `std::is_function_v`,
respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a function type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
