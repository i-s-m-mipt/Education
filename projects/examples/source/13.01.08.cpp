#include <cassert>
#include <exception>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>

////////////////////////////////////////////////////////

int main()
{
    auto path = "13.01.08.data";

    auto size = 5uz;

//  ----------------------------------------------------

    if (std::fstream stream(path); stream)
    {
        for (auto i = 0uz; i < size; ++i)
        {
            stream << "aaaaa\n";
        }

        stream.seekp((size - 1) * 6, std::ios::beg);

        stream << "bbbbb\n";
    }
    else 
    {
        throw std::runtime_error("invalid stream");
    }

//  ----------------------------------------------------

    std::cout << "main : enter char : "; std::cin.get();

//  ----------------------------------------------------

    if (std::fstream stream(path); stream)
    {
        stream.seekg((size - 1) * 6, std::ios::beg);

    //  --------------------------------------------

        std::string string;

    //  --------------------------------------------
            
        std::getline(stream >> std::ws, string);

    //  --------------------------------------------
            
        assert(string == "bbbbb");
    }
    else 
    {
        throw std::runtime_error("invalid stream");
    }

//  ----------------------------------------------------

    std::filesystem::remove(path);
}