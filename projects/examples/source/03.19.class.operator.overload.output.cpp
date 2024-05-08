#include <iostream>
#include <ostream>

//  ================================================================================================

class Base
{
public:

    virtual ~Base() {};

    friend std::ostream & operator<<(std::ostream & stream, const Base & base)
    {
        return base.print(stream);
    }

    virtual std::ostream & print(std::ostream & stream) const { return (stream << "Base"); }

}; // class Base

//  ================================================================================================

class Derived : public Base 
{ 
public: 

    std::ostream & print(std::ostream & stream) const override { return (stream << "Derived"); }

}; // class Derived : public Base 

//  ================================================================================================

int main()
{
    const Base * const base = new const Derived();

    std::cout << *base << std::endl;

    delete base;

    return 0;
}