#include <cassert>
#include <vector>

//  ================================================================================================

struct Entity
{
    virtual ~Entity() = default; 

//  ------------------------------------------------------------------------------------------------

    virtual std::size_t size() const = 0;
};

//  ================================================================================================

struct Client : public Entity { std::size_t size() const override { return 1; }; };
struct Server : public Entity { std::size_t size() const override { return 2; }; };

//  ================================================================================================

class Composite : public Entity
{
public:

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

//  ------------------------------------------------------------------------------------------------

    std::size_t size() const override
    {
        auto size = 0uz;

        for (auto entity : m_entities)
        {
            if (entity) 
            {
                size += entity->size();
            }
        }

        return size;
    }
    
//  ------------------------------------------------------------------------------------------------

    void add_entity(Entity * entity) 
    { 
        m_entities.push_back(entity); 
    }

private:
    
    std::vector < Entity * > m_entities;
};

//  ================================================================================================

Entity * make_composite(std::size_t n_clients, std::size_t n_servers)
{
    auto composite = new Composite;

    for (auto i = 0uz; i < n_clients; ++i) { composite->add_entity(new Client()); }
    for (auto i = 0uz; i < n_servers; ++i) { composite->add_entity(new Server()); }

    return composite;
}

//  ================================================================================================

int main()
{
    auto composite = new Composite;

    for (auto i = 0uz; i < 5; ++i) 
    {
        composite->add_entity(make_composite(1, 1));
    }

    Entity * entity = composite;
        
    assert(entity->size() == 15);

    delete entity;
}