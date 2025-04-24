////////////////////////////////////////////////////////

#include <cassert>
#include <cerrno>
#include <cmath>
#include <cstring>
#include <iostream>
#include <tuple>

////////////////////////////////////////////////////////

auto g_has_error = false;

////////////////////////////////////////////////////////

auto test(bool & has_error)
{
    g_has_error = true;

      has_error = true;

    return true;
}

////////////////////////////////////////////////////////

int main()
{
    auto has_error = false;

//  ----------------------------------------------------

    assert(test(has_error) && g_has_error && has_error);

//  ----------------------------------------------------

    std::ignore = std::log(+1); assert(errno == 0);
		
	std::ignore = std::log(-1); assert(errno != 0);

//  ----------------------------------------------------

    auto string = std::strerror(errno);

//  ----------------------------------------------------

    std::cout << "main : string = " << string << '\n';
}

////////////////////////////////////////////////////////