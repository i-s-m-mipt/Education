#include <cassert>
#include <iostream>

//////////////////////////////////////////

class Entity
{
public:

    Entity(int x) : m_data(x) {}

//  --------------------------------------   

    auto get() const 
    { 
//	    m_data = 1; // error

        return m_data; 
    }

//  --------------------------------------

//	void set(int x) { m_data = x; } // bad

    void set(int x) 
    { 
        if (x > 0)
        {
            m_data = x;
        }
    }

//  --------------------------------------

    void test() const;

private: 

    int m_data = 0;
};

//////////////////////////////////////////

void Entity::test() const
{
    std::cout << "Entity::test\n";
}

//////////////////////////////////////////

int main()
{
	Entity entity_1(1);

//	entity_1.m_data = 2; // error

	entity_1.set(2);
		
	assert(entity_1.get() == 2);

//  -----------------------------

    const Entity entity_2(2);

//  entity_2.set(3); // error

    assert(entity_2.get() == 2);

    entity_2.test();
}