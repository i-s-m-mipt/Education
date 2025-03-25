#include <functional>
#include <unordered_set>

/////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int x = 0;
};

/////////////////////////////////////////////////////////////////

class Hash
{
public :

	auto operator()(const Entity & entity) const
	{
		return std::hash < int > ()(entity.x);
	}
};

/////////////////////////////////////////////////////////////////

class Equal
{
public :

	auto operator()(const Entity & lhs, const Entity & rhs) const
	{
		return lhs.x == rhs.x;
	}
};

/////////////////////////////////////////////////////////////////

int main()
{
	std::unordered_set < Entity, Hash, Equal > entities = 
	{
		{ 1 }, { 2 }, { 3 }, { 4 }, { 5 }
	};
}