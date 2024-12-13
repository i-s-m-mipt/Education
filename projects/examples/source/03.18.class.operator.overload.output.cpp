#include <iostream>
#include <ostream>

//////////////////////////////////////////////////////////////////////////

class Entity
{
public:

    virtual ~Entity() = default;

//  ----------------------------------------------------------------------

    friend auto & operator<<(std::ostream & stream, const Entity & entity)
    {
        return entity.print(stream);
    }

private:

    virtual std::ostream & print(std::ostream & stream) const 
    { 
        return stream << "Entity"; 
    }
};

//////////////////////////////////////////////////////////////////////////

class Client : public Entity 
{
public:

    std::ostream & print(std::ostream & stream) const override 
    { 
        return stream << "Client"; 
    }
};

//////////////////////////////////////////////////////////////////////////

int main()
{
    Entity * entity = new Client();

    std::cout << "*entity = " << *entity << '\n';

    delete entity;
}