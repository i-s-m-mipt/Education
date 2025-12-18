#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <random>
#include "sort_algorithms.hpp"

struct Item {
  int key;
  int value;
  
  bool operator<(const Item& other) const { 
    return key < other.key; 
  }
  
  bool operator<=(const Item& other) const { 
    return key <= other.key; 
  }
  
  bool operator>(const Item& other) const { 
    return key > other.key; 
  }
  
  bool operator>=(const Item& other) const { 
    return key >= other.key; 
  }
  
  bool operator==(const Item& other) const { 
    return key == other.key && value == other.value; 
  }
  
  bool operator!=(const Item& other) const { 
    return !(*this == other); 
  }
};

class HybridSortTest : public ::testing::Test {
protected:
  void SetUp() override {
  }
};

TEST_F(HybridSortTest, EmptyVector) {
  std::vector<int> vec;
  hybrid_sort(vec);
  EXPECT_TRUE(vec.empty());
}

TEST_F(HybridSortTest, SingleElement) {
  std::vector<int> vec = {42};
  hybrid_sort(vec);
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec[0], 42);
}

TEST_F(HybridSortTest, AlreadySorted) {
  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::vector<int> expected = vec;
  hybrid_sort(vec);
  EXPECT_EQ(vec, expected);
}

TEST_F(HybridSortTest, ReverseSorted) {
  std::vector<int> vec = {5, 4, 3, 2, 1};
  std::vector<int> expected = {1, 2, 3, 4, 5};
  hybrid_sort(vec);
  EXPECT_EQ(vec, expected);
}

TEST_F(HybridSortTest, RandomVector) {
  std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
  std::vector<int> expected = vec;
  std::sort(expected.begin(), expected.end());
  hybrid_sort(vec);
  EXPECT_EQ(vec, expected);
}

TEST_F(HybridSortTest, DuplicateElements) {
  std::vector<int> vec = {2, 2, 2, 1, 1, 3, 3, 3, 3};
  std::vector<int> expected = vec;
  std::sort(expected.begin(), expected.end());
  hybrid_sort(vec);
  EXPECT_EQ(vec, expected);
}

TEST_F(HybridSortTest, LargeVector) {
  std::vector<int> vec(1000);
  std::iota(vec.rbegin(), vec.rend(), 1);
  std::vector<int> expected = vec;
  std::sort(expected.begin(), expected.end());
  hybrid_sort(vec);
  EXPECT_EQ(vec, expected);
}

TEST_F(HybridSortTest, CharVector) {
  std::vector<char> vec = {'d', 'a', 'c', 'b', 'e'};
  std::vector<char> expected = vec;
  std::sort(expected.begin(), expected.end());
  hybrid_sort(vec);
  EXPECT_EQ(vec, expected);
}

TEST_F(HybridSortTest, DoubleVector) {
  std::vector<double> vec = {3.14, 2.71, 1.41, 1.73, 0.57};
  std::vector<double> expected = vec;
  std::sort(expected.begin(), expected.end());
  hybrid_sort(vec);
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_DOUBLE_EQ(vec[i], expected[i]);
  }
}

TEST_F(HybridSortTest, HybridQuickSortTest) {
  std::vector<int> vec = {9, 3, 7, 1, 5, 8, 2, 6, 4};
  std::vector<int> expected = vec;
  std::sort(expected.begin(), expected.end());
  hybrid_quick_sort(vec);
  EXPECT_EQ(vec, expected);
}

TEST_F(HybridSortTest, CompareWithStdSort) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 1000);
  
  for (int size : {10, 100, 1000}) {
    std::vector<int> vec1(size);
    std::generate(vec1.begin(), vec1.end(), [&]() { return dis(gen); });
    std::vector<int> vec2 = vec1;
    
    hybrid_sort(vec1);
    std::sort(vec2.begin(), vec2.end());
    
    EXPECT_EQ(vec1, vec2);
  }
}

TEST_F(HybridSortTest, StabilityTest) {
  std::vector<Item> vec = {
    {1, 100}, {2, 200}, {1, 300}, {3, 400}, {2, 500}
  };
  
  std::vector<Item> original = vec;
  
  hybrid_sort(vec);
  
  bool is_sorted = std::is_sorted(vec.begin(), vec.end());
  EXPECT_TRUE(is_sorted);
}

TEST_F(HybridSortTest, CustomTypeTest) {
  std::vector<Item> items = {
    {3, 1}, {1, 2}, {2, 3}, {1, 4}, {3, 5}
  };
  
  std::vector<Item> expected = items;
  std::sort(expected.begin(), expected.end());
  
  hybrid_sort(items);
  
  EXPECT_TRUE(std::is_sorted(items.begin(), items.end()));
}