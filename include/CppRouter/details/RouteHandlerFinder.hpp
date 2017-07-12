#ifndef CPPROUTER_DETAILS_ROUTEHANDLERFINDER_HPP
#define CPPROUTER_DETAILS_ROUTEHANDLERFINDER_HPP

#include <CppRouter/GenericHandler.hpp>
#include <CppRouter/details/RouteMatcher.hpp>

#include <memory>
#include <stdexcept>
#include <string>

namespace CppRouter {
namespace details {

template<typename First, typename ...Tail>
struct RouteHandlerFinder
{
    static std::unique_ptr<GenericHandler> find(const std::string& request)
    {
        RouteMatcher<First> matcher{};

        if(matcher(request))
            return std::make_unique<First>(matcher.params);
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
            return std::make_unique<Last>(matcher.params);

        throw std::runtime_error("No handler for route: " + request);
    }
};

} // namespace details
} // namespace CppRouter

#endif // CPPROUTER_DETAILS_ROUTEHANDLERFINDER_HPP
