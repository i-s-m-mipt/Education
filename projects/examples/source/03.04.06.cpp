/////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <istream>
#include <ostream>
#include <sstream>

/////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;

//  ---------------------------------------------------------------------------------

    friend auto & operator>>(std::istream & stream, Entity & entity)
    {
        return entity.get(stream.ignore()).ignore();
    }

//  ---------------------------------------------------------------------------------

    friend auto & operator<<(std::ostream & stream, Entity const & entity)
    {        
        return entity.put(stream << "{ ") << " }";
    }

protected :

    virtual std::istream & get(std::istream & stream)       { return stream >> m_x; }

    virtual std::ostream & put(std::ostream & stream) const { return stream << m_x; }

//  ---------------------------------------------------------------------------------

    int m_x = 0;
};

/////////////////////////////////////////////////////////////////////////////////////

class Client : public Entity 
{
public :

    std::istream & get(std::istream & stream) override
    {
        return Entity::get(stream).ignore() >> m_y;
    }

//  --------------------------------------------------------

    std::ostream & put(std::ostream & stream) const override
    { 
        return Entity::put(stream) << ", " << m_y;
    }

private :

    int m_y = 0;
};

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::stringstream stream_1;

    std::stringstream stream_2;

//  -----------------------------------------

    stream_1.str("{ 1, 1 }");

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

/////////////////////////////////////////////////////////////////////////////////////