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
    if (std::fstream stream_1(path_1, std::ios::in); stream_1)
    {
        std::istreambuf_iterator < char > begin(stream_1), end;

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

        if (std::fstream stream_2(path_2, std::ios::out); stream_2)
        {
            stream_2 << data;
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

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto path_1 = "13.07.algorithm.erase.comment.source.txt";

	auto path_2 = "13.07.algorithm.erase.comment.result.txt";

    transform(path_1, path_2);

    std::cout << "main : enter char to continue : "; auto x = '\0'; std::cin >> x;

    std::filesystem::remove(path_2);
}