#include <iostream>
#include <string>
#include <set>

#include <CppRouter/CppRouter.hpp>
#include <ExampleHandlers.hpp>

int main()
{
    auto router = CppRouter::make_router<PostFooAction, GetFoo>();
    std::set<std::string> endpoints = {"/api/foo/15", "/api/foo/30/action/boo"};

    for(auto endpoint: endpoints)
    {
        std::cout << "endpoint: " << endpoint << std::endl;
        auto handler = router.handler(endpoint);
        handler->handle();
    }

    return 0;
}
