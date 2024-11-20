#include <iostream>

//  ============================================================

struct Entity
{
    virtual ~Entity() = default; 

    virtual void initialize() const = 0;
};

//  ============================================================

class Client : public Entity
{
protected:

    explicit Client(int) {}; 

public:

    void initialize() const override 
    { 
        std::clog << "Client::initialize\n"; 
    }
};

//  ============================================================

template < typename B > struct Router : private B
{
    template < typename ... Ts > explicit Router(Ts && ... args) 
    : 
        B(std::forward < Ts > (args)...)
    {
        this->initialize();
    }
};

//  ============================================================

int main()
{
    Router < Client > router(1);
}