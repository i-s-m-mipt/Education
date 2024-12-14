#include <iostream>
#include <utility>

////////////////////////////////////////////////////////////////////////////////////////

class Client_v1 { public: explicit Client_v1(int) {} };
class Server_v1 { public: explicit Server_v1(int) {} };

////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Bs > class Router_v1 : public Bs ...
{
public:

    template < typename ... Ts > explicit Router_v1(int data, Ts && ... args) 
    : 
        Bs(std::forward < Ts > (args))..., m_data(data)
    {
        std::clog << "Router_v1::Router_v1 : sizeof...(Bs) = " << sizeof...(Bs) << '\n';
    }

private:

    int m_data = 0;
};

////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Client_v2 { public: explicit Client_v2(int) {} };
template < typename T > class Server_v2 { public: explicit Server_v2(int) {} };

////////////////////////////////////////////////////////////////////////////////////////

template < template < typename T > typename ... Bs > class Router_v2 
: 
    public Bs < Router_v2 < Bs ... > > ... 
{
public:

    template < typename ... Ts > explicit Router_v2(int data, Ts && ... args) 
    : 
        Bs < Router_v2 > (std::forward < Ts > (args))..., m_data(data)
    {
        std::clog << "Router_v2::Router_v2 : sizeof...(Bs) = " << sizeof...(Bs) << '\n';
    }

private:

    int m_data = 0;
};

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Router_v1 < Client_v1, Server_v1 > router_v1_1(1, 1, 1);
    Router_v1 < Client_v1            > router_v1_2(2, 2   );
    Router_v1 <                      > router_v1_3(3      );

    Router_v2 < Client_v2, Server_v2 > router_v2_1(1, 1, 1);
    Router_v2 < Client_v2            > router_v2_2(2, 1   );
    Router_v2 <                      > router_v2_3(3      );
}