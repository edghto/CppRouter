#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <vector>

#include <CppRouter/CppRouter.hpp>
#include <ExampleHandlers.hpp>

int main()
{
    auto router = CppRouter::makeRouter<PostFooAction,GetFoo>();

    std::set<std::string> endpoints = {"/api/foo/15", "/api/foo/30/action/boo", "api/foo", "/api/foo/boo", "/api/foo/30/action/"};

    for (auto endpoint : endpoints)
    {
        std::cout << "endpoint: " << endpoint << std::endl;
        auto handler = router.find(endpoint);
        if(handler)
            handler->handle();
    }

    return 0;
}
