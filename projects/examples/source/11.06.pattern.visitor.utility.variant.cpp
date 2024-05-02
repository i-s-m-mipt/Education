#include <cassert>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <variant>

//  ================================================================================================

class Mobile { public: [[nodiscard]] constexpr int run() const noexcept { return 42; }; };
class Tablet { public: [[nodiscard]] constexpr int run() const noexcept { return 42; }; };
class Laptop { public: [[nodiscard]] constexpr int run() const noexcept { return 43; }; };

//  ================================================================================================

using Computer = std::variant < Mobile, Tablet, Laptop > ;

//  ================================================================================================

class Tester
{
public:

    void operator()(const Mobile & mobile) const
    {
        if (mobile.run() != 42) throw std::runtime_error("Mobile::run error");
    }

    void operator()(const Tablet & tablet) const
    {
        if (tablet.run() != 42) throw std::runtime_error("Tablet::run error");
    }

    void operator()(const Laptop & laptop) const
    {
        if (laptop.run() != 42) throw std::runtime_error("Laptop::run error");
    }

}; // class Tester

//  ================================================================================================

template < typename ... Bases > class Visitor : public Bases ... { public: using Bases::operator()...; };

//  ================================================================================================

int main()
{
    constexpr Computer computer_1 = Mobile();
    constexpr Computer computer_2 = Tablet();
    constexpr Computer computer_3 = Laptop();

    constexpr Visitor < Tester > visitor(Tester{}); // note: just Visitor in MSVC

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

//  ================================================================================================

    assert(std::visit([](auto x) constexpr noexcept { return x; }, std::variant < int > (42)) == 42);

    constexpr auto lambda = [](auto x) constexpr noexcept { return x; };

    Visitor < decltype(lambda) > test(lambda); // note: just Visitor in MSVC

    assert(std::visit(test, std::variant < int > (42)) == 42);

    return 0;
}