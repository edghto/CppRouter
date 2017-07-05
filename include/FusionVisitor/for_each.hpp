#ifndef STRUCTITERATOR_FOREACH_HPP
#define STRUCTITERATOR_FOREACH_HPP

#include <FusionVisitor/fusion_visitor.hpp>
#include <utility>

namespace StructIterator {

template<typename Struct>
struct Fusion
{
    template<typename Functor>
    static inline void for_each(Struct& s, Functor&& f)
    {
        FusionVisitor<Struct, Functor>::visit(s, std::forward<Functor>(f));
    }
};

} // namespace StructIterator


#endif // STRUCTITERATOR_FOREACH_HPP
