#include <iostream>
#include <utility>

///////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public:

    void initialize() const 
    { 
        std::cout << "Entity::initialize\n";
    }

protected:

    Entity(int) {}
};

///////////////////////////////////////////////////////////////////////////////////////

template < typename B > class Handler : private B
{
public:

    template < typename ... Ts > Handler(Ts && ... xs) : B(std::forward < Ts > (xs)...)
    {
        this->initialize();
    }
};

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Handler < Entity > entity(1);
}