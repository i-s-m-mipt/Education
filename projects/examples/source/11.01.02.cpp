#include <cassert>
#include <functional>
#include <iostream>
#include <utility>

//////////////////////////////////////////////////////////////////////////

auto test(int x, int y) 
{ 
	return x + y;
}

//////////////////////////////////////////////////////////////////////////

template < typename F, typename ... Ts > auto invoke(F && f, Ts && ... xs)
{
	return f(std::forward < Ts > (xs)...);
}

//////////////////////////////////////////////////////////////////////////

class Entity
{
public:

    void test() const
    {
        std::cout << "Entity::test\n";
    }
};

//////////////////////////////////////////////////////////////////////////

int main()
{
    assert(		invoke(test, 1, 2) == 3);

	assert(std::invoke(test, 1, 2) == 3);

//  -------------------------------------

    std::invoke(&Entity::test, Entity());
}