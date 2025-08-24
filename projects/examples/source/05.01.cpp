////////////////////////////////////////////////////

#include <cassert>

////////////////////////////////////////////////////

struct Entity
{
    int x = 0, y = 0;
};

////////////////////////////////////////////////////

class Builder
{
public :

    virtual ~Builder() = default;

//  -------------------------------

    auto make_entity()
    { 
        m_entity = new Entity;

        set_x();
        
        set_y();

        return m_entity;
    }

//  -------------------------------

    virtual void set_x() const = 0;

    virtual void set_y() const = 0;

protected :

    Entity * m_entity = nullptr;
};

////////////////////////////////////////////////////

class Builder_Client : public Builder
{
public :

    void set_x() const override { m_entity->x = 1; }

    void set_y() const override { m_entity->y = 1; }
};

////////////////////////////////////////////////////

class Builder_Server : public Builder
{
public :

    void set_x() const override { m_entity->x = 1; }

    void set_y() const override { m_entity->y = 1; }
};

////////////////////////////////////////////////////

int main()
{
    Builder * builder = new Builder_Client;

//  ---------------------------------------

    delete builder->make_entity();
    
    delete builder;
}

////////////////////////////////////////////////////