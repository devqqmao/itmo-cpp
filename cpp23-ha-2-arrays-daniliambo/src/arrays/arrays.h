#pragma once

#include <numeric>
#include <string>
#include <vector>

namespace mse {

void sort(std::vector<std::int32_t> &elements);

[[nodiscard]] std::int32_t
trace(const std::vector<std::vector<std::int32_t>> &matrix);

[[nodiscard]] std::int32_t
find_unique_element(const std::vector<std::int32_t> &elements);

[[nodiscard]] std::size_t
find_max_square(const std::vector<std::vector<std::int8_t>> &matrix);

} // namespace mse
