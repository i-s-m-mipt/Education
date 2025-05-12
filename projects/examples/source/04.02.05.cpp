///////////////////////////////////////////////////////////////////

#include <iostream>
#include <utility>

///////////////////////////////////////////////////////////////////

struct Entity {};

///////////////////////////////////////////////////////////////////

void handle_v1(Entity       & ) { std::cout << "handle_v1 (1)\n"; }

void handle_v1(Entity const & ) { std::cout << "handle_v1 (2)\n"; }

void handle_v1(Entity       &&) { std::cout << "handle_v1 (3)\n"; }

///////////////////////////////////////////////////////////////////

void handle_v2(Entity       & entity) { handle_v1(entity); }

void handle_v2(Entity const & entity) { handle_v1(entity); }

///////////////////////////////////////////////////////////////////

void handle_v2(Entity && entity)
{ 
	handle_v1(std::move(entity)); 
}

///////////////////////////////////////////////////////////////////

template < typename E > void handle_v3(E && entity) 
{ 
	handle_v1(std::forward < E > (entity));
}

///////////////////////////////////////////////////////////////////

int main()
{
	Entity       entity_1;

	Entity const entity_2;

//  -------------------------------

	handle_v2(entity_1);

	handle_v2(entity_2);

//  -------------------------------

	handle_v2(std::move(entity_1));

//  -------------------------------

	handle_v3(entity_1);

	handle_v3(entity_2);

//  -------------------------------
	
	handle_v3(std::move(entity_1));
}

///////////////////////////////////////////////////////////////////