#include <catch2/catch_test_macros.hpp>

#include <arrays/arrays.h>

using namespace mse;

TEST_CASE("unique_positive_only_element_array", "[unique]") {
  std::vector<std::int32_t> input = {5, 1, 3, 3, 8, 5, 10, 8, 1};
  const auto res = find_unique_element(input);
  REQUIRE(res == 10);
}

TEST_CASE("unique_mixed_element_array", "[unique]") {
  std::vector<std::int32_t> input = {-5, 1, -3, -3, 8, -5, 10, 8, 1};
  const auto res = find_unique_element(input);
  REQUIRE(res == 10);
}

TEST_CASE("unique_repeat_twice_element_array", "[unique]") {
  std::vector<std::int32_t> input = {-5, 8, -3, -3, 8, -5, 10, 8, 8};
  const auto res = find_unique_element(input);
  REQUIRE(res == 10);
}

TEST_CASE("unique_single_element_array", "[unique]") {
  std::vector<std::int32_t> input = {1};
  const auto res = find_unique_element(input);
  REQUIRE(res == 1);
}
