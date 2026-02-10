///////////////////////////////////////////////////////////////////////

// chapter : Debugging and Profiling

///////////////////////////////////////////////////////////////////////

// section : Wrapping Error Codes

///////////////////////////////////////////////////////////////////////

// content : Wrapper std::optional
//
// content : Tag std::nullopt
//
// content : Function std::make_optional
//
// content : Optional Data Members

///////////////////////////////////////////////////////////////////////

#include <cassert>
#include <optional>

///////////////////////////////////////////////////////////////////////

auto test(int x) -> std::optional < int >
{
    if (x > 0)
	{
		return x;
	}
	else
	{
		return std::nullopt;
	}
}

///////////////////////////////////////////////////////////////////////

int main()
{
    std::optional < int > optional_1 = 1;

    std::optional < int > optional_2 = std::nullopt;

//  -------------------------------------------------------------------

    assert(optional_1.has_value() == 1 && optional_1.value_or(2) == 1);

    assert(optional_2.has_value() == 0 && optional_2.value_or(3) == 3);

//  -------------------------------------------------------------------

    assert(optional_1 > optional_2);

//  -------------------------------------------------------------------

    assert(*std::make_optional < int > (1) == 1);

//  -------------------------------------------------------------------

    assert(test(0).has_value() == 0);

	assert(test(1).has_value() == 1);
}

///////////////////////////////////////////////////////////////////////