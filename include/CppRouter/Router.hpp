#ifndef CPPROUTER_ROUTER_HPP
#define CPPROUTER_ROUTER_HPP

#include <CppRouter/GenericHandler.hpp>
#include <CppRouter/MetaHandler.hpp>
#include <CppRouter/details/Filter.hpp>

#include <array>
#include <memory>
#include <string>

namespace CppRouter {

enum class Method {
  Get,
  Post,
  Put,
  Delete,
  Patch,
  Option,
  Header,
};

template <typename... Handlers> class Router {
public:
  std::unique_ptr<GenericHandler> find(const std::string &endpoint) {
    // FIXME: There must be a cleaner way.
    std::unique_ptr<GenericHandler> handler = findImpl(endpoint, getHandlers_);
    if (handler)
      return std::move(handler);
    handler = findImpl(endpoint, postHandlers_);
    if (handler)
      return std::move(handler);
    handler = findImpl(endpoint, putHandlers_);
    if (handler)
      return std::move(handler);
    handler = findImpl(endpoint, deleteHandlers_);
    if (handler)
      return std::move(handler);
    handler = findImpl(endpoint, patchHandlers_);
    if (handler)
      return std::move(handler);
    handler = findImpl(endpoint, optionHandlers_);
    if (handler)
      return std::move(handler);
    return findImpl(endpoint, headerHandlers_);
  }

  std::unique_ptr<GenericHandler> findByMethod(Method method,
                                               const std::string &endpoint) {
    switch (method) {
    case Method::Get:
      return findImpl(endpoint, getHandlers_);
    case Method::Post:
      return findImpl(endpoint, postHandlers_);
    case Method::Put:
      return findImpl(endpoint, putHandlers_);
    case Method::Delete:
      return findImpl(endpoint, deleteHandlers_);
    case Method::Patch:
      return findImpl(endpoint, patchHandlers_);
    case Method::Option:
      return findImpl(endpoint, optionHandlers_);
    case Method::Header:
      return findImpl(endpoint, headerHandlers_);
    default:
      return nullptr;
    }
  }

private:
  using GetHandlers =
      typename details::filter<get_tag, stx::list<Handlers...>>::value;
  using PostHandlers =
      typename details::filter<post_tag, stx::list<Handlers...>>::value;
  using PutHandlers =
      typename details::filter<put_tag, stx::list<Handlers...>>::value;
  using DeleteHandlers =
      typename details::filter<delete_tag, stx::list<Handlers...>>::value;
  using PatchHandlers =
      typename details::filter<patch_tag, stx::list<Handlers...>>::value;
  using OptionHandlers =
      typename details::filter<option_tag, stx::list<Handlers...>>::value;
  using HeaderHandlers =
      typename details::filter<header_tag, stx::list<Handlers...>>::value;

  std::array<MetaHandler, stx::size<GetHandlers>::value> getHandlers_ =
      Initializer<GetHandlers>::init();

  std::array<MetaHandler, stx::size<PostHandlers>::value> postHandlers_ =
      Initializer<PostHandlers>::init();

  std::array<MetaHandler, stx::size<PutHandlers>::value> putHandlers_ =
      Initializer<PutHandlers>::init();

  std::array<MetaHandler, stx::size<DeleteHandlers>::value> deleteHandlers_ =
      Initializer<DeleteHandlers>::init();

  std::array<MetaHandler, stx::size<PatchHandlers>::value> patchHandlers_ =
      Initializer<PatchHandlers>::init();

  std::array<MetaHandler, stx::size<OptionHandlers>::value> optionHandlers_ =
      Initializer<OptionHandlers>::init();

  std::array<MetaHandler, stx::size<HeaderHandlers>::value> headerHandlers_ =
      Initializer<HeaderHandlers>::init();

  template <unsigned int N>
  std::unique_ptr<GenericHandler>
  findImpl(const std::string &endpoint, std::array<MetaHandler, N> &handlers) {
    for (auto &mh : handlers) {
      auto tmp = mh.tryToGetHandler(endpoint);
      if (tmp)
        return std::move(tmp);
    }
    return nullptr;
  }

  template <typename... Ts> struct Initializer {};

  template <template <typename...> class L, typename... Ts>
  struct Initializer<L<Ts...>> {
    static constexpr std::array<MetaHandler, sizeof...(Ts)> init() {
      return {MetaHandler::make<Ts>()...};
    }
  };
};

template <typename... Handlers> auto makeRouter() {
  return Router<Handlers...>();
}

} // namespace CppRouter

#endif // CPPROUTER_ROUTER_HPP
