#include <catch2/catch_test_macros.hpp>

#include <arrays/arrays.h>

using namespace mse;

TEST_CASE("max_square_empty_matrix", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input;
  const auto res = find_max_square(input);
  REQUIRE(res == 0);
}

TEST_CASE("max_square_matrix_1x1", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {{1}};
  const auto res = find_max_square(input);
  REQUIRE(res == 1);
}

TEST_CASE("max_square_matrix_1x1_zero", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {{0}};
  const auto res = find_max_square(input);
  REQUIRE(res == 0);
}

TEST_CASE("max_square_matrix_2x2_one", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {
      {1, 0},
      {0, 0},
  };
  const auto res = find_max_square(input);
  REQUIRE(res == 1);
}

TEST_CASE("max_square_matrix_2x2_one_another", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {
      {1, 1},
      {0, 0},
  };
  const auto res = find_max_square(input);
  REQUIRE(res == 1);
}

TEST_CASE("max_square_matrix_2x2_two", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {
      {1, 1},
      {1, 1},
  };
  const auto res = find_max_square(input);
  REQUIRE(res == 4);
}

TEST_CASE("max_square_matrix_2x2_zero", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {
      {0, 0},
      {0, 0},
  };
  const auto res = find_max_square(input);
  REQUIRE(res == 0);
}

TEST_CASE("max_square_matrix_4x4_three", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {
      {1, 1, 1, 1},
      {1, 1, 1, 1},
      {1, 1, 1, 1},
      {1, 1, 0, 1},
  };
  const auto res = find_max_square(input);
  REQUIRE(res == 9);
}

TEST_CASE("max_square_matrix_4x4_four", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {
      {1, 1, 1, 1},
      {1, 1, 1, 1},
      {1, 1, 1, 1},
      {1, 1, 1, 1},
  };
  const auto res = find_max_square(input);
  REQUIRE(res == 16);
}

TEST_CASE("max_square_matrix_5x5_one", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {
      {0, 0, 0, 0, 1}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
  };
  const auto res = find_max_square(input);
  REQUIRE(res == 1);
}

TEST_CASE("max_square_matrix_5x5_one_another", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {
      {0, 0, 0, 0, 1}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0}, {0, 0, 0, 0, 0},
  };
  const auto res = find_max_square(input);
  REQUIRE(res == 1);
}

TEST_CASE("max_square_matrix_5x5_one_yet_another", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {
      {1, 0, 0, 0, 1}, {0, 1, 1, 0, 0}, {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}, {1, 0, 0, 0, 1},
  };
  const auto res = find_max_square(input);
  REQUIRE(res == 1);
}

TEST_CASE("max_square_matrix_5x5_two", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {
      {1, 0, 0, 0, 1}, {0, 1, 1, 0, 0}, {0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0}, {1, 0, 0, 0, 1},
  };
  const auto res = find_max_square(input);
  REQUIRE(res == 4);
}

TEST_CASE("max_square_matrix_5x5_two_another", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {
      {1, 0, 0, 0, 1}, {1, 1, 1, 1, 0}, {0, 1, 1, 1, 0},
      {0, 0, 1, 1, 0}, {1, 0, 0, 0, 1},
  };
  const auto res = find_max_square(input);
  REQUIRE(res == 4);
}

TEST_CASE("max_square_matrix_5x5_three", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {
      {1, 1, 1, 0, 1}, {1, 1, 1, 1, 0}, {1, 1, 1, 1, 0},
      {0, 0, 1, 1, 0}, {1, 0, 0, 0, 1},
  };
  const auto res = find_max_square(input);
  REQUIRE(res == 9);
}

TEST_CASE("max_square_matrix_5x5_three_another", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {
      {1, 1, 1, 0, 1}, {1, 1, 1, 1, 0}, {1, 1, 1, 1, 0},
      {0, 1, 1, 1, 0}, {1, 1, 1, 1, 1},
  };
  const auto res = find_max_square(input);
  REQUIRE(res == 9);
}

TEST_CASE("max_square_matrix_5x5_zero", "[max_square]") {
  std::vector<std::vector<std::int8_t>> input = {
      {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
  };
  const auto res = find_max_square(input);
  REQUIRE(res == 0);
}
