#include <iostream>
#include <utility>

////////////////////////////////////////////////////////////////

class Entity
{
public:

    virtual ~Entity() = default; 

//  ------------------------------------

    virtual void initialize() const = 0;
};

////////////////////////////////////////////////////////////////

class Client : public Entity
{
public:

    void initialize() const override 
    { 
        std::clog << "Client::initialize\n"; 
    }

protected:

    explicit Client(int) {}; 
};

////////////////////////////////////////////////////////////////

template < typename B > class Router : private B
{
public:

    template < typename ... Ts > explicit Router(Ts && ... args) 
    : 
        B(std::forward < Ts > (args)...)
    {
        this->initialize();
    }
};

////////////////////////////////////////////////////////////////

int main()
{
    Router < Client > router(1);
}