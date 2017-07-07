#ifndef CPPROUTER_DERAILS_ROUTEMATCHER_HPP
#define CPPROUTER_DERAILS_ROUTEMATCHER_HPP

#include <string>

#include <boost/format.hpp>
#include <boost/regex.hpp>

#include <FusionVisitor/for_each.hpp>

#include <CppRouter/DefaultConstraints.hpp>
#include <CppRouter/details/ParameterManager.hpp>

namespace CppRouter {
namespace details {

template<typename RouteHandler>
struct RouteMatcher
{
    bool operator()(const std::string& request)
    {
        auto routeDesc = std::string(RouteHandler::route);
        auto constraints = parameterConstraints();

        auto route = constructRoute(routeDesc, constraints);

        return match(route, request);
    }

private:
    std::string constructRoute(const std::string& routeDesc,
                               decltype(ParameterManager::parameterConstraints)& constraints)
    {
        std::string route = routeDesc;
        for(auto constraint : constraints)
        {
            auto paramPlaceHolder = boost::regex(str(boost::format("\\{%s\\}") % constraint.first));
            auto paramConstraint = str(boost::format("(?<%s>%s)") % constraint.first % constraint.second);
            route = boost::regex_replace(route,
                                      paramPlaceHolder,
                                      paramConstraint);
        }

        return std::move(route);
    }

    decltype(ParameterManager::parameterConstraints) parameterConstraints()
    {
        ParameterManager parameterManager{};
        typename RouteHandler::Params params{};
        StructIterator::Fusion<typename RouteHandler::Params>::for_each(params, parameterManager);

        return std::move(parameterManager.parameterConstraints);
    }

    bool match(std::string routeDesc, const std::string& request)
    {
        boost::smatch m;
        boost::regex re(routeDesc);

        if(!boost::regex_match(request.begin(), request.end(), m, re))
            return false;

        return true;
    }
};

} // namespace details
} // namespace CppRouter

#endif // CPPROUTER_DERAILS_ROUTEMATCHER_HPP
