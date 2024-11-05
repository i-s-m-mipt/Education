#include <iostream>

//  ================================================================================================

struct Entity
{    
    virtual ~Entity() = default; 

//  ------------------------------------------------------------------------------------------------

    [[nodiscard]] virtual Entity * copy() const = 0;

    virtual void test() const = 0;
};

//  ================================================================================================

struct Client : public Entity
{
    [[nodiscard]] Entity * copy() const override 
    { 
        return new Client(*this); 
    } 

    void test() const override 
    { 
        std::clog << "Client::test\n"; 
    };
};

//  ================================================================================================

struct Server : public Entity
{
    [[nodiscard]] Entity * copy() const override 
    { 
        return new Server(*this); 
    } 

    void test() const override 
    { 
        std::clog << "Server::test\n"; 
    };
};

//  ================================================================================================

struct Factory
{
    [[nodiscard]] static auto make_client() { static Client prototype; return prototype.copy(); }
    [[nodiscard]] static auto make_server() { static Server prototype; return prototype.copy(); }
};

//  ================================================================================================

int main()
{
    auto entity = Factory::make_client(); 

    entity->test(); 
    
    delete entity;
}