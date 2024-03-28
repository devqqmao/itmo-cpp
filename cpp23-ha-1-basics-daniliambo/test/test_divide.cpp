#include <catch2/catch_test_macros.hpp>

#include <basics/numbers.h>

using namespace mse;

TEST_CASE("divide_0_any", "[devide]") { REQUIRE(divide(0, 123) == 0); }

TEST_CASE("divide_0_any_negative", "[devide]") {
  REQUIRE(divide(0, -123) == 0);
}

TEST_CASE("divide_any_1", "[devide]") { REQUIRE(divide(321, 1) == 321); }

TEST_CASE("divide_any_negative_1", "[devide]") {
  REQUIRE(divide(-321, 1) == -321);
}

TEST_CASE("divide_any_-1", "[devide]") { REQUIRE(divide(321, -1) == -321); }

TEST_CASE("divide_any_negative_-1", "[devide]") {
  REQUIRE(divide(-321, -1) == 321);
}

TEST_CASE("divide_1_1", "[devide]") { REQUIRE(divide(1, 1) == 1); }

TEST_CASE("divide_-1_1", "[devide]") { REQUIRE(divide(-1, 1) == -1); }

TEST_CASE("divide_1_-1", "[devide]") { REQUIRE(divide(1, -1) == -1); }

TEST_CASE("divide_-1_-1", "[devide]") { REQUIRE(divide(-1, -1) == 1); }

TEST_CASE("divide_4_2", "[devide]") { REQUIRE(divide(4, 2) == 2); }

TEST_CASE("divide_-4_2", "[devide]") { REQUIRE(divide(-4, 2) == -2); }

TEST_CASE("divide_4_-2", "[devide]") { REQUIRE(divide(4, -2) == -2); }

TEST_CASE("divide_-4_-2", "[devide]") { REQUIRE(divide(-4, -2) == 2); }

TEST_CASE("divide_5_2", "[devide]") { REQUIRE(divide(5, 2) == 2); }

TEST_CASE("divide_-5_2", "[devide]") { REQUIRE(divide(-5, 2) == -2); }

TEST_CASE("divide_5_-2", "[devide]") { REQUIRE(divide(5, -2) == -2); }

TEST_CASE("divide_-5_-2", "[devide]") { REQUIRE(divide(-5, -2) == 2); }

TEST_CASE("divide_2_5", "[devide]") { REQUIRE(divide(2, 5) == 0); }

TEST_CASE("divide_-2_5", "[devide]") { REQUIRE(divide(-2, 5) == 0); }

TEST_CASE("divide_2_-5", "[devide]") { REQUIRE(divide(2, -5) == 0); }

TEST_CASE("divide_-2_-5", "[devide]") { REQUIRE(divide(-2, -5) == 0); }

TEST_CASE("divide_max_1", "[devide]") {
  REQUIRE(divide(std::numeric_limits<int>::max(), 1) ==
          std::numeric_limits<int>::max());
}

TEST_CASE("divide_0_max", "[devide]") {
  REQUIRE(divide(0, std::numeric_limits<int>::max()) == 0);
}

TEST_CASE("divide_min_1", "[devide]") {
  REQUIRE(divide(std::numeric_limits<int>::min(), 1) ==
          std::numeric_limits<int>::min());
}

TEST_CASE("divide_0_min", "[devide]") {
  REQUIRE(divide(0, std::numeric_limits<int>::min()) == 0);
}

TEST_CASE("divide_min_-1", "[devide]") {
  REQUIRE(divide(std::numeric_limits<int>::min(), -1) ==
          std::numeric_limits<int>::max());
}

TEST_CASE("divide_max_max", "[devide]") {
  REQUIRE(divide(std::numeric_limits<int>::max(),
                 std::numeric_limits<int>::max()) == 1);
}

TEST_CASE("divide_min_min", "[devide]") {
  REQUIRE(divide(std::numeric_limits<int>::min(),
                 std::numeric_limits<int>::min()) == 1);
}

TEST_CASE("divide_max_min", "[devide]") {
  REQUIRE(divide(std::numeric_limits<int>::max(),
                 std::numeric_limits<int>::min()) == 0);
}

TEST_CASE("divide_min_max", "[devide]") {
  REQUIRE(divide(std::numeric_limits<int>::min(),
                 std::numeric_limits<int>::max()) == -1);
}
