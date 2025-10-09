#include <cmath>
#include <iostream>
#include <numbers>

const double Pi = std::numbers::pi;

class Triangle {
private:
  double a = 0, b = 0, c = 0;

public:
  Triangle(const double a_, const double b_, const double c_)
      : a(a_), b(b_), c(c_) {}

  double PerimetrCalc() { return a + b + c; }

  double SquareCalc() {
    auto p = PerimetrCalc() / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
  }
};

class Square {
private:
  double a = 0;

public:
  Square(const double a_) : a(a_) {};

  double PerimetrCalc() { return 4 * a; }

  double SquareCalc() { return a * a; }
};

class Circle {
private:
  double r = 0;

public:
  Circle(const double r_) : r(r_) {};

  double PerimetrCalc() { return 2 * Pi * r; }

  double SquareCalc() { return Pi * r * r; }
};

int main() {
  // TESTS
  std::cout << "Triangle:\n";
  Triangle a(3, 4, 5);
  std::cout << "Perimeter: " << a.PerimetrCalc() << "\n";
  std::cout << "Square: " << a.SquareCalc() << "\n";
  std::cout << "\n";

  std::cout << "Square:\n";
  Square b(2);
  std::cout << "Perimeter: " << b.PerimetrCalc() << "\n";
  std::cout << "Square: " << b.SquareCalc() << "\n";
  std::cout << "\n";

  std::cout << "Circle:\n";
  Circle c(10);
  std::cout << "Perimeter: " << c.PerimetrCalc() << "\n";
  std::cout << "Square: " << c.SquareCalc() << "\n";

  return 0;
}