#include "arrays.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

namespace mse {

int partition(int arr[], int start, int end) {

  int pivot = arr[start];

  int count = 0;
  for (int i = start + 1; i <= end; i++) {
    if (arr[i] <= pivot)
      count++;
  }

  int pivotIndex = start + count;
  std::swap(arr[pivotIndex], arr[start]);

  int i = start, j = end;

  while (i < pivotIndex && j > pivotIndex) {

    while (arr[i] <= pivot) {
      i++;
    }

    while (arr[j] > pivot) {
      j--;
    }

    if (i < pivotIndex && j > pivotIndex) {
      std::swap(arr[i++], arr[j--]);
    }
  }

  return pivotIndex;
}

void quickSort(int arr[], int start, int end) {

  if (start >= end)
    return;

  int p = partition(arr, start, end);

  quickSort(arr, start, p - 1);

  quickSort(arr, p + 1, end);
}

void sort(std::vector<std::int32_t> &elements) {
  int n = static_cast<int>(elements.size());
  int *arr = &elements[0]; // to get a pointer on the first element
  quickSort(arr, 0, n - 1);
}

std::int32_t trace(const std::vector<std::vector<std::int32_t>> &matrix) {
  int max_of = std::max(static_cast<int>(matrix.size()),
                        static_cast<int>(matrix.size()));
  int sum = 0;
  for (int i = 0; i < max_of; ++i) {
    sum += matrix[i][i];
  }
  return sum;
};

std::int32_t find_unique_element(const std::vector<std::int32_t> &elements1) {
  std::vector<std::int32_t> elements = elements1;
  std::sort(elements.begin(), elements.end());
  int imax = std::numeric_limits<int>::max();
  elements.push_back(imax);

  for (int i = 1; i < static_cast<int>(elements.size()); i = i + 2) {
    if (elements[i] != elements[i - 1]) {
      return elements[i - 1];
    }
  }
  return -1;
};

int fill_dp(const std::vector<std::vector<std::int8_t>> &matrix) {
  size_t rows = matrix.size();
  size_t cols = matrix[0].size();

  // create dp
  std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, 0));

  // fill the matrix
  // max submatrix of only 1's
  // prefill
  int max = 0;

  for (size_t j = 0; j < cols; ++j) {
    if (matrix[0][j] == 1) {
      dp[0][j] = 1;
      max = 1;
    } else {
      dp[0][j] = 0;
    }
  };

  for (size_t i = 0; i < rows; ++i) {
    if (matrix[i][0] == 1) {
      dp[i][0] = 1;
      max = 1;
    } else {
      dp[i][0] = 0;
    }
  }

  // fill dp
  for (size_t i = 1; i < rows; ++i) {
    for (size_t j = 1; j < cols; ++j) {
      if (matrix[i][j] == 1) {
        dp[i][j] = 1 + std::min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
        max = std::max({dp[i][j], max});
      }
    }
  }

  return max;
}

size_t find_max_square(const std::vector<std::vector<std::int8_t>> &matrix) {
  if (!matrix.size()) {
    return 0;
  }
  int ans = fill_dp(matrix);
  return static_cast<size_t>(ans * ans);
};

} // namespace mse
