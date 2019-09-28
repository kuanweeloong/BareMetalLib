# `<bml/type_traits/add_pointer.hpp>`
#### Table of Contents
- [`add_pointer`](#add_pointer)

## `add_pointer`
```c++
template <typename T>
struct add_pointer;

template <typename T>
using add_pointer_ty = typename add_pointer<T>::type;
```
Creates a pointer to `T`. This provides a member type alias `type` which names:

- `T*` if `T` is *not* a reference type, and names a referenceable type or a (possibly cv-qualified)
  `void`.
- `U*` if `T` is a reference to `U`.
- `T` otherwise.

Both `add_pointer` and `add_pointer_ty` are similar to `std::add_pointer` and `std::add_pointer_t`,
respectively, except that the latter has been suffixed with `_ty` for POSIX compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names:

- `T*` if `T` is not a reference type, and names a referenceable type or a (possibly cv-qualified)
  `void`.
- `U*` if `T` is a reference to `U`.
- `T` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
