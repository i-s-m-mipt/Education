///////////////////////////////////////////////////////////

// chapter : Software Engineering Patterns

///////////////////////////////////////////////////////////

// content : Pattern Prototype

///////////////////////////////////////////////////////////

#include <vector>

///////////////////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;

//  ----------------------------------

    virtual Entity * copy() const = 0;
};

///////////////////////////////////////////////////////////

class Client : public Entity
{
public :

    Entity * copy() const override
    {
        return new Client(*this);
    }
};

///////////////////////////////////////////////////////////

class Server : public Entity
{
public :

    Entity * copy() const override
    {
        return new Server(*this);
    }
};

///////////////////////////////////////////////////////////

class Factory
{
public :

    Factory()
    {
        m_entities.push_back(new Client);

        m_entities.push_back(new Server);
    }

//  -------------------------------------------------------

   ~Factory()
    {
        for (auto entity : m_entities)
        {
            delete entity;
        }
    }

//  -------------------------------------------------------

    auto make_client() { return m_entities.at(0)->copy(); }

    auto make_server() { return m_entities.at(1)->copy(); }

private :

    std::vector < Entity * > m_entities;
};

///////////////////////////////////////////////////////////

int main()
{
    delete Factory().make_client();
}

///////////////////////////////////////////////////////////