#include <iostream>

//  ================================================================================================

class BIOS
{
public:

    virtual ~BIOS() = default; 

    virtual void run() const = 0;

}; // class BIOS 

//  ================================================================================================

class Phoenix : public BIOS { public: void run() const override; };
class Microid : public BIOS { public: void run() const override; };

//  ================================================================================================

void Phoenix::run() const { std::cout << "Phoenix" << std::endl; }
void Microid::run() const { std::cout << "Microid" << std::endl; }

//  ================================================================================================

class Computer
{
public:

    explicit Computer(const BIOS & bios) : m_bios(bios) {}

    virtual ~Computer() = default; 

    virtual void run() const = 0;

protected:

    const BIOS & m_bios;

}; // class Computer 

//  ================================================================================================

class Laptop : public Computer 
{
public:

    explicit Laptop(const BIOS & bios) : Computer(bios) {}

    void run() const override { m_bios.run(); }

}; // class Laptop : public Computer 

//  ================================================================================================

int main() 
{
    const Computer * const laptop = new const Laptop(Phoenix());

    laptop->run(); 
    
    delete laptop;

    return 0;
}