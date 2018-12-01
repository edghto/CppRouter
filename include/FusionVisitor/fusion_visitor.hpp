#ifndef STRUCTITERATOR_FUSIONVISITOR_HPP
#define STRUCTITERATOR_FUSIONVISITOR_HPP

#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/sequence.hpp>
#include <boost/mpl/next.hpp>

namespace StructIterator {

namespace detail {

template <typename Struct, typename Functor, typename N>
struct FusionVisitorImpl {
  using next_t = typename boost::mpl::next<N>::type;
  using name_t = boost::fusion::extension::struct_member_name<Struct, N::value>;

  static inline void visit(Struct &s, Functor &f) {
    f(name_t::call(), boost::fusion::at<N>(s));
    FusionVisitorImpl<Struct, Functor, next_t>::visit(s, f);
  }
};

template <typename Struct, typename Functor>
struct FusionVisitorImpl<
    Struct, Functor, typename boost::fusion::result_of::size<Struct>::type> {
  static inline void visit(Struct &, Functor &) {}
};

} // namespace detail

template <typename Struct, typename Functor>
using FusionVisitor =
    detail::FusionVisitorImpl<Struct, Functor, boost::mpl::int_<0>>;

} // namespace FusionVisitor

#endif // STRUCTITERATOR_FUSIONVISITOR_HPP
