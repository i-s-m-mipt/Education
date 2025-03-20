#include <cassert>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std::literals;

#include <nlohmann/json.hpp>

/////////////////////////////////////////////////////////////////

int main()
{
    nlohmann::json json; // support: boost::property_tree

//  -------------------------------------------------------------

    auto string = "aaaaa"s;

    std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  -------------------------------------------------------------

    auto path = "13.03.02.json";

//  -------------------------------------------------------------

    json["string"] = string;

    json["vector"] = vector;

    json["x"]["y"] = 1;

//  -------------------------------------------------------------

    std::fstream(path) << std::setw(4) << json;

//  -------------------------------------------------------------

    std::cout << "main : enter char : "; std::cin.get();

//  -------------------------------------------------------------
    
    json = nlohmann::json::parse(std::fstream(path));

//  -------------------------------------------------------------

    assert(json["string"].get < decltype(string) > () == string);

    assert(json["vector"].get < decltype(vector) > () == vector);

    assert(json["x"]["y"].get < int > () == 1);

//  -------------------------------------------------------------

    std::filesystem::remove(path);
}