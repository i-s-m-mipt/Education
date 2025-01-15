#include <exception>
#include <filesystem>
#include <ios>
#include <iostream>
#include <iterator>
#include <fstream>
#include <stdexcept>
#include <string>

void transform(const std::string & path_1, const std::string & path_2)
{
    if (std::fstream fin(path_1, std::ios::in); fin)
    {
        std::istreambuf_iterator < char > begin(fin), end;

        std::string data(begin, end);

        for (auto iterator = std::begin(data); iterator != std::end(data); ++iterator) 
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
                    auto last = std::next(iterator, 2);

                    while (last != std::end(data) && *last != '\n')
                    {
                        ++last;
                    }

                    iterator = data.erase(iterator, last);
                }
                else if (*std::next(iterator) == '*')
                {
                    auto last = std::next(iterator, 3);

                    while (!(*last == '/' && *std::prev(last) == '*'))
                    {
                        ++last;
                    }

                    iterator = data.erase(iterator, ++last);
                }
            }

            if (iterator == std::end(data)) 
            {
                break;
            }
        }

        if (std::fstream fout(path_2, std::ios::out); fout)
        {
            fout << data;
        }
        else 
        {
            throw std::runtime_error("invalid stream");
        }
    }
    else 
    {
        throw std::runtime_error("invalid stream");
    }
}

int main()
{
    auto path_1 = "13.07.algorithm.erase.comment.source.txt";

	auto path_2 = "13.07.algorithm.erase.comment.result.txt";

    transform(path_1, path_2);

    std::cout << "main : enter char to continue : "; char c; std::cin >> c;

    std::filesystem::remove(path_2);
}