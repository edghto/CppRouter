#ifndef CPPROUTER_DERAILS_ROUTEMATCHER_HPP
#define CPPROUTER_DERAILS_ROUTEMATCHER_HPP

#include <string>
#include <utility>

#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/di.hpp>

#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/sequence.hpp>

#include <FusionVisitor/for_each.hpp>

#include <CppRouter/DefaultConstraints.hpp>
#include <CppRouter/Literals.hpp>
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

    auto params()
    {
//        return paramsImpl(std::make_index_sequence<boost::fusion::result_of::size<typename RouteHandler::Params>::value>());
        return paramsImpl(std::make_index_sequence<1>());
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
        StructIterator::Fusion<typename RouteHandler::Params>::for_each(params_, parameterManager);

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
        StructIterator::Fusion<typename RouteHandler::Params>::for_each(params_, extractor);
    }

    template<size_t... Idx>
    auto paramsImpl(std::index_sequence<Idx...>)
    {
        using S = typename RouteHandler::Params;
        return boost::di::make_injector( paramToInjector<S,Idx>(params_) ... );
    }

    template<typename S, size_t Idx>
    auto paramToInjector(S& s)
    {
        using name_t = boost::fusion::extension::struct_member_name<S, Idx>;
        using type_t = typename std::remove_reference<decltype(boost::fusion::at_c<Idx>(params_))>::type;

        return boost::di::bind<type_t>()
            .named("id"_s)
            .to(boost::fusion::at_c<Idx>(s));
    }

    typename RouteHandler::Params params_{};

    boost::smatch matches_;
};

} // namespace details
} // namespace CppRouter

#endif // CPPROUTER_DERAILS_ROUTEMATCHER_HPP
