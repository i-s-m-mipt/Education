////////////////////////////////////////////////////////

#include <cstddef>
#include <iostream>
#include <new>

////////////////////////////////////////////////////////

template < typename D > class Entity
{
public :

	static auto operator new(std::size_t size) -> void *
	{
		std::cout << "Entity::operator new\n";

		return ::operator new(size);
	}

//  ----------------------------------------------------

	static void operator delete(void * x, std::size_t)
	{
		std::cout << "Entity::operator delete\n";

		::operator delete(x);
	}

protected :

    Entity() = default;

   ~Entity() = default;
};

////////////////////////////////////////////////////////

class Client : private Entity < Client >
{
private :

	using base_t = Entity < Client > ;

public :

	Client() { std::cout << "Client:: Client\n"; }

   ~Client() { std::cout << "Client::~Client\n"; }

//  ----------------------------------------------------

    using base_t::operator new, base_t::operator delete;
};

////////////////////////////////////////////////////////

int main()
{
    delete new Client;
}

////////////////////////////////////////////////////////