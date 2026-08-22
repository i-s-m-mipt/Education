////////////////////////////////////////////////////

// chapter : Software Engineering Patterns

////////////////////////////////////////////////////

// content : Gang Of Four (GOF) Patterns
//
// content : Pattern Builder

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

class Builder_v1 : public Builder
{
public :

    void set_x() const override { m_entity->x = 1; }

    void set_y() const override { m_entity->y = 1; }
};

////////////////////////////////////////////////////

class Builder_v2 : public Builder
{
public :

    void set_x() const override { m_entity->x = 2; }

    void set_y() const override { m_entity->y = 2; }
};

////////////////////////////////////////////////////

int main()
{
    Builder * builder = new Builder_v1;

//  -----------------------------------

    delete builder->make_entity();

    delete builder;
}

////////////////////////////////////////////////////