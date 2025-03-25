#include <cassert>
#include <functional>
#include <utility>

//////////////////////////////////////////////////////////////////////////

auto test(int x) 
{ 
	return x;
}

//////////////////////////////////////////////////////////////////////////

template < typename F, typename ... Ts > auto invoke(F && f, Ts && ... xs)
{
	return f(std::forward < Ts > (xs)...);
}

//////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    auto test(int x) const
    {
        return x;
    }
};

//////////////////////////////////////////////////////////////////////////

int main()
{
    assert(		invoke(test, 1) == 1);

	assert(std::invoke(test, 1) == 1);

//  -----------------------------------------------------

    assert(std::invoke(&Entity::test, Entity(), 1) == 1);
}