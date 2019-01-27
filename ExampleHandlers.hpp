#ifndef EXAMPLEHANDLERS_HPP
#define EXAMPLEHANDLERS_HPP

#include <CppRouter/GenericHandler.hpp>
#include <string>

class PostFooAction
    : public CppRouter::GenericHandler
{
public:
    using tag = CppRouter::post_tag;
    struct Params
    {
        int id;
        CppRouter::Constraint id_constraints = "[0-9]+";

        std::string name;
    };

    static constexpr const char* route = "/api/foo/{id}/action/{name}";

    PostFooAction(Params params)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " " << params.id << " " << params.name << std::endl;
    }

    virtual void handle() override
    {
        std::cout << __PRETTY_FUNCTION__ <<  std::endl;
    }
};

class GetFoo
    : public CppRouter::GenericHandler
{
public:
    using tag = CppRouter::get_tag;
    struct Params
    {
        int id;
        CppRouter::Constraint id_constraints = "[0-9]+";
    };

    static constexpr const char* route = "/api/foo/{id}";

    GetFoo(Params params)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " " << params.id << std::endl;
    }

    virtual void handle() override
    {
        std::cout << __PRETTY_FUNCTION__ <<  std::endl;
    }
};

BOOST_FUSION_ADAPT_STRUCT(
    PostFooAction::Params,
    (int, id)
    (CppRouter::Constraint, id_constraints)
    (std::string, name)
);

BOOST_FUSION_ADAPT_STRUCT(
    GetFoo::Params,
    (int, id)
    (CppRouter::Constraint, id_constraints)
);

#endif // EXAMPLEHANDLERS_HPP
