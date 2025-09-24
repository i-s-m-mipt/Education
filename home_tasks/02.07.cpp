#include <iostream>
#include <cmath>

int main() {
  size_t size;
  std::cout << "Dynamic massiv size: ";
  std::cin >> size;

  double *dyn_arr = new double[size];

  for (size_t i = 0; i < size; ++i) {
    double tmp;
    std::cin >> tmp;
    dyn_arr[i] = tmp;
  }

  double min_el = 1e6;
  double max_el = -1e6;
  double mean = 0;
  double std = 0;

  for (size_t ii = 0; ii < size; ++ii) {
    if (dyn_arr[ii] <= min_el)
      min_el = dyn_arr[ii];
    if (dyn_arr[ii] >= max_el)
      max_el = dyn_arr[ii];
    mean += dyn_arr[ii];
  }

  mean /= (size);

  for (size_t ii = 0; ii < size; ++ii) {
    std += dyn_arr[ii] * dyn_arr[ii];
  }

  delete[] dyn_arr;

  std /= (size);
  std -= mean * mean;
  std = sqrt(std);

  std::cout << "Statistics: " << std::endl;
  std::cout << min_el << std::endl;
  std::cout << max_el << std::endl;
  std::cout << mean << std::endl;
  std::cout << std << std::endl;

  return 0;
}