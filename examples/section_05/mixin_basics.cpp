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

int main() 
{
    Mixin_2 < Mixin_1 < Base > > ().h();

    return 0;
}