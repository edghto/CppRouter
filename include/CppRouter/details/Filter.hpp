#ifndef CPPROUTER_DETAILS_FILTER_HPP
#define CPPROUTER_DETAILS_FILTER_HPP

#include <stx/list.hpp>

#include <type_traits>

namespace CppRouter {

namespace details {

template <typename Tag, typename... Ts> struct filter {};

template <typename Tag, template<typename...> class L, typename T, typename... Ts>
struct filter<Tag, L<T, Ts...>> {
  using value = std::conditional_t<
      std::is_same<Tag, typename T::tag>::value,
      typename stx::prepend<T, typename filter<Tag, stx::list<Ts...>>::value>::value,
      typename filter<Tag, stx::list<Ts...>>::value>;
};

template <typename Tag> struct filter<Tag, stx::empty_list> { using value = stx::empty_list; };

} // namespace details

} // namespace CppRouter

#endif // CPPROUTER_DETAILS_FILTER_HPP
