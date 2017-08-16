# CppRouter

C++ implementation of web request router.
Highly influenced by ASP.NET MVC 5.

You have to provide implementation of handlers. Each handler has to provide route description, parameter structure with constraints.
For provided request, router finds matching handlers and invokes it.

Check [main.cpp] and [ExampleHandlers.hpp] for example.

It will produce output like this:
```
endpoint: /api/foo/15
GetFoo:47 15
virtual void GetFoo::handle()
endpoint: /api/foo/30/action/boo
PostFooAction:24 30 boo
virtual void PostFooAction::handle()
```
