# `<bml/containers/variant.hpp>`
#### Table of Contents
- [`variant_size`](#variant_size)
- [`variant_alternative`](#variant_alternative)
- [`variant`](#variant)

## `variant_size`
```c++
template <typename T>
struct variant_size;

template <typename T>
constexpr auto variant_size_v = ptrdiff_t(variant_size<T>::value);
```
Gets the number of alternatives in a `bml::variant`. 

- If `bml::remove_cv_ty<T>` names `bml::variant`, then this has a base characteristic of
  `bml::integral_constant<ptrdiff_t, N>`, where `N` is the number of alternatives in that
  `variant`.
- Otherwise, this does not have a definition.

If the number of alternatives in the `variant` named by `T` is larger than `PTRDIFF_MAX`, the
program is ill-formed.

Both `variant_size` and `variant_size_v` are similar to `std::variant_size` and
`std::variant_size_v`, respectively, except that they expose the number of alternatives as
`ptrdiff_t` instead of `size_t`.

#### Public base classes
```c++
bml::integral_constant<ptrdiff_t, N>
```
`N` is the number of alternatives in the `variant` named by `T`.

## `variant_alternative`
```c++
template <ptrdiff_t I, typename T>
struct variant_alternative;

template <ptrdiff_t I, typename T>
using variant_alternative_ty = typename variant_alternative<I, T>::type;
```
Gets the `I`-th alternative in a `bml::variant`.

- If `bml::remove_cv_ty<T>` names `bml::variant`, then this provides a member type alias `type`
  which names the `I`-th alternative in that `variant` after combining its top-level cv-qualifiers
  with those of `T` (e.g. `variant_alternative_ty<0, bml::variant<int volatile> const>` names
  `int const volatile`).
- Otherwise, this does not have a definition.

If `I` is not in the range `[0, N)`, where `N` is the total number of alternatives in the `variant`
named by `T`, the program is ill-formed.

Both `variant_alternative` and `variant_alternative_ty` are similar to `std::variant_alternative`
and `std::variant_alternative_t`, respectively, except that they use `ptrdiff_t` for the index
instead of `size_t`, and that the latter has been suffixed with `_ty` for POSIX compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names the `I`-th alternative in the `variant` named by `T`, after combining its top-level
cv-qualifiers with `T`'s top-level cv-qualifiers.

## `variant`
```c++
template <typename... Ts>
class variant;
```
A tagged union whose value may be of any type in `Ts...`.

Each type in `Ts...` is called an *alternative*; if a `variant` currently contains a value of the
`i`-th alternative (i.e. the `i`-th type in `Ts...`), that `variant` is said to *hold the `i`-th
alternative*.

This is similar to `std::variant`, except that:

- It does not support any member function overloads which take in `std::initializer_list` (since BML
  does not assume that the C++ standard library is available).
- It does not have a `valueless_by_exception` state, since BML is `noexcept`.

#### Constructors
```c++
template <ptrdiff_t I, typename... Args>
constexpr explicit variant(bml::in_place_index_ty<I>, Args&&... args) noexcept;
```
Constructs a `variant` which holds the `I`-th alternative. The new `variant`'s value is initialized
via direct-initialization with `bml::forward<Args>(args)...`.

This does not participate in overload resolution unless `bml::is_constructible_v<T_I, Args...>` is
`true`, where `T_I` refers to the `I`-th alternative.

#### Special member functions
```c++
constexpr variant(variant const& other) noexcept;
```
Copy constructs a `variant` from `other`. The new `variant` holds the same alternative as `other`,
and its value is initialized from `other`'s value by direct-initialization with `other.get<I>()`,
where `I` is the index of `other`'s alternative.

This is trivial if all elements of `bml::is_trivially_copy_constructible_v<Ts>...` is `true`, and
deleted if at least one element of `bml::is_copy_constructible_v<Ts>...` is `false`.

```c++
constexpr variant(variant&& other) noexcept;
```
Move constructs a `variant` from `other`. The new `variant` holds the same alternative as `other`,
and its value is initialized from `other`'s value by direct-initialization with
`bml::move(other.get<I>())`, where `I` is the index of `other`'s alternative.

This is trivial if all elements of `bml::is_trivially_move_constructible_v<Ts>...` is `true`, and
does not participate in overload resolution (i.e. is not declared) if at least one element of
`bml::is_move_constructible_v<Ts>...` is `false`.

```c++
constexpr auto operator=(variant const& other) noexcept -> variant&;
```
Copy assigns this `variant` from `other`.

Let `I` be equal to the index of `other`'s alternative. Then:

- If this `variant` holds the same alternative as `other`, its current value is assigned from
  `other`'s value via `this->get<I>() = other.get<I>()`.
- Otherwise, this `variant` is made to hold `other`'s alternative via
  `this->emplace<I>(other.get<I>())`.

This is trivial if all the conditions below are met:

- All elements of `bml::is_trivially_copy_assignable_v<Ts>...` are `true`.
- All elements of `bml::is_trivially_copy_constructible_v<Ts>...` are `true`.
- All elements of `bml::is_trivially_destructible_v<Ts>...` are `true`.

This is deleted if at least one condition below is met:

- At least one element of `bml::is_copy_assignable_v<Ts>...` is `false`.
- At least one element of `bml::is_copy_constructible_v<Ts>...` is `false`.

```c++
constexpr auto operator=(variant&& other) noexcept -> variant&;
```
Move assigns this `variant` from `other`.

Let `I` be equal to the index of `other`'s alternative. Then:

- If this `variant` holds the same alternative as `other`, its current value is assigned from
  `other`'s value via `this->get<I>() = bml::move(other.get<I>())`.
- Otherwise, this `variant` is made to hold `other`'s alternative via
  `this->emplace<I>(bml::move(other.get<I>()))`.

This is trivial if all the conditions below are met:

- All elements of `bml::is_trivially_move_assignable_v<Ts>...` are `true`.
- All elements of `bml::is_trivially_move_constructible_v<Ts>...` are `true`.
- All elements of `bml::is_trivially_destructible_v<Ts>...` are `true`.

This does not participate in overload resolution (i.e. is not declared) if at least one condition
below is met:

- At least one element of `bml::is_move_assignable_v<Ts>...` is `false`.
- At least one element of `bml::is_move_constructible_v<Ts>...` is `false`.

```c++
~variant();
```
Destroys this `variant` and its value.

This is trivial if all elements of `bml::is_trivially_destructible_v<Ts>...` are `true`, and deleted
if at least one element of `bml::is_destructible_v<Ts>...` is `false`.

#### Member functions
```c++
template <ptrdiff_t I, typename... Args>
auto emplace(Args&&... args) noexcept -> bml::variant_alternative_ty<I, variant>&;
```
Destroys the currently held value and constructs a value of the `I`-th alternative in this
`variant`, thereby making it hold the `I`-th alternative. The new value is initialized by
direct-initialization with `bml::forward<Args>(args)...`.

This does not participate in overload resolution unless `bml::is_constructible_v<T_I, Args...>` is
`true`, where `T_I` refers the `I`-th alternative.

```c++
[[nodiscard]] constexpr auto index() const noexcept -> ptrdiff_t;
```
Gets the index of the current alternative.

```c++
auto swap(variant& other) noexcept -> void;
```
Swaps this `variant`'s value with `other`'s value (note that `other` may hold a different
alternative).

Let `I` be equal to the index of this `variant`'s alternative, and `J` be equal to the index of
`other`'s alternative.

- If both this `variant` and `other` hold the same alternative, their values are swapped via:
  > ```c++
  > using bml::swap;
  > swap(this->get<I>(), other.get<I>());
  > ```
- Otherwise, this `variant` and `other` are made to hold each other's alternatives by exchanging
  their values via:
  > ```c++
  > auto temp = variant(bml::move(other));
  > other.emplace<I>(bml::move(this->get<I>()));
  > this->emplace<J>(bml::move(temp.get<J>()));
  > ```

This does not participate in overload resolution unless both conditions below are met:

- All elements of `bml::is_move_constructible_v<Ts>...` are `true`.
- All elements of `bml::is_swappable_v<Ts>...` are `true`.

``` c++
template <ptrdiff_t I>
[[nodiscard]] constexpr auto get() & noexcept
    -> bml::variant_alternative_ty<I, variant>&;

template <ptrdiff_t I>
[[nodiscard]] constexpr auto get() const & noexcept
    -> bml::variant_alternative_ty<I, variant> const&;

template <ptrdiff_t I>
[[nodiscard]] constexpr auto get() && noexcept
    -> bml::variant_alternative_ty<I, variant>&&;

template <ptrdiff_t I>
[[nodiscard]] constexpr auto get() const && noexcept
    -> bml::variant_alternative_ty<I, variant> const&&;
```
Returns a reference to the stored value, as if the value was of the `I`-th alternative.

The program is ill-formed if `I` is negative or `sizeof...(Ts) >= I`. Program behavior is undefined
if this is invoked while the `variant` does not hold the `I`-th alternative.

#### Associated free functions
```c++
template <ptrdiff_t I, typename... Ts>
[[nodiscard]] constexpr auto get(variant<Ts...>& v) noexcept
    -> bml::variant_alternative_ty<I, variant<Ts...>>&;

template <ptrdiff_t I, typename... Ts>
[[nodiscard]] constexpr auto get(variant<Ts...> const& v) noexcept
    -> bml::variant_alternative_ty<I, variant<Ts...>> const&;

template <ptrdiff_t I, typename... Ts>
[[nodiscard]] constexpr auto get(variant<Ts...>&& v) noexcept
    -> bml::variant_alternative_ty<I, variant<Ts...>>&&;

template <ptrdiff_t I, typename... Ts>
[[nodiscard]] constexpr auto get(variant<Ts...> const&& v) noexcept
    -> bml::variant_alternative_ty<I, variant<Ts...>> const&&;
```
Returns a reference to `v`'s value, as if its value was of the `I`-th alternative in `v`.

The program is ill-formed if `I` is negative or `sizeof...(Ts) >= I`. Program behavior is undefined
if this is invoked while `v` does not hold the `I`-th alternative.

This is similar to the index-based `std::get` for `variant`s, except that it uses `ptrdiff_t` for
the index instead of `size_t`, and exhibits undefined behaviour instead of throwing if
`v.index() != I`.

```c++
template <typename Visitor, typename... Variants>
constexpr auto visit(Visitor&& vis, Variants&&... vars) noexcept -> /* ... */;
```
Applies the visitor `vis` to the `variant`s `vars...` and returns the result.

Let `Is...` be an integer pack whose `i`-th element is equal to the index of the alternative
currently held by the `i`-th `variant` in `vars...`. Then this invokes `vis` with `vars...`'s
values via:

> `bml::invoke(bml::forward<Visitor>(vis), bml::forward<Variants>(vars).get<Is>()...)`

The return type of this is deduced from the expression above using `decltype`.

This does not participate in overload resolution unless all types in `Variants...` name `variant`.
If the expression above is not valid for all combination of alternatives across all `variant`s in
`Variants...`, the program is ill-formed.

This is similar to `std::visit`, except that it requires all types in `Variants...` to name
`variant`.

```c++
template <typename... Ts>
auto swap(variant<Ts...>& lhs, variant<Ts...> & rhs) noexcept -> void;
```
Swaps `lhs`'s value with `rhs`'s value (note that both may hold different alternatives).

Let `L` be equal to the index of `lhs`'s alternative, and `R` be equal to the index of `rhs`'s
alternative. Then:

- If both this `lhs` and `rhs` hold the same alternative, their contained values are swapped via:
  > ```c++
  > using bml::swap;
  > swap(lhs.get<L>(), rhs.get<L>());
  > ```
- Otherwise, `lhs` and `rhs` are made to hold each other's alternatives by exchanging their values
  via:
  > ```c++
  > auto temp = variant(bml::move(lhs));
  > lhs.emplace<R>(bml::move(rhs.get<R>()));
  > rhs.emplace<L>(bml::move(temp.get<L>()));
  > ```

This does not participate in overload resolution unless both conditions below are met:

- All elements of `bml::is_move_constructible_v<Ts>...` are `true`.
- All elements of `bml::is_swappable_v<Ts>...` are `true`.

This is similar to `std::swap` for `variant`s.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
