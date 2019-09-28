# `<bml/utilities/integer_sequence.hpp>`
#### Table of Contents
- [`integer_sequence`](#integer_sequence)

## `integer_sequence`
```c++
template <typename T, T... Is>
struct integer_sequence;
```
Represents a compile-time sequence of integers. `T` names an integer type to use for the elements of
the sequence, and `Is...` defines the sequence itself.

This is similar to `std::integer_sequence`.

#### Static member functions
```c++
[[nodiscard]] static constexpr auto size() noexcept -> ptrdiff_t;
```
Returns the number of integers in the sequence.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
