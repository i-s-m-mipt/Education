//////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <istream>
#include <ostream>
#include <sstream>

//////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;

//  ----------------------------------------------------------------------

    friend auto & operator>>(std::istream & stream, Entity & entity)
    {
        stream.get();

    //  -------------------
        
        entity.get(stream);

    //  -------------------

        stream.get();

    //  -------------------

        return stream;
    }

//  ----------------------------------------------------------------------

    friend auto & operator<<(std::ostream & stream, const Entity & entity)
    {
        stream << "{ "; 

    //  -------------------
        
        entity.put(stream);

    //  -------------------

        stream << " }";

    //  -------------------

        return stream;
    }

protected :

    virtual void get(std::istream & stream)
    {
        stream >> m_x;
    }

//  ----------------------------------------------------------------------

    virtual void put(std::ostream & stream) const 
    { 
        stream << m_x;
    }

//  ----------------------------------------------------------------------

    int m_x = 0;
};

//////////////////////////////////////////////////////////////////////////

class Client : public Entity 
{
public :

    void get(std::istream & stream) override
    {
        Entity::get(stream);
        
        stream >> m_y;
    }

//  ----------------------------------------------

    void put(std::ostream & stream) const override 
    { 
        Entity::put(stream);

        stream << ' ' << m_y;
    }

private :

    int m_y = 0;
};

//////////////////////////////////////////////////////////////////////////

int main()
{
    std::stringstream stream_1("{ 1 1 }");

    std::stringstream stream_2;

//  -----------------------------------------
    
    Entity * entity = new Client;

//  -----------------------------------------

    stream_1 >> *entity;

    stream_2 << *entity;

//  -----------------------------------------

    delete entity;

//  -----------------------------------------

    assert(stream_2.str() == stream_1.str());
}

//////////////////////////////////////////////////////////////////////////