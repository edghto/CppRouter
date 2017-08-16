#ifndef CPPROUTER_DETAILS_ROUTEHANDLERFINDER_HPP
#define CPPROUTER_DETAILS_ROUTEHANDLERFINDER_HPP

#include <CppRouter/GenericHandler.hpp>
#include <CppRouter/details/RouteMatcher.hpp>

#include <memory>
#include <stdexcept>
#include <string>

#include <boost/di.hpp>

namespace CppRouter {
namespace details {

template<typename Handler, typename Matcher>
auto make_handler(Matcher& m)
{
    auto injector = m.params();
    return injector.template create<std::unique_ptr<Handler>>();
}

template<typename First, typename ...Tail>
struct RouteHandlerFinder
{
    static std::unique_ptr<GenericHandler> find(const std::string& request)
    {
        RouteMatcher<First> matcher{};

        if(matcher(request))
            return make_handler<First>(matcher);
        else
            return RouteHandlerFinder<Tail...>::find(request);
    }
};

template<typename Last>
struct RouteHandlerFinder<Last>
{
    static std::unique_ptr<GenericHandler> find(const std::string &request)
    {
        RouteMatcher<Last> matcher{};
        if(matcher(request))
            return make_handler<Last>(matcher);

        throw std::runtime_error("No handler for route: " + request);
    }
};

} // namespace details
} // namespace CppRouter

#endif // CPPROUTER_DETAILS_ROUTEHANDLERFINDER_HPP
