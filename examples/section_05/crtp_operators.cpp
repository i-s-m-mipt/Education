#include <iostream>

#include <boost/operators.hpp>

template < typename T > class Relational 
{
    friend auto operator> (const T & lhs, const T & rhs) { return  (rhs < lhs); }
    friend auto operator<=(const T & lhs, const T & rhs) { return !(lhs > rhs); }
    friend auto operator>=(const T & lhs, const T & rhs) { return !(lhs < rhs); }

    friend auto operator==(const T & lhs, const T & rhs) // note: operator!= not required
    {
        return (!(lhs < rhs) && !(rhs < lhs));
    }

}; // template < typename T > class Relational

class Apple : Relational < Apple > // note: allowed private inheritance
{
public:

    explicit Apple(double weight) : m_weight(weight) {}

    friend auto operator<(const Apple & lhs, const Apple & rhs)
    {
        return (lhs.m_weight < rhs.m_weight);
    }

private:

    double m_weight;

}; // class Apple : public Relational < Apple > 

class Human : Relational < Human > // note: allowed private inheritance
{
public:

    explicit Human(double height) : m_height(height) {}

    friend auto operator<(const Human & lhs, const Human & rhs)
    {
        return (lhs.m_height < rhs.m_height);
    }

private:

    double m_height;

}; // class Human : public Relational < Human > 

class Train : boost::less_than_comparable < Train > , boost::equivalent < Train >
{
public:

    explicit Train(double length) : m_length(length) {}

    friend auto operator<(const Train & lhs, const Train & rhs)
    {
        return (lhs.m_length < rhs.m_length);
    }

private:

    double m_length;

}; // class Train : public boost::less_than_comparable < Train >

int main() 
{
    Apple apple_1(200.0);
    Apple apple_2(100.0);

    std::cout << "apple_1 <  apple_2: " << (apple_1 <  apple_2) << std::endl;
    std::cout << "apple_1 >  apple_2: " << (apple_1 >  apple_2) << std::endl;
    std::cout << "apple_1 <= apple_2: " << (apple_1 <= apple_2) << std::endl;
    std::cout << "apple_1 >= apple_2: " << (apple_1 >= apple_2) << std::endl;
    std::cout << "apple_1 == apple_2: " << (apple_1 == apple_2) << std::endl;
    std::cout << "apple_1 != apple_2: " << (apple_1 != apple_2) << std::endl;

    std::cout << std::endl;
    
    Human human_1(185.0);
    Human human_2(180.0);

    std::cout << "human_1 <  human_2: " << (human_1 <  human_2) << std::endl;
    std::cout << "human_1 >  human_2: " << (human_1 >  human_2) << std::endl;
    std::cout << "human_1 <= human_2: " << (human_1 <= human_2) << std::endl;
    std::cout << "human_1 >= human_2: " << (human_1 >= human_2) << std::endl;
    std::cout << "human_1 == human_2: " << (human_1 == human_2) << std::endl;
    std::cout << "human_1 != human_2: " << (human_1 != human_2) << std::endl;

    std::cout << std::endl;

    Train train_1(800.0);
    Train train_2(600.0);

    std::cout << "train_1 <  train_2: " << (train_1 <  train_2) << std::endl;
    std::cout << "train_1 >  train_2: " << (train_1 >  train_2) << std::endl;
    std::cout << "train_1 <= train_2: " << (train_1 <= train_2) << std::endl;
    std::cout << "train_1 >= train_2: " << (train_1 >= train_2) << std::endl;
    std::cout << "train_1 == train_2: " << (train_1 == train_2) << std::endl;
    std::cout << "train_1 != train_2: " << (train_1 != train_2) << std::endl;
    
    return 0;
}