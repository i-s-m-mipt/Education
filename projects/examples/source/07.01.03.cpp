#include <cassert>
#include <cmath>
#include <iostream>
#include <tuple>

///////////////////////////////

auto g_has_error = false;

///////////////////////////////

auto test(bool & has_error)
{
    g_has_error = true;

      has_error = true;

    return true;
}

///////////////////////////////

int main()
{
    auto has_error = false;

//  ---------------------------

    assert(test(has_error));

//  ---------------------------

    assert(g_has_error);

    assert(  has_error);

//  ---------------------------

    assert(errno == 0);
		
	std::ignore = std::log(-1);
		
	assert(errno != 0);
}