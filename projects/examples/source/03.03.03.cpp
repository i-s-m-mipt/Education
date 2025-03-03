int main()
{
	auto x = 1.0;

//  -------------------------------------------------

//	[[maybe_unused]]       int &  r_x_1 = x; // error

	[[maybe_unused]] const int &  r_x_2 = x;

	[[maybe_unused]]       int && r_x_3 = x;

	[[maybe_unused]] const int && r_x_4 = x;
}