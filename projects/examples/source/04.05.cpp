/////////////////////////////////////////////////////////////////////

#include <print>

/////////////////////////////////////////////////////////////////////

void show_v1() 
{
	std::print("show_v1\n");
}

/////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > void show_v1(T x, Ts ... ys)
{
	std::print("show_v1 : x = {} ", x);
	
	std::print("sizeof...(ys) = {}\n", sizeof...(ys));
	
	show_v1(ys...); // support : cppinsights.io
}

/////////////////////////////////////////////////////////////////////

template < typename T > void show_v2(T x)
{
	std::print("show_v2 : x = {} ", x);
}

/////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > void show_v2(T x, Ts ... ys)
{
	show_v2(x);

	std::print("sizeof...(ys) = {}\n", sizeof...(ys));

	show_v2(ys...);

	if (sizeof...(ys) == 1)
	{
		std::print("sizeof...(ys) = 0\n");
	}
}

/////////////////////////////////////////////////////////////////////

template < typename ... Ts > void transform(Ts ... xs) 
{ 
	show_v1(xs * xs...); // support : cppinsights.io
}

/////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int x = 0, y = 0;
};

/////////////////////////////////////////////////////////////////////

template < typename ... Ts > auto make_entity(Ts ... xs)
{
	return new Entity(xs...);
}

/////////////////////////////////////////////////////////////////////

int main()
{
	show_v1(1, 2.0, "aaaaa");
		
	show_v2(1, 2.0, "aaaaa");

//  -------------------------

	transform(1, 2, 3);

//  -------------------------

    delete make_entity(1, 1);
}

/////////////////////////////////////////////////////////////////////