#include <iostream>

class Computer
{
public:
    
    virtual ~Computer() = default; // note: polymorphic base class

    [[nodiscard]] virtual Computer * clone() const = 0; // note: virtual copy

    virtual void run() const = 0;

}; // class Computer

class Mobile : public Computer
{
public:

    [[nodiscard]] Computer * clone() const override 
    { 
        return new Mobile(*this); // note: delete required
    } 

    void run() const override { std::cout << "Mobile" << std::endl; };

}; // class Mobile : public Computer

class Tablet : public Computer
{
public:

    [[nodiscard]] Computer * clone() const override 
    { 
        return new Tablet(*this); // note: delete required
    } 

    void run() const override { std::cout << "Tablet" << std::endl; };

}; // class Tablet : public Computer

class Laptop : public Computer
{
public:

    [[nodiscard]] Computer * clone() const override 
    { 
        return new Laptop(*this); // note: delete required
    } 

    void run() const override { std::cout << "Laptop" << std::endl; };

}; // class Laptop : public Computer

class Factory // note: no factory hierarchy, static prototypes and virtual copy
{
public:

    [[nodiscard]] auto create_mobile() const { static Mobile p; return p.clone(); }
    [[nodiscard]] auto create_tablet() const { static Tablet p; return p.clone(); }
    [[nodiscard]] auto create_laptop() const { static Laptop p; return p.clone(); }

}; // class Factory

int main()
{
    Factory factory;

    delete factory.create_mobile();
    delete factory.create_tablet();
    delete factory.create_laptop();

    return 0;
}