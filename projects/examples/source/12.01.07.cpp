#include <cassert>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>

using namespace std::literals;

//////////////////////////////////////////////////

// support : Boost.StringAlgorithms

//////////////////////////////////////////////////

int main()
{
    std::stringstream stream("aaaaa bbbbb");

//  ----------------------------------------------

    std::string string;

//  ----------------------------------------------

    stream >> string;

//  ----------------------------------------------

    assert(string == "aaaaa");

//  ----------------------------------------------

    stream.seekg(0);

//  ----------------------------------------------
    
    std::getline(stream >> std::ws, string);

//  ----------------------------------------------

    assert(string == "aaaaa bbbbb");

//  ----------------------------------------------

    assert(string.find('a') != std::string::npos);

//  ----------------------------------------------

    assert(std::stoi(std::to_string(1)) == 1);
}