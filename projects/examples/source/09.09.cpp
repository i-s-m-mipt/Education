////////////////////////////////////////////////////////////

// chapter : Memory Management

////////////////////////////////////////////////////////////

// content : Embedded Reference Counting

////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>

////////////////////////////////////////////////////////////

#include <boost/intrusive_ptr.hpp>

////////////////////////////////////////////////////////////

class Entity
{
public :

    auto counter() const
    {
        return m_counter;
    }

//  --------------------------------------------------------

    friend void intrusive_ptr_add_ref(Entity const * entity)
    {
        ++entity->m_counter;
    }

//  --------------------------------------------------------

    friend void intrusive_ptr_release(Entity const * entity)
    {
        --entity->m_counter;

        if (entity->m_counter == 0)
        {
            delete entity;
        }
    }

private :

    mutable std::size_t m_counter = 0;
};

////////////////////////////////////////////////////////////

int main()
{
    boost::intrusive_ptr < Entity > entity_1(new Entity());

//  -------------------------------------------------------

    assert(entity_1->counter() == 1);

//  -------------------------------------------------------

	boost::intrusive_ptr < Entity > entity_2 = entity_1;

//  -------------------------------------------------------

	assert(entity_1->counter() == 2);

	assert(entity_2->counter() == 2);
}

////////////////////////////////////////////////////////////