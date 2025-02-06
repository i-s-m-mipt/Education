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

////////////////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{
    int data_1 = 0;
    
    std::string data_2;
    
    std::vector < int > data_3;
};

////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        nlohmann::json json; // support: boost::property_tree

        Entity entity(1, "aaaaa", { 1, 2, 3, 4, 5 });

        json["data_1"] = entity.data_1;

        json["data_2"] = entity.data_2;

        json["data_3"] = entity.data_3;

        json["x"]["y"] = 1;

        if (std::fstream stream("13.12.serialization.json.example.json", std::ios::out); stream)
        {
            stream << std::setw(4) << json;
        }
        else 
        {
            throw std::runtime_error("invalid stream");
        }

        std::cout << "main : enter char to continue : "; char x = 0; std::cin >> x;
    }
    
//  --------------------------------------------------------------------------------------------

    {
        nlohmann::json json;

        if (std::fstream stream("13.12.serialization.json.example.json", std::ios::in); stream)
        {
            json = nlohmann::json::parse(stream);
        }
        else 
        {
            throw std::runtime_error("invalid stream");
        }

        Entity entity(1, "aaaaa", { 1, 2, 3, 4, 5 });

        assert(json["data_1"].get < decltype(entity.data_1) > () == entity.data_1);

        assert(json["data_2"].get < decltype(entity.data_2) > () == entity.data_2);

        assert(json["data_3"].get < decltype(entity.data_3) > () == entity.data_3);

        assert(json["x"]["y"].get < int > () == 1);
    }

//  --------------------------------------------------------------------------------------------

    {
        std::filesystem::remove("13.12.serialization.json.example.json");
    }
}