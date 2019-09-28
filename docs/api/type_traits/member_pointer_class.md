# `<bml/type_traits/member_pointer_class.hpp>`
#### Table of Contents
- [`member_pointer_class`](#member_pointer_class)

## `member_pointer_class`
```c++
template <typename T>
struct member_pointer_class;

template <bool B, typename T, typename F>
using member_pointer_class_ty = typename member_pointer_class<B, T, F>::type;
```
Obtains the class type that contains the member being pointed to if `T` is a pointer to a non-static
member function or non-static member object (i.e. `T` is a pointer to member).

This provides a member type alias `type` which names the class type that contains the member being
pointed to if `T` is a pointer to member. Otherwise, this does not define any member `type`.

#### Member type aliases
```c++
using type = /* ... */;
```
Names the class type which contains the member being pointed to if `T` is a pointer to member.
Otherwise, this alias is unavailable.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
