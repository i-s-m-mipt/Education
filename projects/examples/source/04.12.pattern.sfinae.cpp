#include <concepts>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

using namespace std::literals;

//  ================================================================================================

class Entity_v1
{
public:
	
	explicit Entity_v1(const std::string & data) : m_data(data) 
	{
		std::clog << "Entity_v1::Entity_v1 (1)\n";
	}

	explicit Entity_v1(std::string && data) : m_data(std::move(data)) 
	{
		std::clog << "Entity_v1::Entity_v1 (2)\n";
	}
	
	Entity_v1(const Entity_v1 &  other) : m_data(          other.m_data ) {}
	Entity_v1(      Entity_v1 && other) : m_data(std::move(other.m_data)) {}

private:

	std::string m_data;
};

//  ================================================================================================

class Entity_v2
{
public:
	
    template < typename S > explicit Entity_v2(S && data) : m_data(std::forward < S > (data)) 
	{
		std::clog << "Entity_v2::Entity_v2\n";
	}
	
	Entity_v2(const Entity_v2 &  other) : m_data(          other.m_data ) {}
	Entity_v2(      Entity_v2 && other) : m_data(std::move(other.m_data)) {}

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
	explicit Entity_v3(S && data) : m_data(std::forward < S > (data))
	{
		std::clog << "Entity_v3::Entity_v3\n";
	}
	
	Entity_v3(const Entity_v3 &  other) : m_data(          other.m_data ) {}
	Entity_v3(      Entity_v3 && other) : m_data(std::move(other.m_data)) {}

private:

	std::string m_data;
};

//  ================================================================================================

class Entity_v4
{
public:
	
    template < typename S > explicit Entity_v4
	(
		S && data
	) 
	requires std::is_convertible_v < S, std::string > : m_data(std::forward < S > (data))
	{
		std::clog << "Entity_v4::Entity_v4\n";
	}
	
	Entity_v4(const Entity_v4 &  other) : m_data(          other.m_data ) {}
	Entity_v4(      Entity_v4 && other) : m_data(std::move(other.m_data)) {}

private:

	std::string m_data;
};

//  ================================================================================================

int main()
{
	auto data_1 = "aaaaa"s;

	Entity_v1 entity_v1_1(               data_1 );
	Entity_v1 entity_v1_2(         	   "aaaaa"s );
	Entity_v1 entity_v1_3(          entity_v1_1 );
	Entity_v1 entity_v1_4(std::move(entity_v1_1));

//  ----------------------------------------------

	auto data_2 = "bbbbb"s;

	const Entity_v2 entity_v2_1(data_2);

    Entity_v2 entity_v2_2(               data_2 );
	Entity_v2 entity_v2_3(             "bbbbb"s );
//	Entity_v2 entity_v2_4(          entity_v2_2 ); // error
    Entity_v2 entity_v2_5(          entity_v2_1 );
	Entity_v2 entity_v2_6(std::move(entity_v2_2));

//  ----------------------------------------------

	auto data_3 = "ccccc"s;

	Entity_v3 entity_v3_1(               data_3 );
	Entity_v3 entity_v3_2(             "ccccc"s );
	Entity_v3 entity_v3_3(          entity_v3_1 );
	Entity_v3 entity_v3_4(std::move(entity_v3_1));

//  ----------------------------------------------

	auto data_4 = "ddddd"s;

	Entity_v4 entity_v4_1(               data_4 );
	Entity_v4 entity_v4_2(             "ddddd"s );
	Entity_v4 entity_v4_3(          entity_v4_1 );
	Entity_v4 entity_v4_4(std::move(entity_v4_1));
}