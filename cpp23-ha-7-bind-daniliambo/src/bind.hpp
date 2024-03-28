#pragma once

#include <optional>
#include <tuple>
#include <type_traits>
#include <utility>

namespace fn {

struct placeholder_1 {};
struct placeholder_2 {};

// Объекты-плейсхолдеры
constexpr placeholder_1 _1{};
constexpr placeholder_2 _2{};

namespace details {

struct Arguments {};

template <typename Bind, typename Arg1 = Arguments, typename Arg2 = Arguments>
struct bind_impl {
  Bind f;
  std::optional<Arg1> arg1;
  std::optional<Arg2> arg2;

  bind_impl(Bind f, Arg1 a1 = Arguments(), Arg2 a2 = Arguments())
      : f(f), arg1(a1), arg2(a2) {}

  auto operator()() -> decltype(auto) {
    if constexpr (std::is_same_v<Arg1, Arguments>) {
      return f();
    } else {
      if constexpr (std::is_same_v<Arg2, Arguments>) {
        return f(*arg1);
      } else {
        return f(*arg1, *arg2);
      }
    }
  }
  template <typename F2, typename Tuple, std::size_t... I>
  auto call_with_tuple(F2 f, Tuple &&t, std::index_sequence<I...>) {
    return f(std::get<I>(std::forward<Tuple>(t))...);
  }
  template <typename... Args>
  auto operator()([[maybe_unused]] Args &&...args) -> decltype(auto) {

    if constexpr (std::is_same_v<Arg1, placeholder_1>) {

      if constexpr (std::is_same_v<Arg2, placeholder_1>) {
        return f(std::get<0>(std::forward_as_tuple(args...)),
                 std::get<0>(std::forward_as_tuple(args...)));
      } else if constexpr (std::is_same_v<Arg2, placeholder_2>) {
        auto args_tuple = std::forward_as_tuple(std::forward<Args>(args)...);
        return call_with_tuple(f, std::move(args_tuple),
                               std::index_sequence_for<Args...>{});
      } else {

        if constexpr (std::is_same_v<Arg2, Arguments>) {
          auto args_tuple = std::forward_as_tuple(std::forward<Args>(args)...);
          return f(std::forward<std::tuple_element_t<0, decltype(args_tuple)>>(
              std::get<0>(args_tuple)));

        } else {
          return f(std::get<0>(std::forward_as_tuple(args...)), *arg2);
        }
      }
    } else if constexpr (std::is_same_v<Arg1, placeholder_2>) {

      if constexpr (std::is_same_v<Arg2, placeholder_1>) {
        return f(std::get<1>(std::forward_as_tuple(args...)),
                 std::get<0>(std::forward_as_tuple(args...)));
      } else if constexpr (std::is_same_v<Arg2, placeholder_2>) {
        return f(std::get<1>(std::forward_as_tuple(args...)),
                 std::get<1>(std::forward_as_tuple(args...)));
      } else if constexpr (!std::is_same_v<Arg2, Arguments>) {
        return f(std::get<1>(std::forward_as_tuple(args...)), *arg2);
      } else {
        return f(std::get<1>(std::forward_as_tuple(args...)));
      }
    } else if constexpr (!std::is_same_v<Arg1, Arguments>) {

      if constexpr (std::is_same_v<Arg2, placeholder_1>) {
        return f(*arg1, std::get<0>(std::forward_as_tuple(args...)));
      } else if constexpr (std::is_same_v<Arg2, placeholder_2>) {
        return f(*arg1, std::get<1>(std::forward_as_tuple(args...)));
      } else {
        return f(*arg1, *arg2);
      }
    } else {
      return f();
    }
  }
};

} // namespace details

template <typename Bind> details::bind_impl<Bind> bind(Bind f) {
  return details::bind_impl<Bind>(f);
}

template <typename Bind, typename Arg1>
details::bind_impl<Bind, Arg1> bind(Bind f, Arg1 a1) {
  return details::bind_impl<Bind, Arg1>(f, a1);
}

template <typename Bind, typename Arg1, typename Arg2>
details::bind_impl<Bind, Arg1, Arg2> bind(Bind f, Arg1 a1, Arg2 a2) {
  return details::bind_impl<Bind, Arg1, Arg2>(f, a1, a2);
}

} // namespace fn
