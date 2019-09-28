# `<bml/type_traits/has_unique_object_representations.hpp>`
#### Table of Contents
- [`has_unique_object_representations`](#has_unique_object_representations)

## `has_unique_object_representations`
```c++
template <typename T>
struct has_unique_object_representations;

template <typename T>
constexpr auto has_unique_object_representations_v =
    bool(has_unique_object_representations<T>::value);
```
Checks if `T` has unique object representations. This has a base characteristic of `bml::true_type`
if `T` is trivially copyable, and any two objects of type `T` with the same value have the same
object representation. Otherwise, this has a base characteristic of `bml::false_type`.

If `T` is an unsigned integer type that does not use padding bits, this is guaranteed to yield
`true`. Otherwise, the result depends on the platform.

Note that this defines the notion of "having the same value" for several classes of types as
follows:

- Arrays have the same value if their elements have the same values.
- Non-union classes have the same value if their direct sub-objects have the same value.
- Unions have the same value if they have the same active member, and those members have the same
  value.

If `T` is an incomplete type other than (possibly cv-qualified) `void` or an array of unknown bound,
program behaviour is undefined.

Both `has_unique_object_representations` and `has_unique_object_representations_v` are similar to
`std::has_unique_object_representations` and `std::has_unique_object_representations_v`,
respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is trivially copyable and has unique object representations.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
