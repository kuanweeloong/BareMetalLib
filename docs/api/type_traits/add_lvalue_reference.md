# `<bml/type_traits/add_lvalue_reference.hpp>`
#### Table of Contents
- [`add_lvalue_reference`](#add_lvalue_reference)

## `add_lvalue_reference`
```c++
template <typename T>
struct add_lvalue_reference;

template <typename T>
using add_lvalue_reference_ty = typename add_lvalue_reference<T>::type;
```
Creates a lvalue reference to `T`. This provides a member type alias `type` which names `T&` if `T`
names a referenceable type, and `T` otherwise.

Both `add_lvalue_reference` and `add_lvalue_reference_ty` are similar to `std::add_lvalue_reference`
and `std::add_lvalue_reference_t`, respectively, except that the latter has been suffixed with `_ty`
for POSIX compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names `T&` if `T` names a referenceable type, and `T` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
