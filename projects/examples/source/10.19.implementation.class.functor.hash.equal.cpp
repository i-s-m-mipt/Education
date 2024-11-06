#include <iostream>
#include <string>
#include <unordered_set>

//  ================================================================================================

struct Entity 
{ 
	int data = 0; 
};

//  ================================================================================================

struct Hash
{
	[[nodiscard]] auto operator()(const Entity & entity) const
	{
		return std::hash < int > ()(entity.data);
	}
};

//  ================================================================================================

struct Equal
{
	[[nodiscard]] auto operator()(const Entity & lhs, const Entity & rhs) const
	{
		return lhs.data == rhs.data;
	}
};

//  ================================================================================================

int main()
{
	auto hash = Hash()(Entity(1));

	std::cout << "hash = " << hash << '\n';

	std::unordered_set < Entity, Hash, Equal > entities;

	entities.emplace(1);
}