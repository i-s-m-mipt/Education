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

class Traits : public std::char_traits < char > 
{
public:

    static auto eq(char x, char y) { return std::toupper(x) == std::toupper(y); }

    static auto lt(char x, char y) { return std::toupper(x) <  std::toupper(y); }

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

    static auto find(const char * string, std::size_t size, char x) -> const char *
    {
        for (auto i = 0uz; i < size; ++i) 
        {
            if (eq(string[i], x)) 
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
        auto string = "aaaaa"s; string.append("bbbbb");
        
        assert(string.contains("aaa") && string.substr(4, 2) == "ab");

        assert(string.find('b') != std::string::npos);

        assert(std::to_string(1) == "1" && std::stoi("1") == 1);
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
        using cistring_t = std::basic_string < char, Traits > ;

        assert(cistring_t("aaaaa") == cistring_t("AAAAA"));
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

//      std::string_view string_view_2 = string; string = "bbbbb"; // bad

//      std::string_view string_view_3 = [](){ return "aaaaa"s; }(); // bad
    }

//  -------------------------------------------------------------------------------------------

	{
        benchmark::RunSpecifiedBenchmarks();
    }
}