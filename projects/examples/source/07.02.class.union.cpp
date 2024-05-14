#include <cmath>
#include <iostream>

//  ================================================================================================

union U
{
	char c1[1]; // detail: 1(B)
	char c2[2]; // detail: 2(B)
	char c3[3]; // detail: 3(B)
	
	int i = 0;  // detail: 4(B)

}; // union U

//  ================================================================================================

struct Result
{
	bool has_error = false;

	union
	{ 
		int error_code; double result = 0.0; // support: enum class
	};

}; // struct Result

//  ================================================================================================

[[nodiscard]] inline Result try_log(double x) noexcept
{
	Result result { true, -1 };

	if (x > 0.0)
	{
		result.has_error = false; result.result = std::log(x);
	}

	return result;
}

//  ================================================================================================

inline void print(const Result & result)
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

//  ================================================================================================

int main()
{
	U u;

	u.c1[0] = 'a';

	std::cout << u.c1[0] << std::endl;

//	std::cout << u.c2[0] << std::endl; // bad
//	std::cout << u.c3[1] << std::endl; // bad

	u.i = 0; 
	
	u.c3[1] = 1;

	std::cout << u.i << std::endl;

//  ================================================================================================

	print(try_log(1.0));
	print(try_log(0.0));

	return 0;
}