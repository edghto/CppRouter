#ifndef CPPROUTER_GENERICHANDLER_HPP
#define CPPROUTER_GENERICHANDLER_HPP

#include <boost/fusion/adapted/struct.hpp>

// TODO: Rename this file to HandlerCommon or something similar.
namespace CppRouter {

struct Constraint {
  const char *constraint;

  Constraint(const char *c) : constraint(c) {}
};

struct get_tag {};
struct post_tag {};
struct put_tag {};
struct delete_tag {};
struct patch_tag {};
struct option_tag {};
struct header_tag {};

class GenericHandler {
public:
  virtual void handle() = 0;
};

} // namespace CppRouter

#endif // CPPROUTER_GENERICHANDLER_HPP
