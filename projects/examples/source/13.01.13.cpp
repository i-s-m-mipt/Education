#include <exception>
#include <filesystem>
#include <ios>
#include <iostream>
#include <iterator>
#include <fstream>
#include <stdexcept>
#include <string>

//////////////////////////////////////////////////////////////////////////////////////

void transform(const std::string & path_1, const std::string & path_2)
{
    auto string = (std::stringstream() << std::fstream(path_1).rdbuf()).str();

//  ----------------------------------------------------------------------------------

    for (auto iterator = std::begin(string); iterator != std::end(string); ++iterator)
    {
        if (*iterator == '\'')
        {
            do
            {
                ++iterator;
            } 
            while (!(*iterator == '\'' && *std::prev(iterator) != '\\'));
        }

    //  -----------------------------------------------------------------

        if (*iterator == '\"')
        {
            do
            {
                ++iterator;
            } 
            while (!(*iterator == '\"' && *std::prev(iterator) != '\\'));
        }

    //  -----------------------------------------------------------------
                
        if (*iterator == '/') 
        {
            if (*std::next(iterator) == '/')
            {
                auto end = std::next(iterator, 2);

                while (end != std::end(string) && *end != '\n')
                {
                    ++end;
                }

                iterator = string.erase(iterator, end);
            }
            else if (*std::next(iterator) == '*')
            {
                auto end = std::next(iterator, 3);

                while (!(*end == '/' && *std::prev(end) == '*'))
                {
                    ++end;
                }

                iterator = string.erase(iterator, ++end);
            }
        }

    //  -----------------------------------------------------------------

        if (iterator == std::end(string)) 
        {
            break;
        }
    }

//  ----------------------------------------------------------------------------------

    std::fstream(path_2) << string;
}

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto path_1 = "13.01.14.cpp";

	auto path_2 = "13.01.15.cpp";

//  ----------------------------------------------------

    transform(path_1, path_2);

//  ----------------------------------------------------

    std::cout << "main : enter char : "; std::cin.get();

//  ----------------------------------------------------

    std::filesystem::remove(path_2);
}