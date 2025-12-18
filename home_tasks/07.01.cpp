#include <cmath>
#include <iostream>
#include <optional>
#include <variant>
#include <utility>

using Root = double;
using TwoRoots = std::pair<double, double>;
using InfiniteRoots = std::monostate;
using RootsVariant = std::variant<Root, TwoRoots, InfiniteRoots>;
using Solution = std::optional<RootsVariant>;

Solution solve(double a, double b, double c) {
    const double epsilon = 1e-7;
    
    if (std::abs(a) < epsilon) {
        if (std::abs(b) < epsilon) {
            if (std::abs(c) < epsilon) {
                return Solution{InfiniteRoots{}};
            } else {
                return std::nullopt;
            }
        } else {
            return Solution{Root{-c / b}};
        }
    }
    
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant > epsilon) {
        double sqrt_d = std::sqrt(discriminant);
        double x1 = (-b + sqrt_d) / (2 * a);
        double x2 = (-b - sqrt_d) / (2 * a);
        return Solution{TwoRoots{x1, x2}};
    } 
    else if (std::abs(discriminant) < epsilon) {
        return Solution{Root{-b / (2 * a)}};
    }
    else {
        return std::nullopt;
    }
}

void print_solution(const Solution& sol) {
    if (!sol.has_value()) {
        std::cout << "No solutions (or complex ones)" << std::endl;
        return;
    }
    
    const auto& variant = sol.value();
    
    if (std::holds_alternative<Root>(variant)) {
        std::cout << "One root: " << std::get<Root>(variant) << std::endl;
    } 
    else if (std::holds_alternative<TwoRoots>(variant)) {
        const auto& roots = std::get<TwoRoots>(variant);
        std::cout << "Two roots: " << roots.first << ", " << roots.second << std::endl;
    } 
    else if (std::holds_alternative<InfiniteRoots>(variant)) {
        std::cout << "Infinite number of roots" << std::endl;
    }
}

int main() {
    std::cout << "Enter coefficients of quadratic equation (a b c): ";
    double a = 0, b = 0, c = 0;
    std::cin >> a >> b >> c;
    
    Solution result = solve(a, b, c);
    print_solution(result);
    
    return 0;
}