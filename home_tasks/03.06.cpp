#include <cmath>
#include <iostream>
#include <numbers>
#include <vector>

const double Pi = std::numbers::pi;

class Shape {
public:
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual ~Shape() = default;
};

class Triangle: public Shape {
private:
    double a = 0, b = 0, c = 0;

public:
    Triangle(const double a_, const double b_, const double c_)
        : a(a_), b(b_), c(c_) {}

    double perimeter() const override final { return a + b + c; }

    double area() const override final {
        auto p = perimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
  }
};

class Square: public Shape {
private:
    double a = 0;

public:
    Square(const double a_) : a(a_) {};

    double perimeter() const override final { return 4 * a; }

    double area() const override final { return a * a; }
};

class Circle: public Shape {
private:
    double r = 0;

public:
    Circle(const double r_) : r(r_) {};

    double perimeter() const override final { return 2 * Pi * r; }

    double area() const override final { return Pi * r * r; }
};

int main() {
    std::vector<Shape*> shapes;
    shapes.push_back(new Triangle(3, 4, 5));
    shapes.push_back(new Square(5));
    shapes.push_back(new Circle(3));
    shapes.push_back(new Triangle(5, 12, 13));
    shapes.push_back(new Square(2.5));
    shapes.push_back(new Circle(1));

    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << "Shape " << i + 1 << ":\n";
        std::cout << "  Perimeter: " << shapes[i]->perimeter() << "\n";
        std::cout << "  Area: " << shapes[i]->area() << "\n";
        std::cout << "  Type: ";
        
        if (dynamic_cast<Triangle*>(shapes[i])) {
            std::cout << "Triangle";
        } else if (dynamic_cast<Square*>(shapes[i])) {
            std::cout << "Square";
        } else if (dynamic_cast<Circle*>(shapes[i])) {
            std::cout << "Circle";
        }
        std::cout << "\n\n";
    }

    for (size_t i = 0; i < shapes.size(); ++i) {
        delete shapes[i];
    }
  
  return 0;
}