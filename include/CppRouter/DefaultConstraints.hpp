#ifndef CPPROUTER_DEFAULTCONSTRAINTS_HPP
#define CPPROUTER_DEFAULTCONSTRAINTS_HPP

#include <string>
#include <utility>
#include <CppRouter/GenericHandler.hpp>

namespace CppRouter {
namespace DefaultConstraints {

    template<typename T>
    std::string get(T);

    template<>
    std::string get(int)
    {
        return R"(-?\\d+)";
    }

    template<>
    std::string get(std::string)
    {
        return R"([\\w_-]+)";
    }

    template<>
    std::string get(Constraint value)
    {
        return std::move(std::string(value.constraint));
    }

} // namespace DefaultConstraints
} // namespace CppRouter

#endif // CPPROUTER_DEFAULTCONSTRAINTS_HPP
