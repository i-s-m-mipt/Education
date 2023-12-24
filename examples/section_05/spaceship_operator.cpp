#include <cassert>
#include <compare>
#include <iostream>

class Apple
{
public:

    explicit Apple(double weight) : m_weight(weight) {}

    auto operator<=>(const Apple & rhs) const // note: auto -> std::partial_ordering
    {
        return (m_weight <=> rhs.m_weight);
    }

private:

    double m_weight;

}; // class Apple 

class Human
{
public:

    explicit Human(double weight, double height) : m_weight(weight), m_height(height) {}

    auto operator<=>(const Human & rhs) const = default; // note: auto -> std::strong_ordering

private:

    double m_weight;
    double m_height;

}; // class Human

int main()
{
    auto x = 4;
    auto y = 7;

    assert((x <=> y) < 0); // note: rewrited expression x < y

    Apple apple_1(200.0);
    Apple apple_2(100.0);

    assert(apple_1 <  apple_2);
    assert(apple_1 >  apple_2);
    assert(apple_1 <= apple_2);
    assert(apple_1 >= apple_2);
//  assert(apple_1 == apple_2); // note: partial ordering
//  assert(apple_1 != apple_2); // note: partial ordering

    Human human_1(85.0, 185.0);
    Human human_2(80.0, 180.0);

    assert(human_1 <  human_2);
    assert(human_1 >  human_2);
    assert(human_1 <= human_2);
    assert(human_1 >= human_2);
    assert(human_1 == human_2);
    assert(human_1 != human_2);

    return 0;
}