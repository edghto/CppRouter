#include <CppRouter/CppRouter.hpp>
#include <ExampleHandlers.hpp>

#include <cassert>

int main() {
  auto router = CppRouter::makeRouter<PostFooAction, GetFoo>();

  {
    auto handler = router.find("/api/foo/15");
    assert(handler);
    handler->handle();
  }
  {
    auto handler = router.find("/api/foo/30/action/boo");
    assert(handler);
    handler->handle();
  }
  {
    auto handler = router.find("api/foo");
    assert(!handler);
  }
  {
    auto handler = router.find("/api/foo/boo");
    assert(!handler);
  }
  {
    auto handler = router.find("/api/foo/30/action/");
    assert(!handler);
  }
  {
    auto handler = router.findByMethod(CppRouter::Method::Get, "/api/foo/15");
    assert(handler);
    handler->handle();
  }
  {
    auto handler =
        router.findByMethod(CppRouter::Method::Post, "/api/foo/30/action/boo");
    assert(handler);
    handler->handle();
  }
  {
    auto handler = router.findByMethod(CppRouter::Method::Put, "/api/foo/15");
    assert(!handler);
  }
  {
    auto handler = router.findByMethod(CppRouter::Method::Delete,
                                       "/api/foo/30/action/boo");
    assert(!handler);
  }

  return 0;
}
