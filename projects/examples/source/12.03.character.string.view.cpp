#include <bit>
#include <cassert>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <string_view>

using namespace std::literals;

#include <benchmark/benchmark.h>

//  ================================================================================================

class case_insensitive_traits : public std::char_traits < char > 
{
public:

    static auto eq(char c1, char c2) { return std::toupper(c1) == std::toupper(c2); }
    static auto lt(char c1, char c2) { return std::toupper(c1) <  std::toupper(c2); }

    static auto compare
    (
        const char * string_1, 
        const char * string_2, std::size_t size
    ) 
    {
        for (auto i = 0uz; i < size; ++i) 
        {
            if (!eq(string_1[i], string_2[i])) 
            {
                return lt(string_1[i], string_2[i]) ? -1 : +1;
            }
        }

        return 0;
    }

    static auto find(const char * string, std::size_t size, char c) -> const char *
    {
        for (auto i = 0uz; i < size; ++i) 
        {
            if (eq(string[i], c)) 
            {
                return &(string[i]);
            }
        }

        return nullptr;
    }
};

//  ================================================================================================

using cistring_t = std::basic_string < char, case_insensitive_traits > ;

//  ================================================================================================

auto & operator<<(std::ostream & stream, const cistring_t & cistring)
{
    return stream << std::string(cistring.data(), std::size(cistring));
}

//  ================================================================================================

template < typename T1, typename T2 > auto distance(T1 * ptr_1, T2 * ptr_2)
{
    return 
    (
        std::bit_cast < std::byte * > (ptr_1) - 
        std::bit_cast < std::byte * > (ptr_2)
    );
}

//  ================================================================================================

void test_v1(std::string_view) {}

//  ================================================================================================

void test_v2(benchmark::State & state)
{
    std::string string(65536, 'a');

    for (auto value : state)
    {
        benchmark::DoNotOptimize(string.substr(0, state.range(0)));	
    }

    state.SetComplexityN(state.range(0));
}

//  ================================================================================================

void test_v3(benchmark::State & state)
{
    std::string string(65536, 'a');

    std::string_view view(string);

    for (auto value : state)
    {
        benchmark::DoNotOptimize(view.substr(0, state.range(0)));	
    }

    state.SetComplexityN(state.range(0));
}

//  ================================================================================================

BENCHMARK(test_v2)->DenseRange(8192, 65537, 8192)->Complexity();
BENCHMARK(test_v3)->DenseRange(8192, 65537, 8192)->Complexity();

//  ================================================================================================

int main()
{
    std::cout << "main : enter string : "; std::string string_1; std::cin >> string_1;

    std::cout << "main : enter string : "; std::string string_2; 
    
    std::getline(std::cin >> std::ws, string_2);

//  ------------------------------------------------------------------------------------

    auto string_3 = "aaaaabbbbb"s;

    if (auto index = string_3.find('b'); index != std::string::npos)
    {
        assert(string_3.substr(0, index) == "aaaaa");
    }

    assert(string_3.starts_with("aaaaa") && string_3.ends_with("bbbbb"));

    assert(std::stoi("1") == 1 && "1" == std::to_string(1));

//  ------------------------------------------------------------------------------------

    [[maybe_unused]] char   buffer_1[]{ 'a', 'a', 'a', 'a', 'a' };

    [[maybe_unused]] char c_string_1[]{ 'a', 'a', 'a', 'a', 'a', '\0' };
    
    [[maybe_unused]] char c_string_2[] = "aaaaa";

    [[maybe_unused]] auto c_string_3   = "aaaaa";

    assert(std::strlen(string_3.c_str()) == 10);

//  ------------------------------------------------------------------------------------

    std::cout << "main : enter string : "; char buffer_2[1'000]{};

    std::cin.getline(buffer_2, std::size(buffer_2));

//  std::cout << "main : buffer_1 = " << buffer_1 << '\n'; // bad

    std::cout << "main : buffer_2 = " << buffer_2 << '\n';

//  ------------------------------------------------------------------------------------

    assert(cistring_t("AAAAA") == cistring_t("aaaaa"));

//  ------------------------------------------------------------------------------------

    auto string_4 = "aaaaa"s, string_5 = std::string(1'000'000, 'a');

    assert(distance(&string_4.front(), &string_4) == 16);
    assert(distance(&string_5.front(), &string_5) != 16);

//  ------------------------------------------------------------------------------------

    auto string_view = "aaaaa"sv;

    test_v1(string_3);
    
    test_v1(string_view);

    test_v1(std::string_view(std::begin(string_3), std::next(std::begin(string_3), 5)));

//  std::string_view bad_view_1 = "aaaaa"s + "bbbbb"s; // bad

//  std::string_view bad_view_3 = string_4; string_4 = "aaaaa"; // bad

//  std::string_view bad_view_2 = [](){ return "aaaaa"s; }(); // bad

//  ------------------------------------------------------------------------------------

	benchmark::RunSpecifiedBenchmarks();
}