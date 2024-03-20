#include <iostream>

class Computer
{
public:

    virtual ~Computer() = default; // note: polymorphic base class

    virtual void run() const = 0;
    
}; // class Computer

class Mobile : public Computer { public: void run() const override { std::cout << "Mobile" << std::endl; }; };
class Tablet : public Computer { public: void run() const override { std::cout << "Tablet" << std::endl; }; };
class Laptop : public Computer { public: void run() const override { std::cout << "Laptop" << std::endl; }; };

template < typename T > [[nodiscard]] inline Computer * create() // note: factory function, consider enumeration
{
    return new T; // note: consider type traits to verify type T is correct
}

class Server : public Computer
{
public:

    class Factory // note: factory methods
    {
    public:

        [[nodiscard]] static Computer * create_v1() { return new Server(1); }
        [[nodiscard]] static Computer * create_v2() { return new Server(2); }
        [[nodiscard]] static Computer * create_v3() { return new Server(3); }

    }; // class Factory

    void run() const override { std::cout << "Server v" << m_version << std::endl; };

private:

    explicit Server(int version) : m_version(version) {}; // note: use factory methods

    int m_version = 0;

}; // class Server : public Computer

class Factory
{
public:

    virtual ~Factory() = default; // note: polymorphic base class

    [[nodiscard]] virtual Computer * create() const = 0;
    
}; // class Factory

class Factory_Mobile : public Factory
{
public: 
    
    [[nodiscard]] Computer * create() const override { return new Mobile; } 

}; // class Factory_Mobile : public Factory

class Factory_Tablet : public Factory
{
public: 
    
    [[nodiscard]] Computer * create() const override { return new Tablet; }

}; // class Factory_Tablet : public Factory

class Factory_Laptop : public Factory
{
public: 
    
    [[nodiscard]] Computer * create() const override { return new Laptop; }

}; // class Factory_Laptop : public Factory

int main()
{
    Computer * const mobile = create < Mobile > (); 

    mobile->run(); 
    
    delete mobile; // good: no memory leak

    Computer * const server = Server::Factory::create_v1(); 

    server->run(); 
    
    delete server; // good: no memory leak

    Factory * const factory_laptop = new Factory_Laptop;

    Computer * const laptop = factory_laptop->create(); 

    laptop->run(); 
    
    delete laptop; delete factory_laptop; // good: no memory leak

    return 0;
}