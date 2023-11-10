#include <iostream>

class Computer
{
public:

    virtual ~Computer() = default;

public:

    virtual void run() const = 0;
    
}; // class Computer

class Laptop : public Computer 
{ 
public: 
    
    void run() const override { std::cout << "Laptop" << std::endl; }; 

}; // class Laptop : public Computer 

class Desktop : public Computer
{
public:

    void run() const override { std::cout << "Desktop" << std::endl; };

}; // class Desktop : public Computer 

class Server : public Computer
{
public:

    void run() const override { std::cout << "Server" << std::endl; };

}; // class Server : public Computer 

class Factory
{
public:

    virtual ~Factory() = default;

public:

    [[nodiscard]] virtual Computer * create_computer() const = 0;
    
}; // class Factory

class Laptop_Factory : public Factory
{
public:

    [[nodiscard]] Computer * create_computer() const override 
    { 
        return new Laptop; // note: delete required
    } 

}; // class Laptop_Factory : public Factory

class Desktop_Factory : public Factory
{
public:

    [[nodiscard]] Computer * create_computer() const override 
    { 
        return new Desktop; // note: delete required
    } 

}; // class Desktop_Factory : public Factory

class Server_Factory : public Factory
{
public:

    [[nodiscard]] Computer * create_computer() const override 
    { 
        return new Server; // note: delete required
    } 

}; // class Server_Factory : public Factory

int main()
{
    Factory * factory = new Laptop_Factory; // good: laptop only here

    auto computer = factory->create_computer();

    computer->run();

    delete computer; // good: no memory leak

    delete factory; // good: no memory leak

    return 0;
}