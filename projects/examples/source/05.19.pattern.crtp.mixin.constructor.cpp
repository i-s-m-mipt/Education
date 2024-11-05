#include <iostream>

//  ================================================================================================

struct Entity
{
    virtual ~Entity() = default; 

    virtual void test() const = 0;
};

//  ================================================================================================

class Client : public Entity
{
protected:

    explicit Client(int) {} 

public:

    void test() const override 
    { 
        std::clog << "Client::test\n"; 
    }
};

//  ================================================================================================

template < typename B > struct Router : private B
{
    template < typename ... Ts > explicit Router(Ts && ... args) : B(std::forward < Ts > (args)...)
    {
        this->test();
    }
};

//  ================================================================================================

int main()
{
    Router < Client > router(1);
}