# `<bml/utilities/reference_wrapper.hpp>`
#### Table of Contents
- [`reference_wrapper`](#reference_wrapper)

## `reference_wrapper`
```c++
template <typename T>
class reference_wrapper;
```
A class for wrapping a reference to `T` in a copy-constructible and copy-assignable object.

This is similar to `std::reference_wrapper`.

#### Deduction Guides
```c++
template <typename T>
reference_wrapper(T&) -> reference_wrapper<T>;
```

#### Member type aliases
```c++
using type = T;
```
Names the type being referred to in the stored reference.

#### Constructors
```c++
template <typename U>
constexpr reference_wrapper(U&& u) noexcept;
```
Constructs a `reference_wrapper` that stores a reference to the object referred to by `u`.

This does not participate in overload resolution if any of the conditions below are met:

- `u`'s original value category is rvalue.
- `u` is not implicitly convertible to `T&` as if by `T& r = bml::forward<U>(u)`.

#### Special member functions
```c++
constexpr reference_wrapper(reference_wrapper const& other) noexcept;
```
Copy constructs a `reference_wrapper` from `other`. The new wrapper stores a reference to the object
referred to by `other.get()`. This is always trivial.

```c++
constexpr auto operator=(reference_wrapper const& other) noexcept -> reference_wrapper&;
```
Copy assigns this `reference_wrapper` from `other`. This drops the current reference and stores a
reference to the object referred to by `other.get()`. This is always trivial.

#### Member functions
```c++
constexpr auto get() const noexcept -> T&;
```
Returns the stored reference.

```c++
constexpr operator T&() const noexcept;
```
Returns the stored reference.

```c++
template <typename... Args>
constexpr auto operator()(Args&&... args) const noexcept -> bml::invoke_result_ty<T&, Args...>;
```
Invokes the stored reference via `bml::invoke(get(), bml::forward<Args>(args)...)`.

This does not participate in overload resolution unless `bml::is_invocable_v<T&, Args...>` is
`true`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
