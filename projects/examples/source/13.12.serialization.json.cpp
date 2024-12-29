#include <cassert>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

//  ================================================================================================

void save(const std::filesystem::path & path, const nlohmann::json & json)
{
	if (std::fstream fout(path.string(), std::ios::out); fout)
	{
		fout << std::setw(4) << json;
	}
	else 
    {
        throw std::runtime_error("invalid stream");
    }
}

//  ================================================================================================

auto load(const std::filesystem::path & path)
{
	if (std::fstream fin(path.string(), std::ios::in); fin)
	{
		return nlohmann::json::parse(fin);
	}
	else 
    {
        throw std::runtime_error("invalid stream");
    }
}

//  ================================================================================================

struct Entity 
{
    int data_1 = 0; std::string data_2; std::vector < int > data_3;
};

//  ================================================================================================

int main()
{
    Entity entity { 1, "aaaaa", { 1, 2, 3, 4, 5 } };

    auto path = "13.12.serialization.json.example.json";

//  -------------------------------------------------------------------------

    nlohmann::json json_1; // support: boost::property_tree

    json_1["data_1"] = entity.data_1;
    json_1["data_2"] = entity.data_2;
    json_1["data_3"] = entity.data_3;

    json_1["x"]["y"] = 1;

    save(path, json_1);

//  -------------------------------------------------------------------------

    auto json_2 = load(path);

    using data_1_t = int;

    using data_2_t = std::string;

    using data_3_t = std::vector < int > ;

    assert(json_2["data_1"].get < data_1_t > () == entity.data_1);
    assert(json_2["data_2"].get < data_2_t > () == entity.data_2);
    assert(json_2["data_3"].get < data_3_t > () == entity.data_3);

    assert(json_2["x"]["y"].get < int > () == 1);

//  -------------------------------------------------------------------------

    std::cout << "main : enter char to continue : "; char c; std::cin >> c;

    std::filesystem::remove(path);
}