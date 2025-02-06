#include <cassert>

//////////////////////////////////////////////////////////////

union Entity // support: compiler-explorer.com
{ 
	char data_1[1], data_2[2], data_3[3];
	
	int data_4 = 0;
};

//////////////////////////////////////////////////////////////

struct Variant 
{
	union 
	{ 
		int data_1, data_2 = 0;
	};
	
	bool has_error = 0;
};

//////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////

int main()
{
	{
		Entity entity;

		entity.data_1[0] = 'a';

		assert(entity.data_1[0] == 'a');

//		assert(entity.data_2[0] == 'a'); // bad

//		assert(entity.data_3[0] == 'a'); // bad

		entity.data_1[0] = 0;
		
		entity.data_3[1] = 1;

		assert(entity.data_4 == 256);
	}

//  ----------------------------------------------------------

	{
		auto variant_1 = test(-1);
		
		auto variant_2 = test(+1);

		assert( variant_1.has_error && variant_1.data_1 == 1);

		assert(!variant_2.has_error && variant_2.data_2 == 1);
	}
}