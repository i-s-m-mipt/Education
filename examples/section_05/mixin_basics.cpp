#include <iostream>

class Base 
{
public:

    void f() const { std::cout << "Base" << std::endl; };

}; // class Base 

template < typename Base > class Mixin_1 : public Base
{
public:

    void g() const { std::cout << "Mixin_1" << std::endl; Base::f(); }

}; // template < typename Base > class Mixin_1 : public Base 

template < typename Base > class Mixin_2 : public Base
{
public:

    void h() const { std::cout << "Mixin_2" << std::endl; Base::g(); }

}; // template < typename Base > class Mixin_2 : public Base 

class Color {};
class Label {};

template < typename ... Bases > class Point : private Bases... // note: modern mixin
{
public:

    explicit Point(double x, double y) : Bases()..., m_x(x), m_y(y)
    {
        std::cout << sizeof...(Bases) << std::endl;
    }

private:

    double m_x;
    double m_y;

}; // template < typename T, typename ... Bases > class Point : private Bases...

int main() 
{
    Mixin_2 < Mixin_1 < Base > > mixin; // note: old style mixin
    
    mixin.h();

    [[maybe_unused]] Point < Color, Label > p1(1.0, 1.0);
    [[maybe_unused]] Point < Color        > p2(2.0, 2.0);
    [[maybe_unused]] Point <              > p3(3.0, 3.0);

    return 0;
}