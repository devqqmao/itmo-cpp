#include <catch2/catch_test_macros.hpp>

#include <tutorial/message.h>

using namespace mse;

TEST_CASE("message", "[tutorial]") {
  REQUIRE(mse::message() == "Hello, World!");
}
