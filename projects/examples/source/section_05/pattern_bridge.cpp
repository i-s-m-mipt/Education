#include <iostream>

class BIOS 
{
public:

    virtual ~BIOS() = default; // note: polymorphic base class

    virtual void run() const = 0;

}; // class BIOS 

struct Phoenix : public BIOS { void run() const override { std::cout << "Phoenix\n"; } };
struct Microid : public BIOS { void run() const override { std::cout << "Microid\n"; } };

class Computer 
{
public:

    explicit Computer(const BIOS & bios) : m_bios(bios) {}

    virtual ~Computer() = default; // note: polymorphic base class

    virtual void run() const = 0;

protected:

    const BIOS & m_bios;

}; // class Computer 

class Laptop : public Computer 
{
public:

    explicit Laptop(const BIOS & bios) : Computer(bios) {}

    void run() const override { m_bios.run(); }

}; // class Laptop : public Computer 

int main() 
{
    Laptop(Phoenix()).run();
    Laptop(Microid()).run();

    return 0;
}