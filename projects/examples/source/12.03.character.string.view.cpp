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

///////////////////////////////////////////////////////////////////////////////////////////////

class case_insensitive_traits : public std::char_traits < char > 
{
public:

    static auto eq(char c1, char c2) { return std::toupper(c1) == std::toupper(c2); }

    static auto lt(char c1, char c2) { return std::toupper(c1) <  std::toupper(c2); }

    static auto compare
    (
        const char * string_1, const char * string_2, std::size_t size
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
                return &string[i];
            }
        }

        return nullptr;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename T1, typename T2 > auto distance(T1 * ptr_1, T2 * ptr_2)
{
    return 
    (
        std::bit_cast < std::byte * > (ptr_1) - std::bit_cast < std::byte * > (ptr_2)
    );
}

///////////////////////////////////////////////////////////////////////////////////////////////

void test(std::string_view) {}

///////////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    std::string string(65'536, 'a');

    for (auto element : state)
    {
        benchmark::DoNotOptimize(string.substr(0, state.range(0)));	
    }

    state.SetComplexityN(state.range(0));
}

///////////////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    std::string string(65'536, 'a');

    std::string_view view(string);

    for (auto element : state)
    {
        benchmark::DoNotOptimize(view.substr(0, state.range(0)));	
    }

    state.SetComplexityN(state.range(0));
}

///////////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1)->DenseRange(8'192, 65'537, 8'192)->Complexity();

BENCHMARK(test_v2)->DenseRange(8'192, 65'537, 8'192)->Complexity();

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        std::cout << "main : enter std::string : "; std::string string_1; std::cin >> string_1;

        std::cout << "main : enter std::string : "; std::string string_2; 
    
        std::getline(std::cin >> std::ws, string_2);
    }
    
//  -------------------------------------------------------------------------------------------

    {
        auto string = "aaaaabbbbb"s;

        if (auto index = string.find('b'); index != std::string::npos)
        {
            assert(string.substr(0, index) == "aaaaa");
        }

        assert(string.starts_with("aaaaa") && string.ends_with("bbbbb"));

        assert(std::stoi("1") == 1 && "1" == std::to_string(1));
    }

//  -------------------------------------------------------------------------------------------

    {
        [[maybe_unused]] char    array_1[5]{ 'a', 'a', 'a', 'a', 'a' };

        [[maybe_unused]] char c_string_1[6]{ 'a', 'a', 'a', 'a', 'a', '\0' };
        
        [[maybe_unused]] char c_string_2[6] = "aaaaa";

        [[maybe_unused]] auto c_string_3    = "aaaaa";

        auto string = "aaaaa"s;

        assert(std::strlen(string.c_str()) == 5);

        std::cout << "main : enter char[] : "; char array_2[1'000]{};

        std::cin.getline(array_2, std::size(array_2));

//      std::cout << "main : array_1 = " << array_1 << '\n'; // bad

        std::cout << "main : array_2 = " << array_2 << '\n';
    }

//  -------------------------------------------------------------------------------------------

    {
        using cistring_t = std::basic_string < char, case_insensitive_traits > ;

        assert(cistring_t("AAAAA") == cistring_t("aaaaa"));
    }

//  -------------------------------------------------------------------------------------------

    {
        auto string_1 = "aaaaa"s, string_2 = std::string(1'000, 'a');

        assert(distance(&string_1.front(), &string_1) == 16);

        assert(distance(&string_2.front(), &string_2) != 16);
    }

//  -------------------------------------------------------------------------------------------

    {
        auto string = "aaaaa"s; auto string_view = "aaaaa"sv;

        test(string);
    
        test(string_view);

        test(std::string_view(std::begin(string), std::next(std::begin(string), 5)));

//      std::string_view string_view_1 = "aaaaa"s + "bbbbb"s; // bad

//      std::string_view string_view_3 = string; string = "aaaaa"; // bad

//      std::string_view string_view_2 = [](){ return "aaaaa"s; }(); // bad
    }

//  -------------------------------------------------------------------------------------------

	{
        benchmark::RunSpecifiedBenchmarks();
    }
}