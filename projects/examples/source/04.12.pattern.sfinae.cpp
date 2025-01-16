#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

using namespace std::literals;

//  ================================================================================================

class Entity_v1
{
public:
	
	Entity_v1(const std::string & data) : m_data(data) 
	{
		std::cout << "Entity_v1::Entity_v1 (1)\n";
	}

	Entity_v1(std::string && data) : m_data(std::move(data)) 
	{
		std::cout << "Entity_v1::Entity_v1 (2)\n";
	}
	
	Entity_v1(const Entity_v1 & other) : m_data(other.m_data) 
	{
		std::cout << "Entity_v1::Entity_v1 (3)\n";
	}

	Entity_v1(Entity_v1 && other) : m_data(std::move(other.m_data)) 
	{
		std::cout << "Entity_v1::Entity_v1 (4)\n";
	}

private:

	std::string m_data;
};

//  ================================================================================================

class Entity_v2
{
public:
	
    template < typename S > Entity_v2(S && data) : m_data(std::forward < S > (data)) 
	{
		std::cout << "Entity_v2::Entity_v2 (1)\n";
	}
	
	Entity_v2(const Entity_v2 & other) : m_data(other.m_data) 
	{
		std::cout << "Entity_v2::Entity_v2 (2)\n";
	}

	Entity_v2(Entity_v2 && other) : m_data(std::move(other.m_data)) 
	{
		std::cout << "Entity_v2::Entity_v2 (3)\n";
	}

private:

	std::string m_data;
};

//  ================================================================================================

class Entity_v3
{
public:
	
    template 
	< 
		typename S, typename E = std::enable_if_t 
		< 
			std::is_convertible_v < S, std::string > , void 
		> 
	>
	Entity_v3(S && data) : m_data(std::forward < S > (data))
	{
		std::cout << "Entity_v3::Entity_v3 (1)\n";
	}
	
	Entity_v3(const Entity_v3 & other) : m_data(other.m_data) 
	{
		std::cout << "Entity_v3::Entity_v3 (2)\n";
	}

	Entity_v3(Entity_v3 && other) : m_data(std::move(other.m_data)) 
	{
		std::cout << "Entity_v3::Entity_v3 (3)\n";
	}

private:

	std::string m_data;
};

//  ================================================================================================

class Entity_v4
{
public:
	
    template < typename S > Entity_v4(S && data) requires std::is_convertible_v < S, std::string > 
	: 
		m_data(std::forward < S > (data))
	{
		std::cout << "Entity_v4::Entity_v4 (1)\n";
	}
	
	Entity_v4(const Entity_v4 &  other) : m_data(other.m_data) 
	{
		std::cout << "Entity_v4::Entity_v4 (2)\n";
	}

	Entity_v4(Entity_v4 && other) : m_data(std::move(other.m_data)) 
	{
		std::cout << "Entity_v4::Entity_v4 (3)\n";
	}

private:

	std::string m_data;
};

//  ================================================================================================

int main()
{
	{
		auto data = "aaaaa"s;

		Entity_v1 entity_v1_1(data);

		Entity_v1 entity_v1_2("bbbbb"s);

		Entity_v1 entity_v1_3(entity_v1_1);

		Entity_v1 entity_v1_4(std::move(entity_v1_2));
	}

//  --------------------------------------------------

	{
		auto data = "aaaaa"s;

		Entity_v2 entity_v2_1(data);

		Entity_v2 entity_v2_2("bbbbb"s);

//		Entity_v2 entity_v2_3(entity_v2_1); // error

		Entity_v2 entity_v2_4(std::move(entity_v2_2));

		const Entity_v2 entity_v2_5(data);

    	Entity_v2 entity_v2_6(entity_v2_5);
	}

//  --------------------------------------------------

	{
		auto data = "aaaaa"s;

		Entity_v3 entity_v3_1(data);

		Entity_v3 entity_v3_2("bbbbb"s);

		Entity_v3 entity_v3_3(entity_v3_1);

		Entity_v3 entity_v3_4(std::move(entity_v3_2));
	}

//  --------------------------------------------------

	{
		auto data = "aaaaa"s;

		Entity_v4 entity_v4_1(data);

		Entity_v4 entity_v4_2("bbbbb"s);

		Entity_v4 entity_v4_3(entity_v4_1);

		Entity_v4 entity_v4_4(std::move(entity_v4_2));
	}
}