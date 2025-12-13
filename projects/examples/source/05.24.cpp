///////////////////////////////////////////////////////////////////////

// support : github.com/tdlib/td/blob/master/example/cpp/td_example.cpp

///////////////////////////////////////////////////////////////////////

#include <utility>

///////////////////////////////////////////////////////////////////////

class Client_v1 { public : Client_v1(int) {} };

class Server_v1 { public : Server_v1(int) {} };

///////////////////////////////////////////////////////////////////////

template < typename ... Bs > class Router_v1 : public Bs ...
{
public :

    template < typename ... Ts > Router_v1(int x, Ts && ... xs) 
    : 
        Bs(std::forward < Ts > (xs))..., m_x(x)
    {}

private :

    int m_x = 0;
};

///////////////////////////////////////////////////////////////////////

template < typename T > class Client_v2 { public : Client_v2(int) {} };

template < typename T > class Server_v2 { public : Server_v2(int) {} };

///////////////////////////////////////////////////////////////////////

template < template < typename T > typename ... Bs > class Router_v2 
: 
    public Bs < Router_v2 < Bs ... > > ... 
{
public :

    template < typename ... Ts > Router_v2(int x, Ts && ... xs) 
    : 
        Bs < Router_v2 > (std::forward < Ts > (xs))..., m_x(x)
    {}

private :

    int m_x = 0;
};

///////////////////////////////////////////////////////////////////////

int main()
{
    Router_v1 < Client_v1, Server_v1 > router_v1(1, 1, 1);
    
    Router_v2 < Client_v2, Server_v2 > router_v2(1, 1, 1);
}

///////////////////////////////////////////////////////////////////////