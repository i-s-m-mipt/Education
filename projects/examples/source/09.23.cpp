///////////////////////////////////////////////////////////////////

// chapter : Memory Management

///////////////////////////////////////////////////////////////////

// section : Dynamic Memory

///////////////////////////////////////////////////////////////////

// content : Overloading Functions operator new and operator delete

///////////////////////////////////////////////////////////////////

#include <cstddef>
#include <new>
#include <print>

///////////////////////////////////////////////////////////////////

template < typename D > class Entity
{
public :

	static auto operator new(std::size_t size) -> void *
	{
		std::print("Entity::operator new\n");

		return ::operator new(size);
	}

//  ----------------------------------------------------

	static void operator delete(void * x)
	{
		std::print("Entity::operator delete\n");

		::operator delete(x);
	}

protected :

    Entity() = default;
};

///////////////////////////////////////////////////////////////////

class Client : private Entity < Client >
{
public :

	Client() { std::print("Client:: Client\n"); }

   ~Client() { std::print("Client::~Client\n"); }

//  ---------------------------------------------

    using Entity < Client > ::operator new;

	using Entity < Client > ::operator delete;
};

///////////////////////////////////////////////////////////////////

int main()
{
    delete new Client;
}

///////////////////////////////////////////////////////////////////