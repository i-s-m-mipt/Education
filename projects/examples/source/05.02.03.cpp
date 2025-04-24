//////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <vector>

//////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;

//  -----------------------------

    virtual int test() const = 0;
};

//////////////////////////////////////////////////////////////////////////////

class Client : public Entity 
{ 
public : 

    int test() const override 
    { 
        return 1; 
    } 
};

//////////////////////////////////////////////////////////////////////////////

class Server : public Entity 
{ 
public : 

    int test() const override 
    { 
        return 2; 
    } 
};

//////////////////////////////////////////////////////////////////////////////

class Composite : public Entity
{
public :

   ~Composite()
    {
        for (auto entity : m_entities)
        {
            if (entity)
            {
                delete entity;
            }
        }
    }

//  ------------------------------------

    void add_entity(Entity * entity) 
    { 
        m_entities.push_back(entity);
    }

//  ------------------------------------

    int test() const override
    {
        auto x = 0;

        for (auto entity : m_entities)
        {
            if (entity) 
            {
                x += entity->test();
            }
        }

        return x;
    }

private :
    
    std::vector < Entity * > m_entities;
};

//////////////////////////////////////////////////////////////////////////////

auto make_composite(std::size_t size_1, std::size_t size_2) -> Entity *
{
    auto composite = new Composite;

    for (auto i = 0uz; i < size_1; ++i) { composite->add_entity(new Client); }
    
    for (auto i = 0uz; i < size_2; ++i) { composite->add_entity(new Server); }

    return composite;
}

//////////////////////////////////////////////////////////////////////////////

int main()
{
    auto composite = new Composite;

//  ------------------------------------------------

    for (auto i = 0uz; i < 5; ++i)
    {
        composite->add_entity(make_composite(1, 1));
    }

//  ------------------------------------------------

    Entity * entity = composite;

//  ------------------------------------------------
        
    assert(entity->test() == 15);

//  ------------------------------------------------

    delete entity;
}

//////////////////////////////////////////////////////////////////////////////