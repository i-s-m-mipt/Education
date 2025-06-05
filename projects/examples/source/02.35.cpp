/////////////////////////////////////////////////

int main()
{
    auto       x = 1;
	
	auto const y = 2;

//  ---------------------------------------------

	[[maybe_unused]] int       & z1 = x;

//	[[maybe_unused]] int       & z2 = y; // error

//	[[maybe_unused]] int       & z3 = 3; // error

//  ---------------------------------------------

	[[maybe_unused]] int const & z4 = x;

	[[maybe_unused]] int const & z5 = y;
	
    [[maybe_unused]] int const & z6 = 3;
}

/////////////////////////////////////////////////