//////////////////////////////////////////////////

int main()
{
	auto x = 1.0;

//  ----------------------------------------------

//	[[maybe_unused]] int       &  y1 = x; // error

	[[maybe_unused]] int const &  y2 = x;

	[[maybe_unused]] int       && y3 = x;

	[[maybe_unused]] int const && y4 = x;
}

//////////////////////////////////////////////////