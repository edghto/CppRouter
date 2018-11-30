#ifndef CPPROUTER_DERAILS_ROUTEMATCHER_HPP
#define CPPROUTER_DERAILS_ROUTEMATCHER_HPP

#include <CppRouter/DefaultConstraints.hpp>
#include <CppRouter/details/ParameterManager.hpp>
#include <FusionVisitor/for_each.hpp>

#include <boost/format.hpp>
#include <boost/regex.hpp>

#include <string>

namespace CppRouter
{
namespace details
{

template <typename RouteHandler>
struct RouteMatcher
{
    RouteMatcher()
    {
        auto routeDesc = std::string(RouteHandler::route);
        auto constraints = parameterConstraints();
        route_ = constructRoute(routeDesc, constraints);
    }

    bool operator()(boost::smatch &matches, const std::string &request) const
    {
        return match(matches, request);
    }

  private:
    std::string constructRoute(const std::string &routeDesc,
                               decltype(ParameterManager::parameterConstraints) &constraints)
    {
        std::string route = routeDesc;
        for (auto constraint : constraints)
        {
            // TODO: Replace boost format with something newer.
            auto paramPlaceHolder = boost::regex(str(boost::format("\\{%s\\}") % constraint.first));
            auto paramConstraint = str(boost::format("(?<%s>%s)") % constraint.first % constraint.second);
            route = boost::regex_replace(route,
                                         paramPlaceHolder,
                                         paramConstraint);
        }

        return route;
    }

    decltype(ParameterManager::parameterConstraints) parameterConstraints()
    {
        typename RouteHandler::Params params{};
        ParameterManager parameterManager{};
        StructIterator::Fusion<typename RouteHandler::Params>::for_each(params, parameterManager);

        return std::move(parameterManager.parameterConstraints);
    }

    bool match(boost::smatch &matches, const std::string &request) const
    {
        boost::regex re(route_);
        return boost::regex_match(request.begin(), request.end(), matches, re);
    }

    std::string route_;
};

} // namespace details
} // namespace CppRouter

#endif // CPPROUTER_DERAILS_ROUTEMATCHER_HPP
