#include <cmath>
#include <iostream>
#include <stdexcept>

int main() {
  std::cout << "Enter coeffs Quadratic equation: " << std::endl;
  double a = 0, b = 0, c = 0;
  const double epsilon = 1e-3;
  std::cin >> a >> b >> c;

  if (std::abs(a) < epsilon) {
    if (std::abs(b) < epsilon) {
      if (std::abs(c) < epsilon) {
        std::cout << "Not valid coeffs: Inifinity solutions" << std::endl;
      } else {
        std::cout << "Not valid coeffs: zero solutions" << std::endl;
      }
    } else
      std::cout << "1 equation: " << -c / b;
  }

  else {
    double D = b * b - 4 * a * c;
    if (D == 0) {
      std::cout << "2 equal equations: " << -b / (2 * a) << std::endl;
    } else if (D > epsilon) {
      double x1 = (-b + sqrt(D)) / (2 * a);
      double x2 = (-b - sqrt(D)) / (2 * a);

      std::cout << "Equations: " << x1 << " " << x2 << std::endl;
    }

    else {
      double Re = -b / (2 * a);
      double Im_1 = sqrt(std::abs(D)) / (2 * a);
      double Im_2 = -sqrt(std::abs(D)) / (2 * a);

      std::cout << "Equations are complex: " << std::endl;
      std::cout << Re << " " << Im_1 << std::endl;
      std::cout << Re << " " << Im_2;
      std::cout << std::endl;
    }
  }
  return 0;
}