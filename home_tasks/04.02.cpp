#include <iostream>
#include <type_traits>

template<typename T>
void processDouble(const T& value, double& maxVal, double& minVal, double& sum, int& count) {
    if constexpr (std::is_same_v<T, double>) {
        if (count == 0) {
            maxVal = value;
            minVal = value;
        } else {
            if (value > maxVal) maxVal = value;
            if (value < minVal) minVal = value;
        }
        sum += value;
        count++;
    }
}

template<typename... Args>
void processPack(double& maxVal, double& minVal, double& sum, int& count, Args... args) {
    (processDouble(args, maxVal, minVal, sum, count), ...);
}

template<typename... Args>
void calculateStats(Args... args) {
    double maxVal = 0.0;
    double minVal = 0.0;
    double sum = 0.0;
    int count = 0;
    
    processPack(maxVal, minVal, sum, count, args...);
    
    if (count > 0) {
        double average = sum / count;
        std::cout << "Максимальное значение: " << maxVal << std::endl;
        std::cout << "Минимальное значение: " << minVal << std::endl;
        std::cout << "Сумма: " << sum << std::endl;
        std::cout << "Количество double: " << count << std::endl;
        std::cout << "Среднее арифметическое: " << average << std::endl;
    } else {
        std::cout << "Нет аргументов типа double для обработки" << std::endl;
    }
}

int main() {
    std::cout << "=== Пример 1: Только double ===" << std::endl;
    calculateStats(1.5, 2.7, 3.1, 4.8, 0.5);
    
    std::cout << "\n=== Пример 2: Смешанные типы ===" << std::endl;
    calculateStats(1, 2.5, "hello", 3.7, 'A', 4.2, 5.0f);
    
    std::cout << "\n=== Пример 3: Без double ===" << std::endl;
    calculateStats(1, "text", 'X', true);
    
    return 0;
}