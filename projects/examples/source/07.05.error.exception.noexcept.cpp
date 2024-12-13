#include <cassert>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

///////////////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public:

    Entity() noexcept = default;

	explicit Entity(int data) try : m_data(data)
	{
		std::clog << "Entity::Entity\n";

		throw std::runtime_error("error");
	}
	catch (...)
	{
		uninitialize();
	}

   ~Entity() noexcept
	{
		uninitialize();
	}

//  ----------------------------------------------

	void swap(Entity & other) noexcept
	{
		std::swap(m_data, other.m_data);
	}

//  ----------------------------------------------

	auto data() const noexcept
	{
		return m_data;
	}

private:

	void uninitialize() const noexcept
	{ 
		try
		{
			std::clog << "Entity::uninitialize\n";
		}
		catch (...) {}
	}

//  ----------------------------------------------

	int m_data = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > void swap(T & x, T & y) noexcept
(
	std::is_nothrow_move_constructible_v < T > &&
	std::is_nothrow_move_assignable_v    < T > 
)
{
	auto z = std::move(y);
	     y = std::move(x);
		 x = std::move(z);
}

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename F, typename ... Ts > decltype(auto) invoke(F && f, Ts && ... args) noexcept
(
	noexcept(f(std::declval < Ts > ()...))
)
{
	return f(std::forward < Ts > (args)...);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void test_v1() { std::clog << "test_v1\n"; }

void test_v2() 
{
    Entity entity_1; test_v1();
    Entity entity_2;
}

void test_v3() noexcept
{
    Entity entity_1; test_v1();
    Entity entity_2;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity_1(1);
    Entity entity_2(2);

    entity_1.swap(entity_2);

    assert(entity_1.data() == 2);
    assert(entity_2.data() == 1);

//  ---------------------------------------------

    invoke(swap < Entity > , entity_1, entity_2);

    assert(entity_1.data() == 1);
    assert(entity_2.data() == 2);

//  ---------------------------------------------

    test_v2(); // support: compiler-explorer.com
    test_v3(); // support: compiler-explorer.com
}