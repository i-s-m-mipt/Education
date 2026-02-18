/////////////////////////////////////////////////////////////////////////////////////

// chapter : Memory Management

/////////////////////////////////////////////////////////////////////////////////////

// section : Dynamic Memory

/////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <bit>
#include <cstddef>
#include <memory>
#include <new>
#include <print>

/////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 5uz;

//  ---------------------------------------------------------------------------------

	auto begin = static_cast < std::byte * >
	(
		operator new(sizeof(Entity) * size, std::align_val_t(alignof(Entity)))
	);

//  ---------------------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		new (begin + i * sizeof(Entity)) Entity(i + 1);
	}

//  ---------------------------------------------------------------------------------

	auto entity = new (begin) Entity(2);

				  new (begin) Entity(3);

//  ---------------------------------------------------------------------------------

//	assert(entity->get() == 3); // error

//  ---------------------------------------------------------------------------------

	assert(std::launder(std::bit_cast < Entity * > (begin))->get() == 3);

//  ---------------------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		std::destroy_at(entity + i);
	}

//  ---------------------------------------------------------------------------------

	operator delete(begin, sizeof(Entity) * size, std::align_val_t(alignof(Entity)));
}

/////////////////////////////////////////////////////////////////////////////////////