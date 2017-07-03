#ifndef CPPROUTER_ROUTER_HPP
#define CPPROUTER_ROUTER_HPP

#include <CppRouter/RouteHandlerFinder.hpp>

namespace CppRouter {

template<typename... Handlers>
class Router
{
public:
    std::unique_ptr<GenericHandler> handler(const std::string& request)
    {
        auto handler = details::RouteHandlerFinder<Handlers...>::find(request);
        return std::move(handler);
    }

    std::array<std::string, sizeof...(Handlers)> routes_ = routes_initializer();

    constexpr std::array<std::string, sizeof...(Handlers)> routes_initializer()
    {
        return { Handlers::route ... };
    }
};

template<typename... Handlers>
auto make_router()
{
    return Router<Handlers...>();
}

} // namespace CppRouter

#endif // CPPROUTER_ROUTER_HPP
