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
        std::cout << "Client::initialize\n"; 
    }

protected:

    Client(int) {}; 
};

////////////////////////////////////////////////////////////////

template < typename B > class Router : private B
{
public:

    template < typename ... Ts > Router(Ts && ... xs) : B(std::forward < Ts > (xs)...)
    {
        this->initialize();
    }
};

////////////////////////////////////////////////////////////////

int main()
{
    Router < Client > router(1);
}