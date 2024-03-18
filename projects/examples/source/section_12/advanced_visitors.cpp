#include <cassert>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <variant>

class Mobile { public: [[nodiscard]] int run() const noexcept { return 0; }; };
class Tablet { public: [[nodiscard]] int run() const noexcept { return 0; }; };
class Laptop { public: [[nodiscard]] int run() const noexcept { return 1; }; };

using Computer = std::variant < Mobile, Tablet, Laptop > ;

class Tester
{
public:

    void operator()(const Mobile & mobile) const
    {
        if (mobile.run() != 0) throw std::runtime_error("invalid Mobile::run");
    }

    void operator()(const Tablet & tablet) const
    {
        if (tablet.run() != 0) throw std::runtime_error("invalid Tablet::run");
    }

    void operator()(const Laptop & laptop) const
    {
        if (laptop.run() != 0) throw std::runtime_error("invalid Laptop::run");
    }

}; // class Tester

template < typename ... Bases > struct Visitor : Bases... { using Bases::operator()...; };

int main()
{
    Computer computer_1 = Mobile();
    Computer computer_2 = Tablet();
    Computer computer_3 = Laptop();

    Visitor < Tester > visitor(Tester{}); // note: just Visitor in MSVC

    try
    {
        std::visit(visitor, computer_1);
        std::visit(visitor, computer_2);
        std::visit(visitor, computer_3);
    }
    catch (const std::exception & exception)
    {
        std::cerr << "Tester error: " << exception.what() << '\n';
    }

    assert(std::visit([](auto && x){ return x; }, std::variant < int > (42)) == 42);

    auto lambda = [](auto && x){ return x; };

    Visitor < decltype(lambda) > test(lambda); // note: just Visitor in MSVC

    assert(std::visit(test, std::variant < int > (42)) == 42);

    return 0;
}