int main()
{
    	  auto x = 1;
		  
	const auto y = 2;

//  -------------------------------------------------------

	[[maybe_unused]]       int * const p_x_1 = &x;

//	[[maybe_unused]]       int * const p_y_1 = &y; // error

//  -------------------------------------------------------

	[[maybe_unused]] const int *       p_x_2 = &x;

	[[maybe_unused]] const int *       p_y_2 = &y;

//  -------------------------------------------------------

	[[maybe_unused]] const int * const p_x_3 = &x;

	[[maybe_unused]] const int * const p_y_3 = &y;
}