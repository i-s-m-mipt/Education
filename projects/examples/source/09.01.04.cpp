#include <cassert>
#include <memory>

//////////////////////////////////////////////////////////////////////

int main()
{
//  std::shared_ptr < int > ptr_1(new int[5]{ 1, 2, 3, 4, 5 }); // bad

//  ------------------------------------------------------------------

	std::shared_ptr < int > ptr_2
	(
		new int[5]{ 1, 2, 3, 4, 5 }, std::default_delete < int[] > ()
	);

//	assert(ptr_2[0] == 1); // error

//  ------------------------------------------------------------------

	std::shared_ptr < int[] > array(new int[5]{ 1, 2, 3, 4, 5 });

	assert(array[0] == 1);

//	assert(*array == 1 && *(array + 1) == 2); // error
}