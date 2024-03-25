#include <cassert>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

using namespace std::literals;

[[nodiscard]] inline bool is_identifier(const std::string & string) // note: C++ identifier
{
	return std::regex_match(string, std::regex(R"([_[:alpha:]]\w*)")); // good: raw string
}

[[nodiscard]] inline std::vector < std::string > search_post_code(const std::string & string)
{
    std::vector < std::string > result;

	if (std::smatch matches; std::regex_search(string, matches, std::regex(R"(\w{2}\d{5}(-\d{4})?)")))
	{
		for (const auto & match : matches) result.push_back(match);
	}

    return result;
}

int main()
{
	assert( is_identifier("hello"));
	assert(!is_identifier("12345"));
	assert( is_identifier("_name"));
	assert(!is_identifier("_3.14"));
    assert( is_identifier("A1234"));

    assert(search_post_code("_NY12345______").at(0) == "NY12345"     );
    assert(search_post_code("_NY1234506789_").at(0) == "NY12345"     );
    assert(search_post_code("_NY12345-6789_").at(0) == "NY12345-6789");
    assert(search_post_code("_NY12345-6789_").at(1) ==        "-6789");

    assert(std::empty(search_post_code("_$1$2$3$4$_")));
    assert(std::empty(search_post_code("NY1234-6789")));

    constexpr auto data = "subsequence in the substring";

    const std::regex pattern(R"(\b(sub)([^ ]*))");

	assert(std::regex_replace(data, pattern, "sub-$2") == "sub-sequence in the sub-string");

    return 0;
}