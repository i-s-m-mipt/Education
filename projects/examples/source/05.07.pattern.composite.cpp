#include <cassert>
#include <vector>

//  ================================================================================================

struct Entity
{
    virtual ~Entity() = default; 

//  ------------------------------------------------------------------------------------------------

    [[nodiscard]] virtual std::size_t connections() const = 0;
};

//  ================================================================================================

struct Client : public Entity { [[nodiscard]] std::size_t connections() const override { return 1; }; };
struct Server : public Entity { [[nodiscard]] std::size_t connections() const override { return 2; }; };

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

    [[nodiscard]] std::size_t connections() const override
    {
        auto total_connections = 0uz;

        for (auto entity : m_entities)
        {
            if (entity) 
            {
                total_connections += entity->connections();
            }
        }

        return total_connections;
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

[[nodiscard]] auto make_composite
(
    std::size_t n_clients, 
    std::size_t n_servers
)
{
    auto composite = new Composite;

    for (auto i = 0uz; i < n_clients; ++i) { composite->add_entity(new Client()); }
    for (auto i = 0uz; i < n_servers; ++i) { composite->add_entity(new Server()); }

    return static_cast < Entity * > (composite);
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
        
    assert(entity->connections() == 15);

    delete entity;
}