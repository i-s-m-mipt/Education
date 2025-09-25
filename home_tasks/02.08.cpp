#include <iostream>
#include <vector>


int main() {
  const unsigned long long int N_limit = 100;
  std::vector < unsigned long long > cash(N_limit);
  for (unsigned long long ni = 1; ni <= N_limit; ++ni) {
    size_t tmp_len = 0;
    unsigned long long current = ni;
    while (current != 1) {
      if (cash[current - 1] != 0) {
        tmp_len += cash[current - 1];
        break;
      }

      if (current % 2 != 0) {
        current = 3 * current + 1;
      } else {
        current /= 2;
      }
      tmp_len++;
    }
    cash[ni - 1] = tmp_len;
  }

  size_t kat_max = 0;
  unsigned long long kat_num = 0;
  for (unsigned long long i = 0; i < N_limit; ++i) {
    if (cash[i] > kat_max) {
      kat_max = cash[i];
      kat_num = i + 1;
    }
  }

  std::cout << "MAX LEN: " << kat_max << "\n";
  std::cout << "INITIAL KATTALANZ NUM: " << kat_num << "\n";
  std::cout << "\n";

  return 0;
}
