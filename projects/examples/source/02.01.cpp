//////////////////////////////////////////////

// chapter : Basics of Programming

//////////////////////////////////////////////

// section : Fundamental Data Types

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
// content : Declaration static_assert

//////////////////////////////////////////////

int main()
{
	[[maybe_unused]] bool x = false, y = true;

//  ------------------------------------------

	static_assert(sizeof(bool) == 1);
}

//////////////////////////////////////////////