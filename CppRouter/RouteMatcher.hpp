#ifndef CPPROUTER_DERAILS_ROUTEMATCHER_HPP
#define CPPROUTER_DERAILS_ROUTEMATCHER_HPP

#include <regex>
#include <string>

namespace CppRouter {
namespace details {

template<typename RouteHandler>
struct RouteMatcher
{
    bool operator()(const std::string& request)
    {
        auto routeDesc = std::string(RouteHandler::route);
        return  match(routeDesc, request);
    }

private:
    bool match(std::string routeDesc, const std::string& request)
    {
        std::cmatch m;
        std::regex re(routeDesc); // TODO mwlodarczyk: construct correctly

        if(!std::regex_match(request.c_str(), m, re))
            return false;

        return true;
    }
};

} // namespace details
} // namespace CppRouter

#endif // CPPROUTER_DERAILS_ROUTEMATCHER_HPP
