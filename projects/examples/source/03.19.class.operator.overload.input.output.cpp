#include <iostream>
#include <ostream>

///////////////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public:

    virtual ~Entity() = default;

//  ----------------------------------------------------------------------

    friend auto & operator>>(std::istream & stream, Entity & entity)
    {
        entity.read(stream);

        return stream;
    }

    friend auto & operator<<(std::ostream & stream, const Entity & entity)
    {
        entity.write(stream);

        return stream;
    }

protected:

    virtual void read (std::istream & stream)
    {
        stream >> m_data;
    }

    virtual void write(std::ostream & stream) const 
    { 
        stream << "Entity::m_data = " << m_data;
    }

private:

    int m_data = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Client : public Entity 
{
public:

    void read (std::istream & stream) override
    {
        Entity::read (stream); stream >> m_data;
    }

    void write(std::ostream & stream) const override 
    { 
        Entity::write(stream); stream << "\nClient::m_data = " << m_data; 
    }

private:

    int m_data = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << "main : enter Client : "; Entity * entity = new Client(); std::cin >> *entity;

    std::cout << "main : *entity = " << *entity << '\n';

    delete entity;
}