#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

template <typename T>
void order(std::vector<T> &vector, int left, int right) {
  for (int i = left + 1; i < right; ++i) {
    for (int j = i; j > left; --j) {
      if (vector[j - 1] > vector[j]) {
        std::swap(vector[j], vector[j - 1]);
      }
    }
  }
}

template <typename T>
void merge(std::vector<T> &vector_1, std::size_t left, std::size_t right) {
  auto middle = std::midpoint(left, right), size = right - left;

  std::vector<T> vector_2(size, 0);

  for (auto i = left, j = middle, k = 0uz; k < size; ++k) {
    if (i < middle &&
        ((j < right && vector_1[i] <= vector_1[j]) || j == right)) {
      vector_2[k] = vector_1[i++];
    } else {
      vector_2[k] = vector_1[j++];
    }
  }

  for (auto i = 0uz, j = 0uz; j < size; ++j) {
    vector_1[left + i++] = vector_2[j];
  }
}

template <typename T>
void split(std::vector<T> &vector, std::size_t left, std::size_t right) {
  if (right - left > 16) {
    auto middle = std::midpoint(left, right);

    split(vector, left, middle);

    split(vector, middle, right);

    merge(vector, left, right);
  } else {
    order(vector, left, right);
  }
}

template <typename T>
void sort(std::vector<T> &vector) { split(vector, 0, std::size(vector)); }

template <typename T>
int partition(std::vector<T> &arr, int low, int high) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (arr[j] <= pivot) {
      i++;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[high]);
  return i + 1;
}

template <typename T>
void quick_sort(std::vector<T> &arr, int low, int high) {
  if (high - low < 16) {
    order(arr, low, high);
  }
  if (low < high) {
    int pi = partition(arr, low, high);
    quick_sort(arr, low, pi - 1);
    quick_sort(arr, pi + 1, high);
  }
}

int main() {
  // --------------------------TESTS-------------------------- //
  int size = 5;

  std::vector<char> vector = {'d', 'a', 'c', 'b', 'e'};
  
  quick_sort(vector, 0, size - 1);
  for (auto num : vector) {
    std::cout << num << "\n";
  }

  return 0;
}