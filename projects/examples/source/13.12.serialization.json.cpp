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
        throw std::runtime_error("invalid file stream");
    }
}

//  ================================================================================================

[[nodiscard]] auto load(const std::filesystem::path & path)
{
	if (std::fstream fin(path.string(), std::ios::in); fin)
	{
		return nlohmann::json::parse(fin);
	}
	else 
    {
        throw std::runtime_error("invalid file stream");
    }
}

//  ================================================================================================

struct Entity 
{
    struct Key
    {
        static constexpr auto data_1 = "data_1";
        static constexpr auto data_2 = "data_2";
        static constexpr auto data_3 = "data_3";
        static constexpr auto data_4 = "data_4";
    };

    struct Nested 
    {
        std::vector < int > data_4; 
    };

    int data_1 = 0; std::string data_2; Nested data_3;
};

//  ================================================================================================

int main()
{
    Entity entity(1, "entity", { { 1, 2, 3, 4, 5 } });

    const auto path = "13.12.serialization.json.entity.json";

//  ================================================================================================

    nlohmann::json json_1; // support: boost::property_tree

    json_1[Entity::Key::data_1] = entity.data_1;
    json_1[Entity::Key::data_2] = entity.data_2;
    json_1[Entity::Key::data_3]
          [Entity::Key::data_4] = entity.data_3.data_4;

    save(path, json_1);

//  ================================================================================================

    auto json_2 = load(path);

    using data_1_t = int;

    using data_2_t = std::string;

    using data_4_t = std::vector < int > ;

    assert(json_2[Entity::Key::data_1].get < data_1_t > () == entity.data_1);
    assert(json_2[Entity::Key::data_2].get < data_2_t > () == entity.data_2);
    assert(json_2[Entity::Key::data_3]
                 [Entity::Key::data_4].get < data_4_t > () == entity.data_3.data_4);

//  ================================================================================================

    std::cout << "Enter any character to continue : "; char c; std::cin >> c;

    std::filesystem::remove(path);
}