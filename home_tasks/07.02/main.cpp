#include <iostream>
#include <vector>
#include "sort_algorithms.hpp"

int main() {
  std::cout << "Testing hybrid sort algorithms\n";
  
  // Тест 1: Гибридная сортировка (merge + insertion)
  std::vector<char> vec1 = {'d', 'a', 'c', 'b', 'e'};
  std::cout << "Before hybrid_sort: ";
  for (auto ch : vec1) std::cout << ch << " ";
  std::cout << "\n";
  
  hybrid_sort(vec1);
  
  std::cout << "After hybrid_sort: ";
  for (auto ch : vec1) std::cout << ch << " ";
  std::cout << "\n\n";
  
  // Тест 2: Гибридная быстрая сортировка (quick + insertion)
  std::vector<int> vec2 = {9, 3, 7, 1, 5, 8, 2, 6, 4};
  std::cout << "Before hybrid_quick_sort: ";
  for (auto num : vec2) std::cout << num << " ";
  std::cout << "\n";
  
  hybrid_quick_sort(vec2);
  
  std::cout << "After hybrid_quick_sort: ";
  for (auto num : vec2) std::cout << num << " ";
  std::cout << "\n\n";
  
  // Тест 3: С пользовательским типом
  struct SimpleItem {
    int key;
    int value;
    bool operator<(const SimpleItem& other) const { return key < other.key; }
    bool operator<=(const SimpleItem& other) const { return key <= other.key; }
    bool operator>(const SimpleItem& other) const { return key > other.key; }
  };
  
  std::vector<SimpleItem> vec3 = {{3, 10}, {1, 20}, {2, 30}, {1, 40}};
  std::cout << "Before sorting custom type:\n";
  for (const auto& item : vec3) {
    std::cout << "key=" << item.key << ", value=" << item.value << "\n";
  }
  
  hybrid_sort(vec3);
  
  std::cout << "\nAfter sorting custom type:\n";
  for (const auto& item : vec3) {
    std::cout << "key=" << item.key << ", value=" << item.value << "\n";
  }
  
  return 0;
}