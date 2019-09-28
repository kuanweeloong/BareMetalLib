# `<bml/utilities/launder.hpp>`
#### Table of Contents
- [`launder`](#launder)

## `launder`
```c++
template <typename T>
[[nodiscard]] constexpr auto launder(T* p) noexcept -> T*
```
Obtains a pointer to the object located at the address represented by `p`.

Given that:

- `p` represents the address `A` of a byte in memory.
- An object `X` is located at the address `A`.

This returns a value of type `T*` that points to the object `X` if all the conditions below are met:

- `X` is within its lifetime.
- The type of `X` is the same as `T`, ignoring cv-qualifiers at every level.
- Every byte that would be reachable through the result is reachable through `p` (bytes are
  reachable through a pointer that points to an object `Y` if those bytes are within the storage of
  an object `Z` that is *pointer-interconvertible* with `Y`, or within the immediately enclosing
  array of which `Z` is an element).

If this is invoked when any of the conditions above are not met, program behaviour is undefined. If
`T` names a function type or (possibly cv-qualified) `void`, the program is ill-formed.

This is similar to `std::launder`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
