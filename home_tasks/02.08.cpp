#include <iostream>
#include <vector>

struct KattalatzInfo {
  unsigned long long num;
  size_t len;
};

int main() {
  const unsigned long long int N_limit = 100;
  std::vector<KattalatzInfo> Kattalanz_nums;
  for (unsigned long long ni = 1; ni <= N_limit; ++ni) {
    size_t tmp_len = 0;
    unsigned long long current = ni; // Используем временную переменную
    while (current != 1) {
      if (current % 2 != 0) {
        current = 3 * current + 1;
      } else {
        current /= 2;
      }
      tmp_len++;
      // std::cout << current << " ";
    }
    KattalatzInfo kat_data;
    kat_data.num = ni;
    kat_data.len = tmp_len;
    Kattalanz_nums.push_back(kat_data);
  }

  size_t kat_max = 0;
  unsigned long long kat_num = 0;
  for (unsigned long long i = 0; i < N_limit; ++i) {
    if (Kattalanz_nums[i].len > kat_max) {
      kat_max = Kattalanz_nums[i].len;
      kat_num = Kattalanz_nums[i].num;
    }
  }

  std::cout << "MAX LEN: " << kat_max << "\n";
  std::cout << "INITIAL KATTALANZ NUM: " << kat_num << "\n";
  std::cout << "\n";

  return 0;
}
