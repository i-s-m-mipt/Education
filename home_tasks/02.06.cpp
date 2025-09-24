#include <cmath>
#include <iostream>

int main() {
  const int N = 20;
  double stat_ar[N];

  double number;
  unsigned int i = 0;
  while (std::cin >> number) {
    stat_ar[i] = number;

    if (std::cin.peek() == '\n') {
      break;
    }
    i++;
  }

  double min_el = 1e6;
  double max_el = -1e6;
  double mean = 0;
  double std = 0;

  for (size_t ii = 0; ii <= i; ++ii) {
    if (stat_ar[ii] <= min_el)
      min_el = stat_ar[ii];
    if (stat_ar[ii] >= max_el)
      max_el = stat_ar[ii];
    mean += stat_ar[ii];
  }

  mean /= (i + 1);

  for (size_t ii = 0; ii <= i; ++ii) {
    std += stat_ar[ii] * stat_ar[ii];
  }

  std /= (i + 1);
  std -= mean * mean;
  std = sqrt(std);

  std::cout << "Statistics: " << std::endl;
  std::cout << min_el << std::endl;
  std::cout << max_el << std::endl;
  std::cout << mean << std::endl;
  std::cout << std << std::endl;

  return 0;
}