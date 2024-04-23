#include <cassert>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

// =================================================================================================

void save(const std::filesystem::path & path, const nlohmann::json & object)
{
	if (std::fstream fout(path.string(), std::ios::out); fout)
	{
		fout << std::setw(4) << object;
	}
	else throw std::runtime_error("unable to open file " + path.string());
}

// =================================================================================================

[[nodiscard]] nlohmann::json load(const std::filesystem::path & path)
{
	if (std::fstream fin(path.string(), std::ios::in); fin)
	{
		return nlohmann::json::parse(fin);
	}
	else throw std::runtime_error("unable to open file " + path.string());
}

// =================================================================================================

struct Example 
{ 
    bool b{}; 

    std::vector < int > vector;
    
    struct S { std::string string; double d{}; } s;

}; // struct Example 

// =================================================================================================

struct Key
{
	static constexpr auto b      = "b";
    static constexpr auto vector = "vector";
    static constexpr auto s      = "s";
    static constexpr auto string = "string";
    static constexpr auto d      = "d";

}; // struct Key

// =================================================================================================

int main()
{
    const Example example { true, { 1, 2, 3, 4, 5 }, { "hello", 3.14 } };

    constexpr auto file = "13.12.serialization.json.example.json";

    {
        nlohmann::json object;

        object[Key::b] = example.b;

        object[Key::vector] = example.vector;

        object[Key::s][Key::string] = example.s.string;

        object[Key::s][Key::d] = example.s.d;

        save(file, object);
    }

    {
        const auto object = load(file);

        assert(object[Key::b].get < bool > () == example.b);

        assert(object[Key::vector].get < std::vector < int > > () == example.vector);

        assert(object[Key::s][Key::string].get < std::string > () == example.s.string);

        assert(object[Key::s][Key::d].get < double > () == example.s.d);
    }

    std::cout << "Enter any character to continue: "; char c{}; std::cin >> c;

    std::filesystem::remove(file);

	return 0;
}