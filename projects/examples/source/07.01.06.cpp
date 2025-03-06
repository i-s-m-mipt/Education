#include <cassert>
#include <tuple>

///////////////////////////////////////////////////////////

struct Variant 
{
	union 
	{ 
		int data_1, data_2 = 0;
	};
	
	bool has_error = false;
};

///////////////////////////////////////////////////////////

auto test(int x)
{
	if (x > 0)
	{
		return Variant { .data_1 = x, .has_error = false };
	}
	else
	{
		return Variant { .data_2 = 1, .has_error = true  };
	}
}

///////////////////////////////////////////////////////////

int main()
{
	assert(!test(+1).has_error && test(+1).data_1 == 1);

	assert( test(-1).has_error && test(-1).data_2 == 1);
}