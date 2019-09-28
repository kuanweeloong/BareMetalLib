# `<bml/type_traits/decay.hpp>`
#### Table of Contents
- [`decay`](#decay)

## `decay`
```c++
template <typename T>
struct decay;

template <typename T>
using decay_ty = typename decay<T>::type;
```
Transforms `T` in a manner that models the type conversions applied to function arguments which are
passed by value. This provides a member type alias `type` which names:

- `U*` if `T` is an array of `U`, or reference to an array of `U`.
- `bml::add_pointer_ty<F>` if `T` is a function type `F`, or a reference to `F`.
- `bml::remove_cvref_ty<T>` otherwise.

Essentially, this applies lvalue-to-rvalue, array-to-pointer, and function-to-pointer implicit
conversions to `T`, and also removes top-level cv-qualifiers from `T` if `T` is not a function or
array type, or a reference to such types.

Both `decay` and `decay_ty` are similar to `std::decay` and `std::decay_t`, respectively, except
that the latter has been suffixed with `_ty` for POSIX compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names the result of applying the transformations detailed above to `T`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
