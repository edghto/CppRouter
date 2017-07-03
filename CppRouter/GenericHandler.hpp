#ifndef CPPROUTER_GENERICHANDLER_HPP
#define CPPROUTER_GENERICHANDLER_HPP

namespace CppRouter {

class GenericHandler
{
public:
    virtual void handle() = 0;
};

}  // namespace CppRouter

#endif // CPPROUTER_GENERICHANDLER_HPP
