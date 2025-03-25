#include <cassert>
#include <regex>
#include <string>

////////////////////////////////////////////////////////////////////

auto test(const std::string & string) 
{
    std::regex regex(R"([_[:alpha:]]\w*)"); // support : regex101.com

	return std::regex_match(string, regex); 
}

////////////////////////////////////////////////////////////////////

int main()
{
    assert(test("aaaaa") == 1);
        
	assert(test("12345") == 0);

	assert(test("_aaaa") == 1);

	assert(test("_2345") == 1);

	assert(test("_____") == 1);
}