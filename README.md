# CppRouter
C++ implementation of web request router.
Thread-safe, highly influenced by ASP.NET MVC 5 conventions. 

## Dependencies
*  `boost::regex`
*  `boost::format`

## Creating a handler
Following handler will match request like:
*  /api/foo/**30**/action/**turnOn**

```c++
class PostFooAction : public CppRouter::GenericHandler {
public:
    struct Params {
        int id;
        CppRouter::Constraint id_constraints = "[0-9]+";
        std::string name;
    };

    static constexpr const char* route = "/api/foo/{id}/action/{name}";

    PostFooAction(Params params) {}
    void handle() override {}
};

BOOST_FUSION_ADAPT_STRUCT(
    PostFooAction::Params,
    (int, id)
    (CppRouter::Constraint, id_constraints)
    (std::string, name)
);
```

Except implementing interface `CppRouter::GenericHandler` one has to provide:
*  static field named `route` which describes syntax of request, 
*  structure named `Params` - maybe empty,
*  fusion sequence using `BOOST_FUSION_ADAPT_STRUCT`.

Structure `Params` together with field `route` allow for matching incoming request and extracting parameters from that request. Make notice that `route` may contain segments like `{NAME}` which has to map fields in `Params` struct. 

Additionaly one can provide a constraint for each parameter. For that use `CppRouter::Constraint` type and make sure that if parameter is named `NAME` then corresponding constraint is named `NAME_constraint`. Constraint it self is a regular expression. `boost::regex` is used under the hood.

There are some default constraints for `int` and `std::string` types, check `include/CppRouter/DefaultConstraints.hpp` file. You can easly provide your own common constraints for parameters.

## Using router
For provided request, router finds matching handlers. `makeRouter` creates some intermediate representation called `MetaHandler`. Handlers are created only on successful match. It is safe to call `find` from multiple threads. 

```c++
auto router = CppRouter::makeRouter<PostFooAction,GetFoo>();
auto handler = router.find("/api/foo/30/action/turnOn");
if(handler)
    handler->handle();
```
