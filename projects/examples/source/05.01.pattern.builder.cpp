#include <cassert>
#include <string>

///////////////////////////////////////////////////////////////

struct Entity
{
    int data_1 = 0;
    int data_2 = 0; 
};

///////////////////////////////////////////////////////////////

class Builder
{
public:

    virtual ~Builder() = default;

//  -------------------------------------

    auto make() const
    { 
        m_entity = new Entity();

        make_data_1();
        make_data_2();

        return m_entity; 
    }

//  -------------------------------------

    virtual void make_data_1() const = 0;
    virtual void make_data_2() const = 0;

protected:

    mutable Entity * m_entity = nullptr;
};

///////////////////////////////////////////////////////////////

class Builder_Client : public Builder
{
public:

    void make_data_1() const override { m_entity->data_1 = 1; }
    void make_data_2() const override { m_entity->data_2 = 1; }
};

///////////////////////////////////////////////////////////////

class Builder_Server : public Builder
{
public:

    void make_data_1() const override { m_entity->data_1 = 2; }
    void make_data_2() const override { m_entity->data_2 = 2; }
};

///////////////////////////////////////////////////////////////

int main()
{
    Builder * builder = new Builder_Client();

    auto entity = builder->make();

    assert
    (
        entity->data_1 == 1 &&
        entity->data_2 == 1
    );

    delete entity; delete builder;
}