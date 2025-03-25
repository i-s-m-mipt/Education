#include <cassert>

/////////////////////////////////////////////

int main()
{
	auto x = new auto(1);

	assert(*x == 1);
	
	delete x;
	
//  -----------------------------------------

	auto array = new int[5]{ 1, 2, 3, 4, 5 };

	assert(array[0] == 1);

	delete[] array;

//	delete array; // error
}