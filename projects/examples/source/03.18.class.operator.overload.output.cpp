#include <iostream>
#include <ostream>

//  ================================================================================================

struct Entity
{
    virtual ~Entity() = default;

//  ------------------------------------------------------------------------------------------------

    friend auto & operator<<(std::ostream & stream, const Entity & entity)
    {
        return entity.print(stream);
    }

//  ------------------------------------------------------------------------------------------------

    virtual std::ostream & print(std::ostream & stream) const 
    { 
        return stream << "Entity"; 
    }
};

//  ================================================================================================

struct Client : public Entity 
{ 
    std::ostream & print(std::ostream & stream) const override 
    { 
        return stream << "Client"; 
    }
};

//  ================================================================================================

int main()
{
    Entity * entity = new Client();

    std::cout << "*entity = " << *entity << '\n';

    delete entity;
}