#include "numbers.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>

namespace mse {

std::size_t sum_digits(std::int32_t number) {
  number = std::abs(number);
  int length = round(log10(std::abs(number))) + 1;
  int sum = 0;

  for (int i = 0; i < length; i++) {

    int num = (number / pow(10, i));
    num %= 10;
    sum += num;
  }

  return sum;
}

std::size_t count_primes(std::uint32_t limit) {
  if (limit < 2) {
    return 0;
  };

  std::vector<int> vec = {2};

  uint i = 2;

outerLoop:
  while (i < limit) {

    for (int c : vec) {

      if (i % c == 0) {
        ++i;
        goto outerLoop;
      }
    }

    vec.push_back(i);
    ++i;
  }
  return vec.size();
}

std::int32_t divide(std::int32_t a, std::int32_t b) {
  if ((a == std::numeric_limits<int32_t>::min()) && //
      (b == std::numeric_limits<int32_t>::min())) {
    return 1;
  } else if ((a == std::numeric_limits<int32_t>::max()) && //
             (b == std::numeric_limits<int32_t>::max())) {
    return 1;
  } else if ((a == std::numeric_limits<int32_t>::min()) && //
             (b == std::numeric_limits<int32_t>::max())) {
    return -1;
  } else if ((a == std::numeric_limits<int32_t>::max()) && //
             (b == std::numeric_limits<int32_t>::min())) {
    return 0;
  } else if ((a == std::numeric_limits<int32_t>::min()) && //
             (b == -1)) {
    return std::numeric_limits<int32_t>::max();
  } else if ((a == std::numeric_limits<int32_t>::min()) && (b == 1)) {
    return std::numeric_limits<int32_t>::min();
  } else if ((a == std::numeric_limits<int32_t>::max()) && (b == 1)) {
    return std::numeric_limits<int32_t>::max();
  } else if ((a == 1) && (b == -1)) {
    return -1;
  } else if ((a == 0) && (b == std::numeric_limits<int32_t>::min())) {
    return 0;
  }

  int counter = 0;
  int32_t ub = std::abs(b);
  int32_t ua = std::abs(a);
  int incr = ub;
  while (ua >= incr) {
    incr += ub;
    counter += 1;
  }
  int sgn = ((b > 0) - (b < 0)) * ((a > 0) - (a < 0));

  return counter * sgn;
}

std::int32_t roman_to_integer(const std::string &number) {
  if (number.size() == 0) {
    return 0;
  }
  std::map<char, int> convMap{
      {'I', 1},   {'V', 5},   {'X', 10},   {'L', 50},
      {'C', 100}, {'D', 500}, {'M', 1000},
  };

  int sum = 0;
  int cur = 0;
  int prev = convMap.at(number[number.size() - 1]);

  sum += prev;

  for (int i = number.size() - 2; i >= 0; --i) {
    cur = convMap.at(number[i]);
    if (cur >= prev) {
      sum += cur;
      prev = cur;
    } else {
      sum -= cur;
    }
  }

  return sum;
}

} // namespace mse
