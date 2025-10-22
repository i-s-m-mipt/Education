////////////////////////////////////////////////////////////////////////////////////////////

#include <filesystem>
#include <iostream>
#include <iterator>
#include <fstream>
#include <print>
#include <sstream>
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////

void transform(std::string const & path_1, std::string const & path_2)
{
    auto string = (std::stringstream() << std::fstream(path_1, std::ios::in).rdbuf()).str();

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

        if (*iterator == '\"')
        {
            do
            {
                ++iterator;
            } 
            while (!(*iterator == '\"' && *std::prev(iterator) != '\\'));
        }
                
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

        if (iterator == std::end(string)) 
        {
            break;
        }
    }

    std::fstream(path_2, std::ios::out) << string;
}

////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto path_1 = "source.cpp";

	auto path_2 = "output.cpp";

//  ---------------------------------------------------

    transform(path_1, path_2);

//  ---------------------------------------------------

    std::print("main : enter char : "); std::cin.get();

//  ---------------------------------------------------

    std::filesystem::remove(path_2);
}

////////////////////////////////////////////////////////////////////////////////////////////