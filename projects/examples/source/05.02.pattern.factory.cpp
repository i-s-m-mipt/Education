#include <iostream>

//  ================================================================================================

class Computer
{
public:

    virtual ~Computer() = default;

    virtual void run() const = 0;
    
}; // class Computer

//  ================================================================================================

class Mobile : public Computer { public: void run() const override; };
class Tablet : public Computer { public: void run() const override; };
class Laptop : public Computer { public: void run() const override; };

//  ================================================================================================

void Mobile::run() const { std::cout << "Mobile" << std::endl; }
void Tablet::run() const { std::cout << "Tablet" << std::endl; }
void Laptop::run() const { std::cout << "Laptop" << std::endl; }

//  ================================================================================================

template < typename T > [[nodiscard]] inline const Computer * create() { return new const T(); }

//  ================================================================================================

class Server : public Computer
{
public:

    class Factory
    {
    public:

        [[nodiscard]] static const Computer * create_v1() { return new const Server(1); }
        [[nodiscard]] static const Computer * create_v2() { return new const Server(2); }
        [[nodiscard]] static const Computer * create_v3() { return new const Server(3); }

    }; // class Factory

    void run() const override { std::cout << "Server v" << m_version << std::endl; };

private:

    explicit Server(int version) : m_version(version) {};

    int m_version;

}; // class Server : public Computer

//  ================================================================================================

class Factory
{
public:

    virtual ~Factory() = default; 

    [[nodiscard]] virtual const Computer * create() const = 0;
    
}; // class Factory

//  ================================================================================================

class Factory_Mobile : public Factory
{
public: [[nodiscard]] const Computer * create() const override { return new const Mobile(); } 
};

//  ================================================================================================

class Factory_Tablet : public Factory
{
public: [[nodiscard]] const Computer * create() const override { return new const Tablet(); }
};

//  ================================================================================================

class Factory_Laptop : public Factory
{
public: [[nodiscard]] const Computer * create() const override { return new const Laptop(); }
}; 

//  ================================================================================================

int main()
{
    const auto mobile = create < Mobile > (); 

    mobile->run(); 
    
    delete mobile;

//  ================================================================================================

    const auto server = Server::Factory::create_v1(); 

    server->run(); 
    
    delete server;

//  ================================================================================================

    const Factory * const factory_laptop = new const Factory_Laptop();

    const auto laptop = factory_laptop->create(); 

    laptop->run(); 
    
    delete laptop; delete factory_laptop;

    return 0;
}