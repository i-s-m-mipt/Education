#include <iostream>
#include <ostream>

//////////////////////////////////////////////////////////////////////////

class Entity
{
public:

    virtual ~Entity() = default;

//  ----------------------------------------------------------------------

    friend auto & operator>>(std::istream & stream, Entity & entity)
    {
        entity.get(stream);

        return stream;
    }

    friend auto & operator<<(std::ostream & stream, const Entity & entity)
    {
        entity.put(stream);

        return stream;
    }

protected:

    virtual void get(std::istream & stream)
    {
        stream >> m_data;
    }

    virtual void put(std::ostream & stream) const 
    { 
        stream << "{ " << m_data << " }";
    }

//  ----------------------------------------------------------------------

    int m_data = 0;
};

//////////////////////////////////////////////////////////////////////////

class Client : public Entity 
{
public:

    void get(std::istream & stream) override
    {
        Entity::get(stream);
        
        stream >> Client::m_data;
    }

    void put(std::ostream & stream) const override 
    { 
        stream << "{ " << Entity::m_data << ' ' << Client::m_data << " }";
    }

private:

    int m_data = 0;
};

//////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << "main : enter Client : ";
    
    Entity * entity = new Client;
    
    std::cin >> *entity;

    std::cout << "main : *entity = " << *entity << '\n';

    delete entity;
}