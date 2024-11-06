#include <cassert>

//  ================================================================================================

union Entity 
{ 
	char string_1[1]; 
	char string_2[2];
	char string_3[3]; int data = 0; 
};

//  ================================================================================================

struct Variant 
{ 
	union 
	{ 
		int error; int value = 0; 
	}; 
	
	bool has_error = false; 
};

//  ================================================================================================

[[nodiscard]] auto test(int x)
{
	if (x < 0) 
	{
		return Variant({ .error = 1, .has_error = true });
	}
	else
	{
		return Variant({ .value = x });
	}
}

//  ================================================================================================

int main()
{
	Entity entity;

	entity.string_1[0] = 'a';

	assert(entity.string_1[0] == 'a');
//	assert(entity.string_2[0] == 'a'); // bad
//	assert(entity.string_3[0] == 'a'); // bad

	entity.data = 0; 
	
	entity.string_3[1] = 1;

	assert(entity.data == 256);

//  ------------------------------------------------------------------------------------------------

	auto x = 1;

	auto variant = test(x);
	
	assert(!variant.has_error && variant.value == x);
}