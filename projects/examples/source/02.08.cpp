/////////////////////////////////////////////////////////////////

// chapter : Functions

/////////////////////////////////////////////////////////////////

// content : Initialization and Assignment
//
// content : Default, Value, Direct, Copy and List Initialization
//
// content : Undefined Behavior (UB)
//
// content : Uniform Braced Initialization

/////////////////////////////////////////////////////////////////

int main()
{
//	[[maybe_unused]] int x1; // bad

//	[[maybe_unused]] int x2 = x1; // error

	[[maybe_unused]] int x3{};

	[[maybe_unused]] int x4(4);

	[[maybe_unused]] int x5 = 5;

	[[maybe_unused]] int x6 { 6 };

	[[maybe_unused]] int x7 = { 7 };
}

/////////////////////////////////////////////////////////////////