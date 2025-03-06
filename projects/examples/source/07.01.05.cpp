#include <cassert>

//////////////////////////////////////////////

union Entity // support: compiler-explorer.com
{ 
	char data_1[1];
	
	char data_2[2];
	
	char data_3[3];
	
	int  data_4 = 0;
};

//////////////////////////////////////////////

int main()
{
	Entity entity;

//  ---------------------------------------

	entity.data_1[0] = 'a';

//  ---------------------------------------

	assert(entity.data_1[0] == 'a');

//	assert(entity.data_2[0] == 'a'); // bad

//	assert(entity.data_3[0] == 'a'); // bad

//  ---------------------------------------

	entity.data_1[0] = 0;
		
	entity.data_3[1] = 1;

//  ---------------------------------------

	assert(entity.data_4 == 256);
}