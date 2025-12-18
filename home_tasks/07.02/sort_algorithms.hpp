#ifndef SORT_ALGORITHMS_HPP
#define SORT_ALGORITHMS_HPP

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>
#include <iostream>

template <typename T>
void order(std::vector<T> &vector, int left, int right) {
  for (int i = left + 1; i <= right; ++i) {
    for (int j = i; j > left; --j) {
      if (vector[j - 1] > vector[j]) {
        std::swap(vector[j], vector[j - 1]);
      }
    }
  }
}

template <typename T>
void merge(std::vector<T> &vector_1, std::size_t left, std::size_t right) {
  auto middle = std::midpoint(left, right);
  auto size = right - left;

  std::vector<T> vector_2(size);

  for (std::size_t i = left, j = middle, k = 0; k < size; ++k) {
    if (i < middle &&
        ((j < right && vector_1[i] <= vector_1[j]) || j == right)) {
      vector_2[k] = vector_1[i++];
    } else {
      vector_2[k] = vector_1[j++];
    }
  }

  for (std::size_t i = 0, j = 0; j < size; ++j) {
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
    order(vector, static_cast<int>(left), static_cast<int>(right - 1));
  }
}

template <typename T>
void hybrid_sort(std::vector<T> &vector) { 
  if (!vector.empty()) {
    split(vector, 0, vector.size()); 
  }
}

template <typename T>
int partition(std::vector<T> &arr, int low, int high) {
  T pivot = arr[high];
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
    return;
  }
  if (low < high) {
    int pi = partition(arr, low, high);
    quick_sort(arr, low, pi - 1);
    quick_sort(arr, pi + 1, high);
  }
}

template <typename T>
void hybrid_quick_sort(std::vector<T> &arr) {
  if (!arr.empty()) {
    quick_sort(arr, 0, static_cast<int>(arr.size() - 1));
  }
}

#endif // SORT_ALGORITHMS_HPP