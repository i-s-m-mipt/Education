#include <iostream>

int main()
{
	int x;

//	int u = x; // error

	bool   b = true;
	char   c =  'a';
	int    i =   42;
	double d = 3.14;

	int m = 0, n = 42;

	int x0;
	int x1{};
	int x2 = int();
	int x3 = int{};
	int x4 = i;
	int x5(i);
	int x6{i};
	int x7 = {i};

	auto y = i;

//	auto y0; // error

//	auto y1{}; // error

	auto y2 = int(); // auto -> int
	auto y3 = int{}; // auto -> int
	auto y4 = i;     // auto -> int
	auto y5(i);      // auto -> int
	auto y6{i};      // auto -> int 
	auto y7 = {i};   // auto -> std::initilizer_list < int > 

//	int z0 = d; // warning

//	int z1{d}; // error

	int z2{(int)d};
	int z3{int(d)};
	int z4{static_cast < int > (d)};
	int z5{c};

//	int z6{static_cast < int > ("Hello")}; // error

	b = m;

	std::cout << b << '\n';

	b = static_cast < bool > (n);

	std::cout << b << '\n';

	const double pi = 3.14;

	using type = const double;

	type e = 2.72;

	typedef double old_type;

	x, x0, x1, x2, x3, x4, x5, x6, x7;
	y,         y2, y3, y4, y5, y6, y7; 
			   z2, z3, z4, z5;
	pi, e;

	[[maybe_unused]] auto z = 42;

	return 0;
}