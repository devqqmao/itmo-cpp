#include <catch2/catch_test_macros.hpp>

#include <arrays/arrays.h>

using namespace mse;

TEST_CASE("sort_empty_array", "[sort]") {
  std::vector<std::int32_t> input;
  sort(input);
  std::vector<std::int32_t> expected;
  REQUIRE(input == expected);
}

TEST_CASE("sort_single_element_array", "[sort]") {
  std::vector<std::int32_t> input = {1};
  sort(input);
  std::vector<std::int32_t> expected = {1};
  REQUIRE(input == expected);
}

TEST_CASE("sort_positive_only_element_array", "[sort]") {
  std::vector<std::int32_t> input = {1, 3, 5, 10, 8};
  sort(input);
  std::vector<std::int32_t> expected = {1, 3, 5, 8, 10};
  REQUIRE(input == expected);
}

TEST_CASE("sort_negative_only_element_array", "[sort]") {
  std::vector<std::int32_t> input = {-1, -3, -5, -10, -8};
  sort(input);
  std::vector<std::int32_t> expected = {-10, -8, -5, -3, -1};
  REQUIRE(input == expected);
}

TEST_CASE("sort_mixed_element_array", "[sort]") {
  std::vector<std::int32_t> input = {1, 3, -5, 10, -8};
  sort(input);
  std::vector<std::int32_t> expected = {-8, -5, 1, 3, 10};
  REQUIRE(input == expected);
}

TEST_CASE("sort_duplicate_element_array", "[sort]") {
  std::vector<std::int32_t> input = {1, 2, 3, -5, -5, 10, -8, 2};
  sort(input);
  std::vector<std::int32_t> expected = {-8, -5, -5, 1, 2, 2, 3, 10};
  REQUIRE(input == expected);
}

TEST_CASE("sort_sorted_element_array", "[sort]") {
  std::vector<std::int32_t> input = {1, 2, 3, 5};
  sort(input);
  std::vector<std::int32_t> expected = {1, 2, 3, 5};
  REQUIRE(input == expected);
}

TEST_CASE("sort_inv_sorted_element_array", "[sort]") {
  std::vector<std::int32_t> input = {5, 4, 3, 2};
  sort(input);
  std::vector<std::int32_t> expected = {2, 3, 4, 5};
  REQUIRE(input == expected);
}
