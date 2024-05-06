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

//  ================================================================================================

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

    [[nodiscard]] static int compare(const char * string_1, 
                                     const char * string_2, std::size_t n) noexcept
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

//  ================================================================================================

using cistring_t = std::basic_string < char, case_insensitive_traits > ;

//  ================================================================================================

inline std::ostream & operator<<(std::ostream & stream, const cistring_t & cistring)
{
    return (stream << std::string(cistring.data(), std::size(cistring)));
}

//  ================================================================================================

template < typename T1, typename T2 > 

[[nodiscard]] inline constexpr std::ptrdiff_t distance_in_bytes(const T1 * ptr_1, 
                                                                const T2 * ptr_2) noexcept
{
    return (std::bit_cast < const std::byte * > (ptr_1) - 
            std::bit_cast < const std::byte * > (ptr_2));
}

//  ================================================================================================

inline void print(std::string_view view) { std::cout << view << std::endl; }

//  ================================================================================================

void test_1(benchmark::State & state)
{
    const std::string string(65536, 'a');

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(string.substr(0, state.range(0)));	
    }

    state.SetComplexityN(state.range(0));
}

//  ================================================================================================

void test_2(benchmark::State & state)
{
    const std::string string(65536, 'a');

    const std::string_view view(string);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(view.substr(0, state.range(0)));	
    }

    state.SetComplexityN(state.range(0));
}

//  ================================================================================================

BENCHMARK(test_1)->DenseRange(8192, 65537, 8192)->Complexity();
BENCHMARK(test_2)->DenseRange(8192, 65537, 8192)->Complexity();

//  ================================================================================================

int main(int argc, char ** argv)
{
    std::cout << "Enter string 1: "; std::string string_1; std::cin >> string_1;
    std::cout << "Enter string 2: "; std::string string_2; 
    
    std::getline(std::cin >> std::ws, string_2);

    std::cout << std::quoted(string_1) << ' ' << std::quoted(string_2) << std::endl;

//  ================================================================================================

    const auto string_3 = "Hello, world!"s;

    if (const auto index = string_3.find(','); index != std::string::npos)
    {
        assert(string_3.substr(0, index) == "Hello");
    }

    assert(string_3.starts_with("Hello") && string_3.ends_with('!'));

    auto string_4 = "43"s; string_4.erase(1); string_4.append("2");

    assert(std::stoi(string_4) == 42 && string_4 == std::to_string(42));

//  ================================================================================================

    [[maybe_unused]] constexpr char char_array[]{ 'h', 'e', 'l', 'l', 'o'       };

    [[maybe_unused]] constexpr char c_string_1[]{ 'h', 'e', 'l', 'l', 'o', '\0' };
    
    [[maybe_unused]] constexpr char c_string_2[] = "hello";

    [[maybe_unused]] constexpr auto c_string_3   = "hello";

    assert(std::strlen(string_3.c_str()) == 13);

//  ================================================================================================

    std::cout << "Enter characters: "; char buffer[256]{};

    std::cin.getline(buffer, std::size(buffer));

    std::cout << buffer << std::endl;

//  std::cout << char_array << std::endl; // bad: отсутствует нулевой символ в конце строки

//  ================================================================================================

    assert(cistring_t("HELLO") == cistring_t("hello"));

//  ================================================================================================

    const auto string_5 = "hello"s, string_6 = "abcdefghijklmnopqrstuvwxyz"s;

    std::cout << distance_in_bytes(&string_5.front(), &string_5) << std::endl;
    std::cout << distance_in_bytes(&string_6.front(), &string_6) << std::endl;

//  ================================================================================================

    constexpr auto string_view = "Hello, world!"sv;

    print(string_3);
    
    print(string_view);

    print(std::string_view(std::begin(string_3), std::next(std::begin(string_3), 5)));

//  const std::string_view bad_1 = "hello"s + "world"s;          // bad: временный объект

//  const std::string_view bad_2 = [](){ return "hello"s; }();   // bad: временный объект

//  const std::string_view bad_3 = string_4; string_4 = "hello"; // bad: перезаписанная строка

//  ================================================================================================

    benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

    return 0;
}