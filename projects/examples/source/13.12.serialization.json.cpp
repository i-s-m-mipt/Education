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
    struct Nested 
    {
        std::vector < int > data_3; 
    };

//  --------------------------------------------------

    int data_1 = 0; std::string data_2; Nested nested;
};

//  ================================================================================================

int main()
{
    Entity entity(1, "aaaaa", { { 1, 2, 3, 4, 5 } });

    auto path = "13.12.serialization.json.entity.json";

//  --------------------------------------------------------

    nlohmann::json json_11; // support: boost::property_tree

    json_11["data_1"] = entity.data_1;
    json_11["data_2"] = entity.data_2;

    auto & json_12 = json_11["nested"];

    json_12["data_3"] = entity.nested.data_3;

    save(path, json_11);

//  --------------------------

    auto json_21 = load(path);

    using data_1_t = int;

    using data_2_t = std::string;

    using data_3_t = std::vector < int > ;

    assert(json_21["data_1"].get < data_1_t > () == entity.data_1);
    assert(json_21["data_2"].get < data_2_t > () == entity.data_2);

    auto & json_22 = json_21["nested"];

    assert(json_22["data_3"].get < data_3_t > () == entity.nested.data_3);

//  -------------------------------------------------------------------------

    std::cout << "Enter any character to continue : "; char c; std::cin >> c;

    std::filesystem::remove(path);
}