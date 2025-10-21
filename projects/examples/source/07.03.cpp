////////////////////////////////////////////////////////

#include <cassert>
#include <cerrno>
#include <cmath>
#include <cstring>
#include <print>
#include <tuple>

////////////////////////////////////////////////////////

auto g_has_error = false;

////////////////////////////////////////////////////////

auto test(bool & has_error)
{
    return g_has_error = has_error = true;
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

    std::print("main : string = {}\n", string);
}

////////////////////////////////////////////////////////