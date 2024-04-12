#include <iostream>

// =================================================================================================

class BIOS 
{
public:

    virtual ~BIOS() = default; // note: polymorphic base class

    virtual void run() const = 0;

}; // class BIOS 

// =================================================================================================

class Phoenix : public BIOS { public: void run() const override { std::cout << "Phoenix" << std::endl; } };
class Microid : public BIOS { public: void run() const override { std::cout << "Microid" << std::endl; } };

// =================================================================================================

class Computer 
{
public:

    explicit Computer(const BIOS & bios) : m_bios(bios) {}

    virtual ~Computer() = default; // note: polymorphic base class

    virtual void run() const = 0;

protected:

    const BIOS & m_bios; // note: consider templates instead of hierarchy

}; // class Computer 

// =================================================================================================

class Laptop : public Computer 
{
public:

    explicit Laptop(const BIOS & bios) : Computer(bios) {}

    void run() const override { m_bios.run(); }

}; // class Laptop : public Computer 

// =================================================================================================

int main() 
{
    const Computer * const laptop = new const Laptop(Phoenix());

    laptop->run(); 
    
    delete laptop; // good: no memory leak

    return 0;
}