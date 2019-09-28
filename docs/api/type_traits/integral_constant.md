# `<bml/type_traits/integral_constant.hpp>`
#### Table of Contents
- [`integral_constant`](#integral_constant)

## `integral_constant`
```c++
template <typename T, T Value>
struct integral_constant;
```
A wrapper around a constant of type `T` and value `Value`. This allows constants to be converted to
types.

This is similar to `std::integral_constant`.

#### Member type aliases
```c++
using value_type = T;
```
Names the constant's type.

```c++
using type = integral_constant;
```
Names this `integral_constant` (i.e `integral_constant<T, Value>`).

#### Static member constants
```c++
static constexpr auto value = T(Value);
```
Equal to the constant's value.

#### Member functions
```c++
constexpr operator value_type() const noexcept;
```
Returns the stored value.

```c++
constexpr auto operator()() const noexcept -> value_type;
```
Returns the stored value.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
