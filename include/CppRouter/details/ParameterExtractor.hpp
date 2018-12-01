#ifndef CPPROUTER_DETAILS_PARAMETEREXTRACTOR_HPP
#define CPPROUTER_DETAILS_PARAMETEREXTRACTOR_HPP

#include <CppRouter/GenericHandler.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

namespace CppRouter {
namespace details {

struct ParameterExtractor {
  boost::smatch &matches_;

  template <typename T> void operator()(const char *name, T &value) {
    value = boost::lexical_cast<T>(matches_[name]);
  }

  void operator()(const char *, CppRouter::Constraint &) {
    // ignore
  }
};

} // namespace details
} // namespace CppRouter

#endif // CPPROUTER_DETAILS_PARAMETEREXTRACTOR_HPP
