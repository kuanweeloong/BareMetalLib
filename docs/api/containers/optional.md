# `<bml/containers/optional.hpp>`
#### Table of Contents
- [`nullopt`](#nullopt)
- [`optional`](#optional)

## `nullopt`
```c++
struct nullopt_ty;

constexpr auto nullopt = nullopt_ty(/* ... */);
```
A helper tag type to construct an empty `bml::optional`.

Both `nullopt` and `nullopt_ty` are similar to `std::nullopt` and `std::nullopt_t`, respectively,
except that the latter has been suffixed with `_ty` for POSIX compatibility.

## `optional`
```c++
template <typename T>
class optional;
```
A container for *optionally* storing a value of type `T` (i.e. the value may or may not be present).
An `optional` that does not hold a value is said to be *empty*.

The program is ill-formed if `T` names (possibly cv-qualified) `void`, an array type, a reference
type, `bml::in_place_ty` or `bml::nullopt_ty`.

This is similar to `std::optional`, except that it does not support any member function overloads
which take in `std::initializer_list` (since BML does not assume that the C++ standard library is
available). 

#### Member type aliases
```c++
using value_type = T;
```
Names the type of this `optional`'s value.

#### Constructors
```c++
constexpr optional() noexcept;
```
Constructs an empty `optional`.

```c++
constexpr optional(bml::nullopt_ty) noexcept;
```
Constructs an empty `optional`.

```c++
template <typename... Args>
constexpr explicit optional(bml::in_place_ty, Args&&... args) noexcept;
```
Constructs an `optional` which holds a value. The new `optional`'s value is initialized by
direct-initialization with `bml::forward<Args>(args)...`.

This does not participate in overload resolution unless `bml::is_constructible_v<T, Args...>` is
`true`.

#### Special member functions
```c++
constexpr optional(optional const& other) noexcept;
```
Copy constructs an `optional` from `other`. If `other` holds a value, this initializes the new
`optional`'s value from `other`'s value by direct-initialization with `*other`. Otherwise, the new
`optional` does not hold a value.

This is trivial if `bml::is_trivially_copy_constructible_v<T>` is `true`, and deleted if
`bml::is_copy_constructible_v<T>` is `false`.

```c++
constexpr optional(optional&& other) noexcept;
```
Move constructs an `optional` from `other`. If `other` holds a value, this initializes the new
`optional`'s value from `other`'s value by direct-initialization with `bml::move(*other)` (note that
this does *not* make `other` empty). Otherwise, the new `optional` does not hold a value.

This is trivial if `bml::is_trivially_move_constructible_v<T>` is `true`, and does not participate
in overload resolution (i.e. is not declared) if `bml::is_move_constructible_v<T>` is `false`.

```c++
constexpr auto operator=(optional const& other) noexcept -> optional&;
```
Copy assigns this `optional` from `other`. 

- If both this `optional` and `other` are empty, this function has no effect.
- If this `optional` holds a value, and `other` does not, the value held by this `optional` is
  destroyed and this `optional` is set to an empty state.
- If this `optional` does not hold a value, and `other` does, a new value is constructed in this
  `optional` and initialized from `other`'s value by direct-initialization with `*other`.
- If both this `optional` and `other` hold values, the value held by this `optional` is assigned
  from `other`'s value via `this->value() = *other`.

This is trivial if `bml::is_trivially_copy_assignable_v<T>` is `true`, and deleted if
`bml::is_copy_assignable_v<T>` is `false`.

```c++
constexpr auto operator=(optional&& other) noexcept -> optional&;
```
Move assigns this `optional` from `other`.

- If both this `optional` and `other` are empty, this function has no effect.
- If this `optional` holds a value, and `other` does not, the value held by this `optional` is
  destroyed and this `optional` is set to an empty state.
- If this `optional` does not hold a value, and `other` does, a new value is constructed in this
  `optional` and initialized from `other`'s value by direct-initialization with `bml::move(*other)`
  (note that this does *not* make `other` empty).
- If both this `optional` and `other` hold values, the value held by this `optional` is assigned
  from `other`'s value via `this->value() = bml::move(*other)` (note that this does *not* make
  `other` empty).

This is trivial if `bml::is_trivially_move_assignable_v<T>` is `true`, and does not participate in
overload resolution (i.e. is not declared) if `bml::is_move_assignable_v<T>` is `false`.

```c++
~optional();
```
Destroys this `optional`. If this `optional` holds a value, that value is also destroyed.

This is trivial if `bml::is_trivially_destructible_v<T>` is `true`, and deleted if 
`bml::is_destructible_v<T>` is `false`.

#### Member functions
```c++
auto reset() noexcept -> void;
```
Destroys the currently held value, if any, and resets this `optional` to an empty state.

```c++
auto operator=(bml::nullopt_ty) noexcept -> optional&;
```
Destroys the currently held value, if any, and resets this `optional` to an empty state.

```c++
[[nodiscard]] constexpr auto has_value() const noexcept -> bool;
```
Checks if this `optional` holds a value.

```c++
[[nodiscard]] constexpr explicit operator bool() const noexcept;
```
Checks if this `optional` holds a value.

```c++
[[nodiscard]] constexpr auto value() & noexcept -> T&;

[[nodiscard]] constexpr auto value() const & noexcept -> T const&;

[[nodiscard]] constexpr auto value() && noexcept -> T&&;

[[nodiscard]] constexpr auto value() const && noexcept -> T const&&;
```
Returns a reference to the currently held value.

Program behavior is undefined if this is invoked while the `optional` is empty.

```c++
[[nodiscard]] constexpr auto operator*() & noexcept -> T&;

[[nodiscard]] constexpr auto operator*() const & noexcept -> T const&;

[[nodiscard]] constexpr auto operator*() && noexcept -> T&&;

[[nodiscard]] constexpr auto operator*() const && noexcept -> T const&&;
```
Returns a reference to the currently held value.

Program behavior is undefined if this is invoked while the `optional` is empty.

```c++
[[nodiscard]] constexpr auto operator->() noexcept -> T*;

[[nodiscard]] constexpr auto operator->() const noexcept -> T const*;
```
Returns a pointer to the currently held value.

Program behavior is undefined if this is invoked while the `optional` is empty.

```c++
auto swap(optional& other) noexcept -> void;
```
Swaps this `optional`'s current state and value (if any) with `other`'s state and value (if any).

- If both this `optional` and `other` are empty, this function has no effect.
- If this `optional` holds a value, and `other` does not, a new value is constructed in `other` and
  initialized from this `optional`'s value by direct-initialization with `bml::move(this->value())`.
  Then, this `optional`'s value is destroyed and this `optional` is set to an empty state.
- If this `optional` does not hold a value, and `other` does, a new value is constructed in this
  `optional` and initialized from `other`'s value by direct-initialization with `bml::move(*other)`.
  Then, `other`'s value is destroyed and `other` is set to an empty state.
- If both this `optional` and `other` hold values, their contained values are swapped via:
  > ```c++
  > using bml::swap;
  > swap(this->value(), *other);
  > ```

This does not participate in overload resolution unless both `bml::is_move_constructible_v<T>`
and `bml::is_swappable_v<T>` are `true`.

```c++
template <typename... Args>
auto emplace(Args&&... args) noexcept -> T&;
```
Destroys the currently held value (if any) and constructs a new value in this `optional`. The new
value is initialized by direct-initialization with `bml::forward<Args>(args)...`.

This does not participate in overload resolution unless `bml::is_constructible_v<T, Args...>` is
`true`.

#### Associated free functions
```c++
template <typename T>
auto swap(optional<T>& lhs, optional<T>& rhs) noexcept -> void;
```
Swaps the states and values (if any) of `lhs` with `rhs`.

- If both `lhs` and `rhs` are empty, this function has no effect.
- If `lhs` holds a value and `rhs` does not, a new value is constructed in `rhs` and initialized
  from `lhs`'s value by direct-initialization with `bml::move(*lhs)`. Then, `lhs`'s value is
  destroyed and `lhs` is set to an empty state.
- If `rhs` holds a value and `lhs` does not, a new value is constructed in `lhs` and initialized
  from `rhs`'s value by direct-initialization with `bml::move(*rhs)`. Then, `rhs`'s value is
  destroyed and `rhs` is set to an empty state.
- If both `lhs` and `rhs` hold values, their contained values are swapped via:
  > ```c++
  > using bml::swap;
  > swap(*lhs, *rhs);
  > ```

This does not participate in overload resolution unless both `bml::is_move_constructible_v<T>`
and `bml::is_swappable_v<T>` are `true`.

This is similar to `std::swap` for `std::optional`s.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
