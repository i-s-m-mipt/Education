#include <iostream>
#include <ostream>

class Base
{
public:

    virtual ~Base() {}; // note: polymorphic base class

    friend std::ostream & operator<<(std::ostream & stream, const Base & base)
    {
        base.print(stream); // note: virtual function called from non-virtual operator

        return stream;
    }

    virtual void print(std::ostream & stream) const { stream << "Base"; }

}; // class Base

class Derived : public Base
{
public:
    
    void print(std::ostream & stream) const override { stream << "Derived"; }

}; // class Derived : public Base

int main()
{
    const Base * const base = new Derived;

    std::cout << *base << std::endl;

    delete base;

    return 0;
}