#ifndef CPPROUTER_DERAILS_ROUTEMATCHER_HPP
#define CPPROUTER_DERAILS_ROUTEMATCHER_HPP

#include <string>

#include <boost/format.hpp>
#include <boost/regex.hpp>

#include <FusionVisitor/for_each.hpp>

#include <CppRouter/DefaultConstraints.hpp>
#include <CppRouter/details/ParameterManager.hpp>
#include <CppRouter/details/ParameterExtractor.hpp>

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

        auto isMatched = match(route, request);

        if(isMatched)
            extractParameters();

        return isMatched;
    }

    typename RouteHandler::Params params{};

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
        StructIterator::Fusion<typename RouteHandler::Params>::for_each(params, parameterManager);

        return std::move(parameterManager.parameterConstraints);
    }

    bool match(std::string routeDesc, const std::string& request)
    {
        //TODO clear matches_ on every run
        boost::regex re(routeDesc);

        if(!boost::regex_match(request.begin(), request.end(), matches_, re))
            return false;

        return true;
    }

    auto extractParameters()
    {
        ParameterExtractor extractor{matches_};
        StructIterator::Fusion<typename RouteHandler::Params>::for_each(params, extractor);
    }

    boost::smatch matches_;
};

} // namespace details
} // namespace CppRouter

#endif // CPPROUTER_DERAILS_ROUTEMATCHER_HPP
