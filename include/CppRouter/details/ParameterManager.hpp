#ifndef CPPROUTER_DETAILS_PARAMETERMANAGER_HPP
#define CPPROUTER_DETAILS_PARAMETERMANAGER_HPP

#include <CppRouter/DefaultConstraints.hpp>

#include <map>
#include <string>

namespace CppRouter {
namespace details {

struct ParameterManager
{
    template<typename T>
    void operator()(const char* name, T& value)
    {
        parameterConstraints[name] = CppRouter::DefaultConstraints::get(value);
    }

    std::map<std::string, std::string> parameterConstraints;
};

} // namespace details
} // namespace CppRouter

#endif // CPPROUTER_DETAILS_PARAMETERMANAGER_HPPs
