//////////////////////////////////////////////

// chapter : Basics of Programming

//////////////////////////////////////////////

// section : Types and Variables

//////////////////////////////////////////////

// content : Logical Types and Literals
//
// content : Type bool
//
// content : Literals false and true
//
// content : Separator ,
//
// content : Attribute [[maybe_unused]]
//
// content : Operator sizeof
//
// content : Compile-Time Assertions
//
// content : Declaration static_assert

//////////////////////////////////////////////

int main()
{
	[[maybe_unused]] bool x = false, y = true;

//  ------------------------------------------

	static_assert(sizeof(bool) == 1);
}

//////////////////////////////////////////////