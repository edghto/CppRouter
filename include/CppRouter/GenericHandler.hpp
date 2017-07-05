#ifndef CPPROUTER_GENERICHANDLER_HPP
#define CPPROUTER_GENERICHANDLER_HPP

namespace CppRouter {

struct Constraint
{
    const char* constraint;

    Constraint(const char* c)
        : constraint(c)
    {}
};

class GenericHandler
{
public:
    virtual void handle() = 0;
};

}  // namespace CppRouter

#endif // CPPROUTER_GENERICHANDLER_HPP