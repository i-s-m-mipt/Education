#include <compare>
#include <iostream>

class Apple
{
public:

    constexpr explicit Apple(double weight) : m_weight(weight) {}

    [[nodiscard]] constexpr auto operator<=>(const Apple & rhs) const // note: auto -> std::partial_ordering
    {
        return (m_weight <=> rhs.m_weight);
    }

private:

    double m_weight;

}; // class Apple 

class Human
{
public:

    constexpr explicit Human(double weight, double height) : m_weight(weight), m_height(height) {}

    [[nodiscard]] constexpr auto operator<=>(const Human & rhs) const = default; // note: auto -> std::strong_ordering

private:

    double m_weight;
    double m_height;

}; // class Human

int main()
{
    constexpr auto x = 4;
    constexpr auto y = 7;

    if ((x <=> y) < 0) std::cout << "x < y" << std::endl << std::endl; // note: same as x < y

    constexpr Apple apple_1(200.0);
    constexpr Apple apple_2(100.0);

    std::cout << "apple_1 <  apple_2: " << (apple_1 <  apple_2) << std::endl;
    std::cout << "apple_1 >  apple_2: " << (apple_1 >  apple_2) << std::endl;
    std::cout << "apple_1 <= apple_2: " << (apple_1 <= apple_2) << std::endl;
    std::cout << "apple_1 >= apple_2: " << (apple_1 >= apple_2) << std::endl;
//  std::cout << "apple_1 == apple_2: " << (apple_1 == apple_2) << std::endl; // note: partial ordering
//  std::cout << "apple_1 != apple_2: " << (apple_1 != apple_2) << std::endl; // note: partial ordering

    std::cout << std::endl;

    constexpr Human human_1(85.0, 185.0);
    constexpr Human human_2(80.0, 180.0);

    std::cout << "human_1 <  human_2: " << (human_1 <  human_2) << std::endl;
    std::cout << "human_1 >  human_2: " << (human_1 >  human_2) << std::endl;
    std::cout << "human_1 <= human_2: " << (human_1 <= human_2) << std::endl;
    std::cout << "human_1 >= human_2: " << (human_1 >= human_2) << std::endl;
    std::cout << "human_1 == human_2: " << (human_1 == human_2) << std::endl;
    std::cout << "human_1 != human_2: " << (human_1 != human_2) << std::endl;

    return 0;
}