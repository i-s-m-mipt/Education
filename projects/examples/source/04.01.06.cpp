#include <cassert>

//////////////////////////////////////////////////////

template < typename ... Ts > auto reduce_v1(Ts ... xs)
{
	return (... + xs); // support: cppinsights.io
}

template < typename ... Ts > auto reduce_v2(Ts ... xs)
{
	return (xs + ...); // support: cppinsights.io
}

template < typename ... Ts > auto reduce_v3(Ts ... xs)
{
	return (0 + ... + xs); // support: cppinsights.io
}

template < typename ... Ts > auto reduce_v4(Ts ... xs)
{
	return (xs + ... + 0); // support: cppinsights.io
}

//////////////////////////////////////////////////////

int main()
{
	assert(reduce_v1(1, 2, 3) == 6);
		
	assert(reduce_v2(1, 2, 3) == 6);

	assert(reduce_v3(1, 2, 3) == 6);

	assert(reduce_v4(1, 2, 3) == 6);
}