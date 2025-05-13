//////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;
};

//////////////////////////////////////////////////////////////////////////

class Client : public Entity
{
public :

    class Factory
    {
    public :

        static auto make_client_v1() -> Entity * { return new Client(1); }
        
        static auto make_client_v2() -> Entity * { return new Client(2); }
    };

private :

    Client(int x) : m_x(x) {}

//  ----------------------------------------------------------------------

    int m_x = 0;
};

//////////////////////////////////////////////////////////////////////////

int main()
{
    delete Client::Factory::make_client_v1();
}

//////////////////////////////////////////////////////////////////////////