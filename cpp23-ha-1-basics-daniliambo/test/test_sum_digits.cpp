#include <catch2/catch_test_macros.hpp>

#include <basics/numbers.h>

using namespace mse;

TEST_CASE("sum_digits_zero", "[sum_digits]") { REQUIRE(sum_digits(0) == 0); }

TEST_CASE("sum_digits_one", "[sum_digits]") { REQUIRE(sum_digits(1) == 1); }

TEST_CASE("sum_digits_one_another", "[sum_digits]") {
  REQUIRE(sum_digits(2) == 2);
}

TEST_CASE("sum_digits_one_negative", "[sum_digits]") {
  REQUIRE(sum_digits(-3) == 3);
}

TEST_CASE("sum_digits_two", "[sum_digits]") { REQUIRE(sum_digits(25) == 7); }

TEST_CASE("sum_digits_two_another", "[sum_digits]") {
  REQUIRE(sum_digits(72) == 9);
}

TEST_CASE("sum_digits_two_negative", "[sum_digits]") {
  REQUIRE(sum_digits(-66) == 12);
}

TEST_CASE("sum_digits_five", "[sum_digits]") {
  REQUIRE(sum_digits(12345) == 15);
}

TEST_CASE("sum_digits_five_negative", "[sum_digits]") {
  REQUIRE(sum_digits(-12345) == 15);
}

TEST_CASE("sum_digits_five_with_zeros", "[sum_digits]") {
  REQUIRE(sum_digits(-12005) == 8);
}

TEST_CASE("sum_digits_repeats", "[sum_digits]") {
  REQUIRE(sum_digits(1111) == 4);
}

TEST_CASE("sum_digits_zeros", "[sum_digits]") {
  REQUIRE(sum_digits(0000) == 0);
}
