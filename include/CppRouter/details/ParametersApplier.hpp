#ifndef CPPROUTER_DETAILS_PARAMETERSAPPLIER_HPP
#define CPPROUTER_DETAILS_PARAMETERSAPPLIER_HPP

#include <CppRouter/details/ParameterExtractor.hpp>
#include <FusionVisitor/for_each.hpp>

#include <boost/regex.hpp>

namespace CppRouter {
namespace details {

template<typename RouteHandler>
struct ParametersApplier {
    boost::smatch matches;

    typename RouteHandler::Params operator()() {
        typename RouteHandler::Params params{};
        ParameterExtractor extractor{matches};
        StructIterator::Fusion<typename RouteHandler::Params>::for_each(params, extractor);
        return params;
    }
};

} // namespace details
} // namespace CppRouter

#endif // CPPROUTER_DETAILS_PARAMETERSAPPLIER_HPP
