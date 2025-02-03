#include <cassert>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

//////////////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public:

	Entity(int data) try : m_data(data)
	{
		if (m_data < 0)
		{
			throw std::runtime_error("error");
		}
	}
	catch (...)
	{
		uninitialize();
	}

   ~Entity() noexcept
	{
	//	throw std::runtime_error("error"); // error

		uninitialize();
	}

//  -----------------------------------------------

	void swap(Entity & other) noexcept
	{
		std::swap(m_data, other.m_data);
	}

//  -----------------------------------------------

	auto data() const noexcept
	{
		return m_data;
	}

private:

	void uninitialize() const noexcept
	{ 
		try
		{
			std::cout << "Entity::uninitialize\n";
		}
		catch (...) {}
	}

//  -----------------------------------------------

	int m_data = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > void swap(T & x, T & y) noexcept
(
	std::is_nothrow_move_constructible_v < T > && std::is_nothrow_move_assignable_v < T > 
)
{
	auto z = std::move(y);

	     y = std::move(x);

		 x = std::move(z);
}

//////////////////////////////////////////////////////////////////////////////////////////////

template 
< 
	typename F, typename ... Ts 
> 
decltype(auto) invoke(F && f, Ts && ... xs) noexcept(noexcept(f(std::declval < Ts > ()...)))
{
	return f(std::forward < Ts > (xs)...);
}

//////////////////////////////////////////////////////////////////////////////////////////////

void test_v1() { std::cout << "test_v1\n"; }

void test_v2() 
{
    Entity entity_1(1); test_v1();

    Entity entity_2(2);
}

void test_v3() noexcept
{
    Entity entity_1(1); test_v1();

    Entity entity_2(2);
}

//////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		static_assert(noexcept(std::declval < Entity > ().data()));
	}

//  ---------------------------------------------------------------

	{
		try
		{
			Entity entity(-1);
		}
		catch(const std::exception & exception)
		{
			std::cerr << "main : " << exception.what() << '\n';
		}
	}

//  ---------------------------------------------------------------

	{
		Entity entity_1(1), entity_2(2);

    	entity_1.swap(entity_2);
	}

//  ---------------------------------------------------------------

	{	
		Entity entity_1(1), entity_2(2);

		invoke(swap < Entity > , entity_1, entity_2);
	}

//  ---------------------------------------------------------------

	{
		test_v2(); // support: compiler-explorer.com

    	test_v3(); // support: compiler-explorer.com
	}
}