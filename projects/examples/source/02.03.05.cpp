#include <cassert>

/////////////////////////////////////////////

int main()
{
	auto ptr = new auto(1);

	assert(*ptr == 1);
	
	delete ptr;
	
//  -----------------------------------------

	auto array = new int[5]{ 1, 2, 3, 4, 5 };

	assert(array[0] == 1);

	delete[] array;

//	delete array; // error
}