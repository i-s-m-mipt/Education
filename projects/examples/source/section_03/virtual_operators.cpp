#include <iostream>
#include <ostream>

class Base
{
public:

    virtual ~Base() {}; // note: polymorphic base class

    virtual void print() const { std::cout << "Base"; }

    friend std::ostream & operator<<(std::ostream & stream, const Base & base)
    {
        base.print(); // note: virtual function called from non-virtual operator

        return stream;
    }

}; // class Base

class Derived : public Base
{
public:

    void print() const override { std::cout << "Derived"; }

}; // class Derived : public Base

int main()
{
    Base * base = new Derived;

    std::cout << *base << std::endl;

    delete base;

    return 0;
}