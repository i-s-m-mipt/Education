#include <cassert>

//////////////////////////////////////////////////////////

union Entity // support: compiler-explorer.com
{ 
	char array_1[1]; 

	char array_2[2];

	char array_3[3]; int data = 0; 
};

//////////////////////////////////////////////////////////

struct Variant 
{
	union 
	{ 
		int data_1; 
		
		int data_2 = 0; 
	};

	bool has_error = false; 
};

//////////////////////////////////////////////////////////

auto test(int x)
{
	if (x < 0)
	{
		return Variant { .data_1 = 1, .has_error = 1 };
	}
	else
	{
		return Variant { .data_2 = x, .has_error = 0 };
	}
}

//////////////////////////////////////////////////////////

int main()
{
	{
		Entity entity { .data = 0 };

		entity.array_1[0] = 'a';

		assert(entity.array_1[0] == 'a');

//		assert(entity.array_2[0] == 'a'); // bad

//		assert(entity.array_3[0] == 'a'); // bad

		entity.data = 0; 
		
		entity.array_3[1] = 1;

		assert(entity.data == 256);
	}

//  ------------------------------------------------------

	{
		auto x = 1;

		auto variant = test(x);
	
		assert(!variant.has_error && variant.data_2 == x);
	}
}