#include <catch2/catch_test_macros.hpp>

#include <basics/numbers.h>

using namespace mse;

TEST_CASE("count_primes_0", "[count_primes]") { REQUIRE(count_primes(0) == 0); }

TEST_CASE("count_primes_1", "[count_primes]") { REQUIRE(count_primes(1) == 0); }

TEST_CASE("count_primes_3", "[count_primes]") { REQUIRE(count_primes(3) == 1); }

TEST_CASE("count_primes_4", "[count_primes]") { REQUIRE(count_primes(4) == 2); }

TEST_CASE("count_primes_7", "[count_primes]") { REQUIRE(count_primes(7) == 3); }

TEST_CASE("count_primes_12", "[count_primes]") {
  REQUIRE(count_primes(12) == 5);
}

TEST_CASE("count_primes_123", "[count_primes]") {
  REQUIRE(count_primes(123) == 30);
}

TEST_CASE("count_primes_1234", "[count_primes]") {
  REQUIRE(count_primes(1234) == 202);
}

TEST_CASE("count_primes_4321", "[count_primes]") {
  REQUIRE(count_primes(4321) == 590);
}

TEST_CASE("count_primes_54321", "[count_primes]") {
  REQUIRE(count_primes(54321) == 5525);
}
