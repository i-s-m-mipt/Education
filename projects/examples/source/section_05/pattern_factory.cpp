#include <iostream>

class Computer
{
public:

    virtual ~Computer() = default; // note: polymorphic base class

    virtual void run() const = 0;
    
}; // class Computer

struct Mobile : public Computer { void run() const override { std::cout << "Mobile" << std::endl; }; };
struct Tablet : public Computer { void run() const override { std::cout << "Tablet" << std::endl; }; };
struct Laptop : public Computer { void run() const override { std::cout << "Laptop" << std::endl; }; };

template < typename T > [[nodiscard]] inline Computer * create() // note: factory function, consider enumeration
{
    return new T; // note: delete required, consider type traits to verify type T is correct
}

class Server : public Computer
{
public:

    struct Factory // note: factory methods
    {
        [[nodiscard]] static Computer * create_v1() { return new Server(1); } // note: delete required
        [[nodiscard]] static Computer * create_v2() { return new Server(2); } // note: delete required
        [[nodiscard]] static Computer * create_v3() { return new Server(3); } // note: delete required

    }; // struct Factory

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
public: [[nodiscard]] Computer * create() const override { return new Mobile; } // note: delete required 
};

class Factory_Tablet : public Factory
{
public: [[nodiscard]] Computer * create() const override { return new Tablet; } // note: delete required 
};

class Factory_Laptop : public Factory
{
public: [[nodiscard]] Computer * create() const override { return new Laptop; } // note: delete required
};

int main()
{
    auto mobile = create < Mobile > (); 

    mobile->run(); delete mobile; // good: no memory leak

    auto server = Server::Factory::create_v1(); 

    server->run(); delete server; // good: no memory leak

    Factory * factory_laptop = new Factory_Laptop; // note: delete required

    auto laptop = factory_laptop->create(); 

    laptop->run(); delete laptop; // good: no memory leak

    delete factory_laptop; // good: no memory leak

    return 0;
}