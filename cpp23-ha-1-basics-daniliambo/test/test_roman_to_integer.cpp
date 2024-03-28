#include <catch2/catch_test_macros.hpp>

#include <basics/numbers.h>

using namespace mse;

TEST_CASE("roman_to_int_empty", "[roman_to_int]") {
  const auto res = roman_to_integer("");
  REQUIRE(res == 0);
}

TEST_CASE("roman_to_int_I", "[roman_to_int]") {
  const auto res = roman_to_integer("I");
  REQUIRE(res == 1);
}

TEST_CASE("roman_to_int_V", "[roman_to_int]") {
  const auto res = roman_to_integer("V");
  REQUIRE(res == 5);
}

TEST_CASE("roman_to_int_X", "[roman_to_int]") {
  const auto res = roman_to_integer("X");
  REQUIRE(res == 10);
}

TEST_CASE("roman_to_int_L", "[roman_to_int]") {
  const auto res = roman_to_integer("L");
  REQUIRE(res == 50);
}

TEST_CASE("roman_to_int_C", "[roman_to_int]") {
  const auto res = roman_to_integer("C");
  REQUIRE(res == 100);
}

TEST_CASE("roman_to_int_D", "[roman_to_int]") {
  const auto res = roman_to_integer("D");
  REQUIRE(res == 500);
}

TEST_CASE("roman_to_int_M", "[roman_to_int]") {
  const auto res = roman_to_integer("M");
  REQUIRE(res == 1000);
}

TEST_CASE("roman_to_int_MD", "[roman_to_int]") {
  const auto res = roman_to_integer("MD");
  REQUIRE(res == 1500);
}

TEST_CASE("roman_to_int_DC", "[roman_to_int]") {
  const auto res = roman_to_integer("DC");
  REQUIRE(res == 600);
}

TEST_CASE("roman_to_int_MI", "[roman_to_int]") {
  const auto res = roman_to_integer("MI");
  REQUIRE(res == 1001);
}

TEST_CASE("roman_to_int_MDCLXVI", "[roman_to_int]") {
  const auto res = roman_to_integer("MDCLXVI");
  REQUIRE(res == 1666);
}

TEST_CASE("roman_to_int_MDCLXI", "[roman_to_int]") {
  const auto res = roman_to_integer("MDCLXI");
  REQUIRE(res == 1661);
}

TEST_CASE("roman_to_int_MDCLI", "[roman_to_int]") {
  const auto res = roman_to_integer("MDCLI");
  REQUIRE(res == 1651);
}

TEST_CASE("roman_to_int_XVII", "[roman_to_int]") {
  const auto res = roman_to_integer("XVII");
  REQUIRE(res == 17);
}

TEST_CASE("roman_to_int_MCMXCIV", "[roman_to_int]") {
  const auto res = roman_to_integer("MCMXCIV");
  REQUIRE(res == 1994);
}

TEST_CASE("roman_to_int_IX", "[roman_to_int]") {
  const auto res = roman_to_integer("IX");
  REQUIRE(res == 9);
}

TEST_CASE("roman_to_int_CIV", "[roman_to_int]") {
  const auto res = roman_to_integer("CIV");
  REQUIRE(res == 104);
}

TEST_CASE("roman_to_int_XL", "[roman_to_int]") {
  const auto res = roman_to_integer("XL");
  REQUIRE(res == 40);
}

TEST_CASE("roman_to_int_XC", "[roman_to_int]") {
  const auto res = roman_to_integer("XC");
  REQUIRE(res == 90);
}

TEST_CASE("roman_to_int_CD", "[roman_to_int]") {
  const auto res = roman_to_integer("CD");
  REQUIRE(res == 400);
}

TEST_CASE("roman_to_int_CM", "[roman_to_int]") {
  const auto res = roman_to_integer("CM");
  REQUIRE(res == 900);
}
