#include <cassert>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <string_view>

using namespace std::literals;

#include <benchmark/benchmark.h>

// =================================================================================================

struct case_insensitive_traits : public std::char_traits < char > 
{
    [[nodiscard]] static bool eq(char c1, char c2) noexcept 
    { 
        return std::toupper(c1) == std::toupper(c2); 
    }

    [[nodiscard]] static bool lt(char c1, char c2) noexcept 
    { 
        return std::toupper(c1) <  std::toupper(c2); 
    }

    [[nodiscard]] static int compare(const char * string_1, const char * string_2, std::size_t n) noexcept
    {
        for (std::size_t i = 0; i < n; ++i) 
        {
            if (!eq(string_1[i], string_2[i])) return lt(string_1[i], string_2[i]) ? -1 : +1;
        }

        return 0;
    }
    
    [[nodiscard]] static const char * find(const char * string, std::size_t n, char c) noexcept
    {
        for (std::size_t i = 0; i < n; ++i) 
        {
            if (eq(string[i], c)) return &(string[i]);
        }

        return nullptr;
    }

}; // struct case_insensitive_traits : public std::char_traits < char > 

using cistring_t = std::basic_string < char, case_insensitive_traits > ;

// =================================================================================================

inline std::ostream & operator<<(std::ostream & stream, const cistring_t & cistring)
{
    return (stream << std::string(cistring.data(), std::size(cistring)));
}

// =================================================================================================

inline void print(std::string_view view) { std::cout << view << std::endl; }

// =================================================================================================

void test_1(benchmark::State & state) // note: slow
{
    const std::string string(65536, 'a');

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(string.substr(0, state.range(0)));	
    }

    state.SetComplexityN(state.range(0));
}

// =================================================================================================

void test_2(benchmark::State & state) // note: fast
{
    const std::string string(65536, 'a');

    const std::string_view view(string);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(view.substr(0, state.range(0)));	
    }

    state.SetComplexityN(state.range(0));
}

// =================================================================================================

BENCHMARK(test_1)->DenseRange(8192, 65537, 8192)->Complexity(); // note: O(N) complexity
BENCHMARK(test_2)->DenseRange(8192, 65537, 8192)->Complexity(); // note: O(1) complexity

// =================================================================================================

int main(int argc, char ** argv) // note: arguments for benchmark
{
    std::cout << "Enter string 1: "; std::string string_1; std::cin >> string_1;
    std::cout << "Enter string 2: "; std::string string_2; 
    
    std::getline(std::cin >> std::ws, string_2); // good: skip space characters

    std::cout << std::quoted(string_1) << ' ' << 
                 std::quoted(string_2) << std::endl; // note: see arguments

    const auto string_3 = "Hello, world!"s; // good: auto -> std::string, string literal

    if (const auto index = string_3.find(','); index != std::string::npos)
    {
        assert(string_3.substr(0, index) == "Hello");
    }

    assert(string_3.starts_with("Hello") && string_3.ends_with('!'));

    auto string_4 = "43"s; string_4.erase(1); string_4.append("2");

    assert(std::stoi(string_4) == 42 && string_4 == std::to_string(42));

    [[maybe_unused]] constexpr char char_array[]{ 'h', 'e', 'l', 'l', 'o'       };

    [[maybe_unused]] constexpr char c_string_1[]{ 'h', 'e', 'l', 'l', 'o', '\0' };
    
    [[maybe_unused]] constexpr char c_string_2[] = "hello";
    [[maybe_unused]] constexpr auto c_string_3   = "hello"; // note: auto -> const char *

    assert(std::strlen(string_3.c_str()) == 13); // note: see also cstring library functions

    std::cout << "Enter data: "; char data[256]{};

    std::cin.getline(data, std::size(data)); // note: read maximum 256 characters till \n

    std::cout << data << std::endl; // note: outputs characters till null terminator \0

    assert(cistring_t("HELLO") == cistring_t("hello")); // note: custom char traits

    [[maybe_unused]] const auto small_string = "hello"; // note: small strings optimization

    constexpr auto string_view = "Hello, world!"sv; // note: auto -> std::string_view
    
    print(string_view); // good: prefer string_view for read only purposes

    print(string_3);

    print(std::string_view(std::begin(string_3), std::next(std::begin(string_3), 5)));

//  const std::string_view bad_view_1 = "hello"s + "world"s;                   // bad: undefined behavior

//  const std::string_view bad_view_2 = []() constexpr { return "hello"s; }(); // bad: undefined behavior

//  const std::string_view bad_view_3 = string_4; string_4 = "hello";          // bad: undefined behavior

    benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

    return 0;
}