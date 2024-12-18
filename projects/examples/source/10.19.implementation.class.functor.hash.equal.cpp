#include <functional>
#include <unordered_set>

/////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int data = 0; 
};

/////////////////////////////////////////////////////////////////

class Hash
{
public:

	auto operator()(const Entity & entity) const
	{
		return std::hash < int > ()(entity.data);
	}
};

/////////////////////////////////////////////////////////////////

class Equal
{
public:

	auto operator()(const Entity & lhs, const Entity & rhs) const
	{
		return lhs.data == rhs.data;
	}
};

/////////////////////////////////////////////////////////////////

int main()
{
	std::unordered_set < Entity, Hash, Equal > entities;
}