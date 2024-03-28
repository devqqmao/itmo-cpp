#include <catch2/catch_test_macros.hpp>

#include <arrays/arrays.h>

using namespace mse;

TEST_CASE("trace_empty_matrix", "[trace]") {
  std::vector<std::vector<std::int32_t>> input;
  const auto res = trace(input);
  REQUIRE(res == 0);
}

TEST_CASE("trace_matrix_1x1", "[trace]") {
  std::vector<std::vector<std::int32_t>> input = {{1}};
  const auto res = trace(input);
  REQUIRE(res == 1);
}

TEST_CASE("trace_matrix_1x1_negative", "[trace]") {
  std::vector<std::vector<std::int32_t>> input = {{-1}};
  const auto res = trace(input);
  REQUIRE(res == -1);
}

TEST_CASE("trace_matrix_2x2", "[trace]") {
  std::vector<std::vector<std::int32_t>> input = {
      {-1, 1},
      {1, -1},
  };
  const auto res = trace(input);
  REQUIRE(res == -2);
}

TEST_CASE("trace_matrix_3x3", "[trace]") {
  std::vector<std::vector<std::int32_t>> input = {
      {-1, 1, 1},
      {-1, 10, 1},
      {5, 1, -2},
  };
  const auto res = trace(input);
  REQUIRE(res == 7);
}

TEST_CASE("trace_matrix_100x100", "[trace]") {
  constexpr auto size = 100u;
  std::vector<std::vector<std::int32_t>> input(
      100, std::vector<std::int32_t>(100, 0));

  for (auto i = 0u; i < size; ++i) {
    for (auto j = 0u; j < size; ++j) {
      input[i][j] = static_cast<std::int32_t>(i + j);
    }
  }

  const auto res = trace(input);
  REQUIRE(res == size * (size - 1));
}
