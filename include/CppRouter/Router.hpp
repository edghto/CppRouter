#ifndef CPPROUTER_ROUTER_HPP
#define CPPROUTER_ROUTER_HPP

#include <CppRouter/GenericHandler.hpp>
#include <CppRouter/MetaHandler.hpp>

#include <array>
#include <memory>
#include <string>

namespace CppRouter {

template <typename... Handlers>
class Router
{
  public:
    std::unique_ptr<GenericHandler> find(const std::string &endpoint)
    {
        for (auto& mh : handlers_)
        {
            auto tmp = mh.tryToGetHandler(endpoint);
            if (tmp)
                return std::move(tmp);
        }
        return nullptr;
    }

  private:
    std::array<MetaHandler, sizeof...(Handlers)> handlers_ = handlers_initializer();

    constexpr std::array<MetaHandler, sizeof...(Handlers)> handlers_initializer()
    {
        return {MetaHandler::make<Handlers>()...};
    }
};

template <typename... Handlers>
auto makeRouter()
{
    return Router<Handlers...>();
}

} // namespace CppRouter

#endif // CPPROUTER_ROUTER_HPP
