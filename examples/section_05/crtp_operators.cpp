#include <iostream>

template < typename T > class Relational {};

template < typename T >
auto operator< (const Relational < T > & lhs, const Relational < T > & rhs)
{
    return (static_cast < const T & > (lhs) < static_cast < const T & > (rhs));
}

template < typename T >
auto operator> (const Relational < T > & lhs, const Relational < T > & rhs)
{
    return (rhs < lhs);
}

template < typename T >
auto operator<=(const Relational < T > & lhs, const Relational < T > & rhs)
{
    return !(lhs > rhs);
}

template < typename T >
auto operator>=(const Relational < T > & lhs, const Relational < T > & rhs)
{
    return !(lhs < rhs);
}

template < typename T >
auto operator==(const Relational < T > & lhs, const Relational < T > & rhs)
{
    return (!(lhs < rhs) && !(rhs < lhs));
}

template < typename T >
auto operator!=(const Relational < T > & lhs, const Relational < T > & rhs)
{
    return !(lhs == rhs);
}

class Apple : public Relational < Apple > // note: see Boost.Operators
{
public:

    explicit Apple(double weight) : m_weight(weight) {}

public:

    auto weight() const { return m_weight; }

private:

    double m_weight;

}; // class Apple : public Relational < Apple > 

auto operator<(const Apple & lhs, const Apple & rhs) 
{
    return (lhs.weight() < rhs.weight());
}

class Human : public Relational < Human > // note: see Boost.Operators
{
public:

    explicit Human(double height) : m_height(height) {}

public:

    auto height() const { return m_height; }

private:

    double m_height;

}; // class Human : public Relational < Human > 

auto operator<(const Human & lhs, const Human & rhs)
{
    return (lhs.height() < rhs.height());
}

int main() 
{
    Apple apple_1(100.0);
    Apple apple_2(200.0);

    std::cout << (apple_1 <  apple_2) << std::endl;
    std::cout << (apple_1 >  apple_2) << std::endl;
    std::cout << (apple_1 <= apple_2) << std::endl;
    std::cout << (apple_1 >= apple_2) << std::endl;
    std::cout << (apple_1 == apple_2) << std::endl;
    std::cout << (apple_1 != apple_2) << std::endl;
    
    Human human_1(180.0);
    Human human_2(185.0);

    std::cout << (human_1 <  human_2) << std::endl;
    std::cout << (human_1 >  human_2) << std::endl;
    std::cout << (human_1 <= human_2) << std::endl;
    std::cout << (human_1 >= human_2) << std::endl;
    std::cout << (human_1 == human_2) << std::endl;
    std::cout << (human_1 != human_2) << std::endl;
    
    return 0;
}