#include <cmath>
#include <iostream>

union U // note: the whole union occupies 4 bytes
{
	char a[1]; // note: 1 bytes
	char b[2]; // note: 2 bytes
	char c[3]; // note: 3 bytes
	
	int i = 0; // note: 4 bytes, zero initialized union

}; // union U

struct Result
{
	bool has_error = false; // note: additional switch

	union // note: anonymous union
	{ 
		int error_code; double result; // note: consider enumerations
	};

}; // struct Result

Result try_log(double x)
{
	Result result = { true, 0 }; // note: error code 0 by default

	if (x > 0.0)
	{
		result.has_error = false; result.result = std::log(x);
	}

	return result;
}

void print(const Result & result)
{
	if (result.has_error)
	{
		std::cout << "error: " << result.error_code << std::endl;
	}
	else
	{
		std::cout << "result: " << result.result << std::endl;
	}
}

int main()
{
	U u;

	u.a[0] = 'a'; // note: u.a is now the active member

	std::cout << u.a[0] << std::endl;

//	std::cout << u.b[0] << std::endl; // bad: undefined behaviour
//	std::cout << u.b[1] << std::endl; // bad: undefined behaviour

	u.i = 0; 
	
	u.c[1] = 1; // note: u.c is now the active member

	std::cout << u.i << std::endl; // note: explain result

	print(try_log(8.0));
	print(try_log(0.0));

	return 0;
}