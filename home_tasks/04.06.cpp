#include <array>
#include <cmath>

consteval double calculate_e(double epsilon = 1e-15) {
    double e = 1.0;
    double term = 1.0;
    int n = 1;

    while (term > epsilon) {
        term /= n;
        e += term;
        n++;
    }
    
    return e;
}

constexpr std::array<double, 5> epsilons = {
    1e-5, 1e-10, 1e-15, 1e-20, 1e-25
};

consteval double get_e_with_precision(int index) {
    return calculate_e(epsilons[index]);
}

consteval double calculate_e_precise(int max_iterations = 20) {
    double e = 1.0;
    double factorial = 1.0;
    
    for (int i = 1; i <= max_iterations; ++i) {
        factorial *= i;
        e += 1.0 / factorial;
    }
    
    return e;
}

constexpr std::array<int, 4> iteration_counts = {5, 10, 15, 20};

consteval double get_e_with_iterations(int index) {
    return calculate_e_precise(iteration_counts[index]);
}

int main() {
    constexpr double computed_e = calculate_e();
    static_assert(computed_e > 2.71828 && computed_e < 2.71829, 
                  "Basic e computation failed");
    
    static_assert(get_e_with_precision(0) > 2.71828, 
                  "Low precision e computation failed");
    
    static_assert(get_e_with_precision(2) > 2.71828182845904, 
                  "High precision e computation failed");
    
    static_assert(get_e_with_precision(3) > get_e_with_precision(0), 
                  "Precision ordering failed");
    
    static_assert(get_e_with_iterations(3) > get_e_with_iterations(2), 
                  "Iteration progression failed");
    static_assert(get_e_with_iterations(2) > get_e_with_iterations(1), 
                  "Iteration progression failed");
    static_assert(get_e_with_iterations(1) > get_e_with_iterations(0), 
                  "Iteration progression failed");
    
    constexpr double high_precision_e = calculate_e_precise();
    static_assert(high_precision_e > 2.718281828459045 && 
                  high_precision_e < 2.718281828459046, 
                  "High precision e computation failed");
    
    return 0;
}