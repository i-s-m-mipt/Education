#include <functional>
#include <iostream>
#include <vector>

int main()
{
	auto x = 42;
	
//	int & ri; // error: неинициализированная ссылка

	auto & rx = x;

	rx = 42;

	const auto y = 42;

	rx = y;

//	int & ry = y; // error: неконстантная ссылка на константный объект

	[[maybe_unused]] const auto & rcy = y;

//	rcy = 42; // error: константная ссылка

	[[maybe_unused]] const auto & rcv = 42;

//	auto & rv = 42; // error: неконстантная ссылка на временный объект

//  ================================================================================================

//	std::vector < int & > bad_vector; // error: недопустимый контейнер ссылок

	std::vector < std::reference_wrapper < int > > good_vector;

	good_vector.push_back(x);

	good_vector.back().get() = 2;

	std::cout << x << std::endl; 

	return 0;
}