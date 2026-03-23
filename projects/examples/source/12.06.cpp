///////////////////////////////////////////////////

// chapter : String Processing

///////////////////////////////////////////////////

// section : Basic Strings and Views

///////////////////////////////////////////////////

// content : Basic Strings
//
// content : String std::string
//
// content : Functions std::getline and std::ws
//
// content : Functions std::stoi and std::to_string

///////////////////////////////////////////////////

// support : Boost.StringAlgorithms

///////////////////////////////////////////////////

#include <cassert>
#include <istream>
#include <sstream>
#include <string>

///////////////////////////////////////////////////

int main()
{
    std::stringstream stream("aaaaa aaaaa");

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

    assert(string == "aaaaa aaaaa");

//  ----------------------------------------------

    assert(string.find('a') != std::string::npos);

//  ----------------------------------------------

    assert(std::stoi(std::to_string(1)) == 1);
}

///////////////////////////////////////////////////