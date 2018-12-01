#ifndef CPPROUTER_METAHANDLER_HPP
#define CPPROUTER_METAHANDLER_HPP

#include <CppRouter/GenericHandler.hpp>
#include <CppRouter/details/ParametersApplier.hpp>
#include <CppRouter/details/RouteMatcher.hpp>

#include <boost/regex.hpp>

#include <functional>
#include <memory>
#include <string>

namespace CppRouter {

class MetaHandler {
public:
  std::unique_ptr<GenericHandler> tryToGetHandler(const std::string &endpoint) {
    return matcher_(endpoint);
  }

  template <typename T> static MetaHandler make() {
    MetaHandler mh;
    details::RouteMatcher<T> m;
    mh.matcher_ = [matcher = std::move(m)](const std::string &endpoint) {
      details::ParametersApplier<T> params;
      auto isMatched = matcher(params.matches, endpoint);
      return isMatched ? std::make_unique<T>(params()) : nullptr;
    };
    return mh;
  }

private:
  using Matcher = std::function<std::unique_ptr<GenericHandler>(
      const std::string &endpoint)>;
  Matcher matcher_;
};

} // namespace CppRouter

#endif // CPPROUTER_METAHANDLER_HPP
