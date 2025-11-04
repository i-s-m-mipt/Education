#include <iostream>
#include <vector>

template<typename... Args>
void addAllToVector(std::vector<int>& container, Args... args) {
    static_assert((std::is_same_v<Args, int> && ...), "All arguments must be of type int");
    (container.push_back(args), ...);
}

int main() {
    std::vector<int> numbers;
    
    addAllToVector(numbers, 1, 2, 3, 4, 5);
    
    addAllToVector(numbers, 42);
    
    addAllToVector(numbers, -1, 0, -10, 100);

    std::cout << "Содержимое вектора: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Размер вектора: " << numbers.size() << std::endl;
    
    return 0;
}