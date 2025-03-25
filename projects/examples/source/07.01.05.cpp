#include <cassert>

///////////////////////////////////////////////

union Entity // support : compiler-explorer.com
{ 
	char array_1[1];
	
	char array_2[2];
	
	char array_3[3];

//  ----------------
	
	int x = 0;
};

///////////////////////////////////////////////

int main()
{
	Entity entity;

//  ----------------------------------------

	entity.array_1[0] = 'a';

//  ----------------------------------------

	assert(entity.array_1[0] == 'a');

//	assert(entity.array_2[0] == 'a'); // bad

//	assert(entity.array_3[0] == 'a'); // bad

//  ----------------------------------------

	entity.array_1[0] = 0;
		
	entity.array_3[1] = 1;

//  ----------------------------------------

	assert(entity.x == 256);
}