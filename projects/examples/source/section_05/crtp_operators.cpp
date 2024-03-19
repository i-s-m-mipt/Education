#include <iostream>

#include <boost/operators.hpp>

template < typename T > class Relational // note: Barton-Nackman trick
{
public:

    [[nodiscard]] friend inline constexpr bool operator> (const T & lhs, const T & rhs) { return  (rhs < lhs); }
    [[nodiscard]] friend inline constexpr bool operator<=(const T & lhs, const T & rhs) { return !(lhs > rhs); }
    [[nodiscard]] friend inline constexpr bool operator>=(const T & lhs, const T & rhs) { return !(lhs < rhs); }

    [[nodiscard]] friend inline constexpr bool operator==(const T & lhs, const T & rhs) // note: operator!= not required
    {
        return (!(lhs < rhs) && !(rhs < lhs));
    }

protected:

    ~Relational() = default; // note: non-polymorphic class

}; // template < typename T > class Relational

class Apple : private Relational < Apple > // note: allowed private inheritance
{
public:

    constexpr explicit Apple(double weight) : m_weight(weight) {}

    [[nodiscard]] friend inline constexpr bool operator<(const Apple & lhs, const Apple & rhs)
    {
        return (lhs.m_weight < rhs.m_weight);
    }

private:

    double m_weight;

}; // class Apple : private Relational < Apple > 

class Human : private Relational < Human > // note: allowed private inheritance
{
public:

    constexpr explicit Human(double height) : m_height(height) {}

    [[nodiscard]] friend inline constexpr bool operator<(const Human & lhs, const Human & rhs)
    {
        return (lhs.m_height < rhs.m_height);
    }

private:

    double m_height;

}; // class Human : private Relational < Human > 

class Train : private boost::less_than_comparable < Train > , private boost::equivalent < Train >
{
public:

    constexpr explicit Train(double length) : m_length(length) {}

    [[nodiscard]] friend inline constexpr bool operator<(const Train & lhs, const Train & rhs)
    {
        return (lhs.m_length < rhs.m_length);
    }

private:

    double m_length;

}; // class Train : private boost::less_than_comparable < Train > , private boost::equivalent < Train >

int main() 
{    
    constexpr Apple apple_1(200.0);
    constexpr Apple apple_2(100.0);

    std::cout << "apple_1 <  apple_2: " << (apple_1 <  apple_2) << std::endl;
    std::cout << "apple_1 >  apple_2: " << (apple_1 >  apple_2) << std::endl;
    std::cout << "apple_1 <= apple_2: " << (apple_1 <= apple_2) << std::endl;
    std::cout << "apple_1 >= apple_2: " << (apple_1 >= apple_2) << std::endl;
    std::cout << "apple_1 == apple_2: " << (apple_1 == apple_2) << std::endl;
    std::cout << "apple_1 != apple_2: " << (apple_1 != apple_2) << std::endl;

    std::cout << std::endl;
    
    constexpr Human human_1(185.0);
    constexpr Human human_2(180.0);

    std::cout << "human_1 <  human_2: " << (human_1 <  human_2) << std::endl;
    std::cout << "human_1 >  human_2: " << (human_1 >  human_2) << std::endl;
    std::cout << "human_1 <= human_2: " << (human_1 <= human_2) << std::endl;
    std::cout << "human_1 >= human_2: " << (human_1 >= human_2) << std::endl;
    std::cout << "human_1 == human_2: " << (human_1 == human_2) << std::endl;
    std::cout << "human_1 != human_2: " << (human_1 != human_2) << std::endl;

    std::cout << std::endl;

    constexpr Train train_1(800.0);
    constexpr Train train_2(600.0);

    std::cout << "train_1 <  train_2: " << (train_1 <  train_2) << std::endl;
    std::cout << "train_1 >  train_2: " << (train_1 >  train_2) << std::endl;
    std::cout << "train_1 <= train_2: " << (train_1 <= train_2) << std::endl;
    std::cout << "train_1 >= train_2: " << (train_1 >= train_2) << std::endl;
    std::cout << "train_1 == train_2: " << (train_1 == train_2) << std::endl;
    std::cout << "train_1 != train_2: " << (train_1 != train_2) << std::endl;
    
    return 0;
}