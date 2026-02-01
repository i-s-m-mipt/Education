/////////////////////////////////////////////

// chapter : Software Design Patterns

/////////////////////////////////////////////

// section : Generative Patterns

/////////////////////////////////////////////

// content : Pattern Factory Method

/////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;
};

/////////////////////////////////////////////

class Client : public Entity
{
public :

    class Factory
    {
    public :

        static auto make_client() -> Entity *
        { 
            return new Client; 
        }
    };

private :

    Client() = default;
};

/////////////////////////////////////////////

class Server : public Entity
{
public :

    class Factory
    {
    public :

        static auto make_server() -> Entity *
        { 
            return new Server; 
        }
    };

private :

    Server() = default;
};

/////////////////////////////////////////////

int main()
{
    delete Client::Factory::make_client();
}

/////////////////////////////////////////////