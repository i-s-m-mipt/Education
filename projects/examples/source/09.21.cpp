////////////////////////////////////////////////////////////////////////////////

// chapter : Memory Management

////////////////////////////////////////////////////////////////////////////////

// section : Dynamic Memory

////////////////////////////////////////////////////////////////////////////////

// content : Uninitialized Memory
//
// content : Functions operator new and operator delete
//
// content : Type std::align_val_t
//
// content : Operator new
//
// content : Memory Laundering
//
// content : Functions std::launder and std::destroy_at

////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <memory>
#include <new>
#include <print>

////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

	Entity(int x) : m_x(x)
	{
		std::print("Entity:: Entity : m_x = {}\n", m_x);
	}

//  ----------------------------------------------------

   ~Entity()
	{
		std::print("Entity::~Entity : m_x = {}\n", m_x);
	}

//  ----------------------------------------------------

	auto get() const
	{
		return m_x;
	}

private :

	int const m_x = 0;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto storage = static_cast < std::byte * >
	(
		operator new(sizeof(Entity), std::align_val_t(alignof(Entity)))
	);

//  ----------------------------------------------------------------------------

	[[maybe_unused]] auto entity_1 = new (storage) Entity(1);

	[[maybe_unused]] auto entity_2 = new (storage) Entity(2);

//  ----------------------------------------------------------------------------

//	assert(entity_1->get() == 2); // bad

//  ----------------------------------------------------------------------------

	assert(std::launder(entity_1)->get() == 2);

//  ----------------------------------------------------------------------------

	std::destroy_at(storage);

//  ----------------------------------------------------------------------------

	operator delete(storage, sizeof(Entity), std::align_val_t(alignof(Entity)));
}

////////////////////////////////////////////////////////////////////////////////