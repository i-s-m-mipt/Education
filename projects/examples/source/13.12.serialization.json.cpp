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

[[nodiscard]] nlohmann::json load(const std::filesystem::path & path)
{
	if (std::fstream fin(path.string(), std::ios::in); fin)
	{
		return nlohmann::json::parse(fin);
	}
	else throw std::runtime_error("unable to open file " + path.string());
}

void save(const std::filesystem::path & path, const nlohmann::json & object)
{
	if (std::fstream fout(path.string(), std::ios::out); fout)
	{
		fout << std::setw(4) << object;
	}
	else throw std::runtime_error("unable to open file " + path.string());
}

// =================================================================================================

struct Config 
{ 
    bool flag{}; 

    std::vector < int > parameters;
    
    struct Server { std::string name; double parameter{}; } server;

}; // struct Config 

// =================================================================================================

struct File
{
	static constexpr auto config = "config.json";

}; // struct File

struct Key
{
	static constexpr auto flag       = "flag";
    static constexpr auto parameters = "parameters";
    static constexpr auto server     = "server";
    static constexpr auto name       = "name";
    static constexpr auto parameter  = "parameter";

}; // struct Key

// =================================================================================================

int main()
{
    const Config config { true, { 1, 2, 3, 4, 5 }, { "hello", 3.14 } };

    {
        nlohmann::json object;

        object[Key::flag] = config.flag;

        object[Key::parameters] = config.parameters;

        object[Key::server][Key::name] = config.server.name;

        object[Key::server][Key::parameter] = config.server.parameter;

        save(File::config, object);
    }

    {
        const auto object = load(File::config);

        assert(object[Key::flag].get < bool > () == config.flag);

        assert(object[Key::parameters].get < std::vector < int > > () == config.parameters);

        assert(object[Key::server][Key::name].get < std::string > () == config.server.name);

        assert(object[Key::server][Key::parameter].get < double > () == config.server.parameter);
    }

    std::cout << "Continue? (y/n) "; char c{}; std::cin >> c;

    std::remove(File::config);

	return 0;
}