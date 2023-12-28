#include <iostream>

class Computer
{
public:
    
    virtual ~Computer() = default;

public:

    [[nodiscard]] virtual Computer * clone() const = 0; // note: virtual constructor

    virtual void run() const = 0;

}; // class Computer

class Laptop : public Computer
{
public:

    [[nodiscard]] Computer * clone() const override 
    { 
        return new Laptop(*this); // note: delete required
    } 

    void run() const override { std::cout << "Laptop" << std::endl; };

}; // class Laptop : public Computer

class Desktop : public Computer
{
public:

    [[nodiscard]] Computer * clone() const override 
    { 
        return new Desktop(*this); // note: delete required
    } 

    void run() const override { std::cout << "Desktop" << std::endl; };

}; // class Desktop : public Computer

class Server : public Computer
{
public:

    [[nodiscard]] Computer * clone() const override 
    { 
        return new Server(*this); // note: delete required
    } 

    void run() const override { std::cout << "Server" << std::endl; };

}; // class Server : public Computer

class Factory // note: no factory hierarchy
{
public:

    [[nodiscard]] auto create_laptop() const
    { 
        static Laptop prototype; // note: controversial decision
        
        return prototype.clone(); 
    }

}; // class Factory

int main()
{
    Factory factory;

    auto computer = factory.create_laptop(); // good: laptop only here

    computer->run();

    delete computer; // good: no memory leak

    return 0;
}