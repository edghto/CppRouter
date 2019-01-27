#ifndef STX_LIST_HPP
#define STX_LIST_HPP

namespace stx {

template <typename... Ts> struct list {};

using empty_list = list<>;

template <typename... Ts> struct append {};

template <template <typename...> class L, typename I, typename... Is>
struct append<L<Is...>, I> {
  using value = list<Is..., I>;
};

template <typename... Ts> struct prepend {};

template <template <typename...> class L, typename I, typename... Is>
struct prepend<I,L<Is...>> {
  using value = list<I, Is...>;
};

template <typename L> struct size {};

template <template <typename...> class L, typename... Is>
struct size<L<Is...>> {
  static constexpr int value = sizeof...(Is);
};

} // namespace stx

#endif // STX_LIST_HPP
