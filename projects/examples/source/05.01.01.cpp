/////////////////////////////////////////////////////

#include <cassert>

/////////////////////////////////////////////////////

struct Entity
{
    int x = 0, y = 0;
};

/////////////////////////////////////////////////////

class Builder
{
public :

    virtual ~Builder() = default;

//  --------------------------------

    auto make()
    { 
        m_entity = new Entity;

        make_x();
        
        make_y();

        return m_entity;
    }

//  --------------------------------

    virtual void make_x() const = 0;

    virtual void make_y() const = 0;

protected :

    Entity * m_entity = nullptr;
};

/////////////////////////////////////////////////////

class Builder_Client : public Builder
{
public :

    void make_x() const override { m_entity->x = 1; }

    void make_y() const override { m_entity->y = 1; }
};

/////////////////////////////////////////////////////

class Builder_Server : public Builder
{
public :

    void make_x() const override { m_entity->x = 1; }

    void make_y() const override { m_entity->y = 1; }
};

/////////////////////////////////////////////////////

int main()
{
    Builder * builder = new Builder_Client;

//  ---------------------------------------

    delete builder->make();
    
    delete builder;
}

/////////////////////////////////////////////////////