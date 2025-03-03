int main()
{
    auto x = 1; const auto y = 2;

//  ------------------------------------------------

	[[maybe_unused]]       int & p_x_1 = x;

//	[[maybe_unused]]       int & p_y_1 = y; // error

//  ------------------------------------------------

	[[maybe_unused]] const int & p_x_2 = x;

	[[maybe_unused]] const int & p_y_2 = y;

//  ------------------------------------------------

//	[[maybe_unused]]       int & ref_1 = 1; // error

    [[maybe_unused]] const int & ref_2 = 1;
}