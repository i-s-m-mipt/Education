/////////////////////////////////////////////////////////

class Entity
{    
public :

    virtual ~Entity() = default;

//  ----------------------------------

    virtual Entity * copy() const = 0;
};

/////////////////////////////////////////////////////////

class Client : public Entity
{
public :

    Entity * copy() const override 
    { 
        return new Client(*this);
    }
};

/////////////////////////////////////////////////////////

class Server : public Entity
{
public :

    Entity * copy() const override 
    { 
        return new Server(*this);
    }
};

/////////////////////////////////////////////////////////

class Factory
{
public :

    static auto make_client() { return s_client.copy(); }

    static auto make_server() { return s_server.copy(); }

private :

    static inline Client const s_client;

    static inline Server const s_server;
};

/////////////////////////////////////////////////////////

int main()
{
    delete Factory::make_client();
}

/////////////////////////////////////////////////////////